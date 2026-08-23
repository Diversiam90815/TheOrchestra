/*
  ==============================================================================
	Module			Voice Behaviour Tests
	Description		Regression tests for the real-time and audio-quality fixes in ArticulationVoice:
					round-robin cycling, the release envelope, dynamic-layer alignment and
					block-size independence.
  ==============================================================================
*/

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>

#include "ArticulationVoice.h"


namespace SamplerTests
{

namespace
{

constexpr double		  kSampleRate	= 44100.0;
constexpr int			  kBufferLength = 44100;
constexpr int			  kRootNote		= 72;
constexpr int			  kRangeLow		= 60;
constexpr int			  kRangeHigh	= 84;

/* A buffer holding one constant value, so the value identifies which sample was picked. */
juce::AudioBuffer<float> *makeConstantBuffer(float value, int numSamples = kBufferLength)
{
	auto *buffer = new juce::AudioBuffer<float>(2, numSamples);

	for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
		for (int i = 0; i < numSamples; ++i)
			buffer->setSample(channel, i, value);

	return buffer;
}


/* Adds one dynamic layer whose round-robins carry the given constant values. */
void addLayer(SampleSound &sound, Dynamics dynamics, const std::vector<float> &roundRobinValues)
{
	juce::OwnedArray<juce::AudioBuffer<float>> buffers;

	for (const float value : roundRobinValues)
		buffers.add(makeConstantBuffer(value));

	sound.addDynamicLayer(dynamics, std::move(buffers));
}


/* Renders the voice in fixed-size chunks and returns the flattened left channel. */
std::vector<float> renderInChunks(ArticulationVoice &voice, int totalSamples, int blockSize)
{
	std::vector<float> out;
	out.reserve(static_cast<size_t>(totalSamples));

	juce::AudioBuffer<float> block(2, blockSize);

	for (int rendered = 0; rendered < totalSamples; rendered += blockSize)
	{
		const int thisBlock = juce::jmin(blockSize, totalSamples - rendered);

		block.clear();
		voice.renderNextBlock(block, 0, thisBlock);

		for (int i = 0; i < thisBlock; ++i)
			out.push_back(block.getSample(0, i));
	}

	return out;
}

} // namespace


class VoiceBehaviourTest : public ::testing::Test
{
protected:
	std::unique_ptr<ArticulationVoice> mVoice;
	std::unique_ptr<SampleSound> mSound;

	void							SetUp() override
	{
		mVoice = std::make_unique<ArticulationVoice>();

		// The envelope is sample-rate dependent, so this has to be set for the voice to behave
		// the way it does in the running app.
		mVoice->setCurrentPlaybackSampleRate(kSampleRate);

		mSound = std::make_unique<SampleSound>(kRangeLow, kRangeHigh, kRootNote);
		mSound->setArticulation(Articulation::sustain);
	}
};


//==============================================================================
//   Round-robin
//==============================================================================

/*
	The counter used to be a function-local static shared by every voice, and it advanced once per
	dynamic layer rather than once per note - so with N layers it strode by N and never visited
	every round-robin.
*/
TEST_F(VoiceBehaviourTest, RoundRobinVisitsEverySampleInOrder)
{
	addLayer(*mSound, Dynamics::mezzoForte, {0.10f, 0.20f, 0.30f});

	std::set<int> visited;

	for (int note = 0; note < 3; ++note)
	{
		mVoice->startNote(kRootNote, 1.0f, mSound.get(), 8192);

		// Read past the 2 ms attack so the envelope has reached 1.0 and the rendered value is
		// exactly the constant stored in whichever round-robin buffer was chosen.
		constexpr int			 kReadAt = 256;

		juce::AudioBuffer<float> block(2, kReadAt);
		block.clear();
		mVoice->renderNextBlock(block, 0, kReadAt);

		const float rendered = block.getSample(0, kReadAt - 1);
		const float scale	 = rendered / 0.10f;

		visited.insert(static_cast<int>(std::lround(scale)));

		mVoice->stopNote(0.0f, false);
	}

	EXPECT_EQ(visited.size(), 3u) << "Three consecutive notes should visit three distinct round-robins";
}


TEST_F(VoiceBehaviourTest, RoundRobinCountersAreIndependentPerLayer)
{
	SampleSound soundA(kRangeLow, kRangeHigh, kRootNote);
	SampleSound soundB(kRangeLow, kRangeHigh, kRootNote);

	soundA.setArticulation(Articulation::sustain);
	soundB.setArticulation(Articulation::sustain);

	addLayer(soundA, Dynamics::mezzoForte, {0.25f, 0.5f});
	addLayer(soundB, Dynamics::mezzoForte, {0.25f, 0.5f});

	// Advancing one sound's counter must not move the other's.
	soundA.dynamicLayers[0]->roundRobinCounter.fetch_add(1u);

	EXPECT_EQ(soundA.dynamicLayers[0]->roundRobinCounter.load(), 1u);
	EXPECT_EQ(soundB.dynamicLayers[0]->roundRobinCounter.load(), 0u) << "Round-robin state must not be shared between sounds";
}


//==============================================================================
//   Release envelope
//==============================================================================

/*
	stopNote() used to ignore allowTailOff and call clearCurrentNote() immediately, cutting the
	waveform mid-cycle. On a sustained sample that is an audible click on every note-off.
*/
TEST_F(VoiceBehaviourTest, SustainedNoteOffDecaysWithoutDiscontinuity)
{
	addLayer(*mSound, Dynamics::mezzoForte, {0.5f});

	mVoice->startNote(kRootNote, 1.0f, mSound.get(), 8192);

	// Let the attack settle.
	renderInChunks(*mVoice, 512, 64);

	mVoice->stopNote(0.0f, true);

	// kSustainRelease is 120 ms, i.e. 5292 samples at 44.1 kHz.
	const auto tail = renderInChunks(*mVoice, 8192, 64);

	ASSERT_FALSE(tail.empty());

	float maxJump = 0.0f;
	for (size_t i = 1; i < tail.size(); ++i)
		maxJump = juce::jmax(maxJump, std::abs(tail[i] - tail[i - 1]));

	// A 120 ms release over a constant source moves by well under a thousandth per sample. The old
	// hard cut jumped by the full sample amplitude in one step.
	EXPECT_LT(maxJump, 0.01f) << "Note-off should ramp down, not cut";

	EXPECT_FALSE(mVoice->isEnvelopeActive()) << "Release should have finished within 8192 samples";
	EXPECT_NEAR(tail.back(), 0.0f, 1.0e-4f) << "Tail should decay to silence";
}


TEST_F(VoiceBehaviourTest, ShortArticulationIgnoresNoteOffAndRingsOn)
{
	mSound->setArticulation(Articulation::pizzicato);
	addLayer(*mSound, Dynamics::mezzoForte, {0.5f});

	mVoice->startNote(kRootNote, 1.0f, mSound.get(), 8192);
	renderInChunks(*mVoice, 256, 64);

	// Releasing the key must not stop a one-shot.
	mVoice->stopNote(0.0f, true);

	const auto	afterRelease = renderInChunks(*mVoice, 256, 64);

	const float peak		 = *std::max_element(afterRelease.begin(), afterRelease.end());

	EXPECT_GT(peak, 0.1f) << "A pizzicato should ring on after the key is released";
}


TEST_F(VoiceBehaviourTest, NoteOffWithoutTailOffStopsImmediately)
{
	addLayer(*mSound, Dynamics::mezzoForte, {0.5f});

	mVoice->startNote(kRootNote, 1.0f, mSound.get(), 8192);
	renderInChunks(*mVoice, 256, 64);

	mVoice->stopNote(0.0f, false);

	const auto after = renderInChunks(*mVoice, 256, 64);

	for (const float sample : after)
		EXPECT_FLOAT_EQ(sample, 0.0f) << "allowTailOff=false must silence the voice at once";
}


//==============================================================================
//   Dynamic-layer alignment
//==============================================================================

/*
	startNote() used to skip null layers without writing a slot, so mLayerBuffers could be shorter
	than dynamicLayers - and the mCC1 mapping then spread across a different number of layers than
	the indices were clamped to, selecting the wrong layer.
*/
TEST_F(VoiceBehaviourTest, NullLayerStillOccupiesItsSlot)
{
	addLayer(*mSound, Dynamics::piano, {0.25f});
	mSound->dynamicLayers.add(nullptr); // a layer with no usable samples
	addLayer(*mSound, Dynamics::forte, {0.75f});

	ASSERT_EQ(mSound->dynamicLayers.size(), 3);

	mVoice->startNote(kRootNote, 1.0f, mSound.get(), 8192);

	EXPECT_EQ(mVoice->getNumDynamicLayers(), 3) << "Every dynamic layer needs a slot so indices stay aligned";
}


TEST_F(VoiceBehaviourTest, LayerCountIsClampedToCapacity)
{
	for (int i = 0; i < OrchestraVoiceConstant::MaxDynamicLayers + 4; ++i)
		addLayer(*mSound, Dynamics::mezzoForte, {0.1f});

	mVoice->startNote(kRootNote, 1.0f, mSound.get(), 8192);

	EXPECT_EQ(mVoice->getNumDynamicLayers(), OrchestraVoiceConstant::MaxDynamicLayers) << "Layer count must never exceed the fixed capacity";
}


//==============================================================================
//   Block-size independence
//==============================================================================

/*
	mCC11 advanced per sample while mCC1 advanced once per block, so the length of a mCC1 ramp - and
	therefore the rendered output - depended on whatever block size the host happened to use.
*/
TEST_F(VoiceBehaviourTest, OutputIsIdenticalAcrossBlockSizes)
{
	constexpr int total	 = 4096;

	auto		  render = [this](int blockSize)
	{
		SampleSound sound(kRangeLow, kRangeHigh, kRootNote);
		sound.setArticulation(Articulation::sustain);
		addLayer(sound, Dynamics::piano, {0.25f});
		addLayer(sound, Dynamics::forte, {0.75f});

		ArticulationVoice voice;
		voice.setCurrentPlaybackSampleRate(kSampleRate);
		voice.startNote(kRootNote, 1.0f, &sound, 8192);

		// Start a controller ramp; this is what used to move at a block-dependent rate.
		voice.controllerMoved(kModWheelCc, kMaxCcValue);

		return renderInChunks(voice, total, blockSize);
	};

	const auto small  = render(32);
	const auto medium = render(64);
	const auto large  = render(512);

	ASSERT_EQ(small.size(), medium.size());
	ASSERT_EQ(small.size(), large.size());

	for (size_t i = 0; i < small.size(); ++i)
	{
		ASSERT_NEAR(small[i], medium[i], 1.0e-6f) << "Block sizes 32 and 64 diverge at sample " << i;
		ASSERT_NEAR(small[i], large[i], 1.0e-6f) << "Block sizes 32 and 512 diverge at sample " << i;
	}
}


TEST_F(VoiceBehaviourTest, ControllerRampReachesTargetInTheSameTimeRegardlessOfBlockSize)
{
	constexpr int total		 = 2048;

	auto		  finalValue = [this](int blockSize)
	{
		SampleSound sound(kRangeLow, kRangeHigh, kRootNote);
		sound.setArticulation(Articulation::sustain);
		addLayer(sound, Dynamics::mezzoForte, {0.5f});

		ArticulationVoice voice;
		voice.setCurrentPlaybackSampleRate(kSampleRate);
		voice.startNote(kRootNote, 1.0f, &sound, 8192);

		// Expression starts at full; ramp it down and see where it lands.
		voice.controllerMoved(kExpressionCc, kMinCcValue);

		const auto rendered = renderInChunks(voice, total, blockSize);
		return rendered.back();
	};

	EXPECT_NEAR(finalValue(32), finalValue(512), 1.0e-6f) << "A CC ramp must take the same wall-clock time at any block size";
}

} // namespace SamplerTests
