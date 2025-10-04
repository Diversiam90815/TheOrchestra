/*
  ==============================================================================
	Module			Orchestra Voice Tests
	Description		Testing the Orchestra Voice module from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "OrchestraVoice.h"


namespace SamplerTests
{

class OrchestraVoiceTest : public ::testing::Test
{
protected:
	std::unique_ptr<OrchestraVoice> mVoice;
	std::unique_ptr<OrchestraSound> mSound;


	void							SetUp() override
	{
		mVoice = std::make_unique<OrchestraVoice>();

		// Create a test sound with one dynamic layer
		mSound = std::make_unique<OrchestraSound>(60, 84, 72);

		// Add a dynamic layer with sample data
		juce::OwnedArray<juce::AudioBuffer<float>> buffers;
		auto									  *buffer = new juce::AudioBuffer<float>(2, 44100); // 1 second at 44.1kHz
		buffers.add(buffer);

		mSound->addDynamicLayer(Dynamics::mezzoForte, std::move(buffers));
		mSound->setArticulation(Articulation::sustain);
	}

	void TearDown() override
	{
		mVoice.reset();
		mSound.reset();
	}
};


TEST_F(OrchestraVoiceTest, CanPlayOrchestraSound)
{
	// Should be able to play OrchestraSound
	EXPECT_TRUE(mVoice->canPlaySound(mSound.get())) << "Voice should be able to play OrchestraSound";
}


TEST_F(OrchestraVoiceTest, CannotPlayNullSound)
{
	// Should not be able to play null sound
	EXPECT_FALSE(mVoice->canPlaySound(nullptr)) << "Voice should not play null sound";
}


TEST_F(OrchestraVoiceTest, StartNoteInitializesVoice)
{
	int	  midiNote	 = 72;	 // C4
	float velocity	 = 0.8f;
	int	  pitchWheel = 8192; // Center position

	// Start the note
	EXPECT_NO_THROW(mVoice->startNote(midiNote, velocity, mSound.get(), pitchWheel));

	// Voice should now be in playing state
	// (This is internal state, but we can test by checking if renderNextBlock works)
}


TEST_F(OrchestraVoiceTest, StartNoteWithDifferentVelocities)
{
	int midiNote   = 72;
	int pitchWheel = 8192;

	// Test with low velocity
	EXPECT_NO_THROW(mVoice->startNote(midiNote, 0.2f, mSound.get(), pitchWheel));
	mVoice->stopNote(0.0f, false);

	// Test with medium velocity
	EXPECT_NO_THROW(mVoice->startNote(midiNote, 0.5f, mSound.get(), pitchWheel));
	mVoice->stopNote(0.0f, false);

	// Test with high velocity
	EXPECT_NO_THROW(mVoice->startNote(midiNote, 1.0f, mSound.get(), pitchWheel));
	mVoice->stopNote(0.0f, false);
}


TEST_F(OrchestraVoiceTest, StopNoteWithoutTailOff)
{
	int midiNote   = 72;
	int pitchWheel = 8192;

	mVoice->startNote(midiNote, 0.8f, mSound.get(), pitchWheel);

	// Stop without tail-off
	EXPECT_NO_THROW(mVoice->stopNote(0.0f, false));
}


TEST_F(OrchestraVoiceTest, StopNoteWithTailOff)
{
	int midiNote   = 72;
	int pitchWheel = 8192;

	mVoice->startNote(midiNote, 0.8f, mSound.get(), pitchWheel);

	// Stop with tail-off
	EXPECT_NO_THROW(mVoice->stopNote(0.5f, true));
}


TEST_F(OrchestraVoiceTest, ControllerMovedCC1)
{
	// Set CC1 (modulation) to various values
	EXPECT_NO_THROW(mVoice->controllerMoved(1, 0));
	EXPECT_NO_THROW(mVoice->controllerMoved(1, 64));
	EXPECT_NO_THROW(mVoice->controllerMoved(1, 127));
}


TEST_F(OrchestraVoiceTest, ControllerMovedCC11)
{
	// Set CC11 (expression) to various values
	EXPECT_NO_THROW(mVoice->controllerMoved(11, 0));
	EXPECT_NO_THROW(mVoice->controllerMoved(11, 64));
	EXPECT_NO_THROW(mVoice->controllerMoved(11, 127));
}


TEST_F(OrchestraVoiceTest, PitchWheelMovedDoesNotCrash)
{
	// Pitch wheel is not implemented but should not crash
	EXPECT_NO_THROW(mVoice->pitchWheelMoved(0));
	EXPECT_NO_THROW(mVoice->pitchWheelMoved(8192));
	EXPECT_NO_THROW(mVoice->pitchWheelMoved(16383));
}


TEST_F(OrchestraVoiceTest, RenderNextBlockWithoutStartingNote)
{
	juce::AudioBuffer<float> outputBuffer(2, 512);
	outputBuffer.clear();

	// Should not crash when rendering without starting a note
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));

	// Output should remain silent
	const float *leftChannel  = outputBuffer.getReadPointer(0);
	const float *rightChannel = outputBuffer.getReadPointer(1);

	bool		 isSilent	  = true;
	for (int i = 0; i < 512; ++i)
	{
		if (leftChannel[i] != 0.0f || rightChannel[i] != 0.0f)
		{
			isSilent = false;
			break;
		}
	}

	EXPECT_TRUE(isSilent) << "Output should be silent when no note is playing";
}


TEST_F(OrchestraVoiceTest, RenderNextBlockAfterStartingNote)
{
	juce::AudioBuffer<float> outputBuffer(2, 512);
	outputBuffer.clear();

	int	  midiNote	 = 72;
	float velocity	 = 0.8f;
	int	  pitchWheel = 8192;

	// Start a note
	mVoice->startNote(midiNote, velocity, mSound.get(), pitchWheel);

	// Render some audio
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));

	// Output might have audio (depending on sample data)
	// At minimum, it should not crash
}


TEST_F(OrchestraVoiceTest, ShortArticulationBehavior)
{
	// Create a sound with short articulation
	auto									   shortSound = std::make_unique<OrchestraSound>(60, 84, 72);

	juce::OwnedArray<juce::AudioBuffer<float>> buffers;
	auto									  *buffer = new juce::AudioBuffer<float>(2, 44100);
	buffers.add(buffer);

	shortSound->addDynamicLayer(Dynamics::mezzoForte, std::move(buffers));
	shortSound->setArticulation(Articulation::pizzicato); // Short articulation

	int	  midiNote	 = 72;
	float velocity	 = 0.8f;
	int	  pitchWheel = 8192;

	// Start note with short articulation
	EXPECT_NO_THROW(mVoice->startNote(midiNote, velocity, shortSound.get(), pitchWheel));

	juce::AudioBuffer<float> outputBuffer(2, 512);
	outputBuffer.clear();

	// Render should work with short articulation
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));
}


TEST_F(OrchestraVoiceTest, PitchShiftingAtDifferentNotes)
{
	int rootNote   = 72; // C4
	int pitchWheel = 8192;

	// Test note at root (no pitch shift)
	EXPECT_NO_THROW(mVoice->startNote(rootNote, 0.8f, mSound.get(), pitchWheel));
	mVoice->stopNote(0.0f, false);

	// Test note above root (pitch up)
	EXPECT_NO_THROW(mVoice->startNote(rootNote + 12, 0.8f, mSound.get(), pitchWheel));
	mVoice->stopNote(0.0f, false);

	// Test note below root (pitch down)
	EXPECT_NO_THROW(mVoice->startNote(rootNote - 12, 0.8f, mSound.get(), pitchWheel));
	mVoice->stopNote(0.0f, false);
}


TEST_F(OrchestraVoiceTest, MultipleDynamicLayersCrossfade)
{
	// Create a sound with multiple dynamic layers
	auto multiLayerSound = std::make_unique<OrchestraSound>(60, 84, 72);

	// Add 6 dynamic layers
	for (int i = 1; i <= 6; ++i)
	{
		juce::OwnedArray<juce::AudioBuffer<float>> buffers;
		auto									  *buffer = new juce::AudioBuffer<float>(2, 44100);
		buffers.add(buffer);

		Dynamics dyn = static_cast<Dynamics>(i);
		multiLayerSound->addDynamicLayer(dyn, std::move(buffers));
	}

	multiLayerSound->setArticulation(Articulation::sustain);

	int	  midiNote	 = 72;
	float velocity	 = 0.8f;
	int	  pitchWheel = 8192;

	// Start note
	EXPECT_NO_THROW(mVoice->startNote(midiNote, velocity, multiLayerSound.get(), pitchWheel));

	juce::AudioBuffer<float> outputBuffer(2, 512);
	outputBuffer.clear();

	// Test with different CC1 values to trigger crossfade
	mVoice->controllerMoved(1, 0);	 // Lowest dynamic
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));

	mVoice->controllerMoved(1, 64);	 // Middle dynamic
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));

	mVoice->controllerMoved(1, 127); // Highest dynamic
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));
}


TEST_F(OrchestraVoiceTest, RenderBlockBoundaryConditions)
{
	juce::AudioBuffer<float> outputBuffer(2, 1024);
	outputBuffer.clear();

	int	  midiNote	 = 72;
	float velocity	 = 0.8f;
	int	  pitchWheel = 8192;

	mVoice->startNote(midiNote, velocity, mSound.get(), pitchWheel);

	// Test rendering with different block sizes
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 1));	 // Single sample
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 64));	 // Small block
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));	 // Medium block
	EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 1024)); // Large block
}


TEST_F(OrchestraVoiceTest, MultipleNotesSequentially)
{
	juce::AudioBuffer<float> outputBuffer(2, 512);
	int						 pitchWheel = 8192;

	// Play multiple notes in sequence
	for (int note = 60; note <= 84; note += 12)
	{
		mVoice->startNote(note, 0.8f, mSound.get(), pitchWheel);
		EXPECT_NO_THROW(mVoice->renderNextBlock(outputBuffer, 0, 512));
		mVoice->stopNote(0.0f, false);
		outputBuffer.clear();
	}
}

} // namespace SamplerTests
