/*
  ==============================================================================
	Module			Articulation Voice Tests
	Description		Testing the ArticulationVoice module from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "ArticulationVoice.h"
#include "SamplerTypes.h"


namespace SamplerTests
{

class ArticulationVoiceTest : public ::testing::Test
{
protected:
	std::unique_ptr<ArticulationVoice> mVoice;
	std::unique_ptr<SampleSound>	   mSound;


	void							   SetUp() override
	{
		mVoice = std::make_unique<ArticulationVoice>();

		// Create a test sound with one dynamic layer
		mSound = std::make_unique<SampleSound>(60, 84, 72);

		// Add a dynamic layer with sample data
		RoundRobinBuffers buffers;
		buffers.push_back(std::make_unique<juce::AudioBuffer<float>>(2, 44100)); // 1 second at 44.1kHz

		mSound->addDynamicLayer(Dynamics::mezzoForte, std::move(buffers));
		mSound->setArticulation(Articulation::sustain);
	}

	void TearDown() override
	{
		mVoice.reset();
		mSound.reset();
	}
};


TEST_F(ArticulationVoiceTest, CanPlayOrchestraSound)
{
	// Should be able to play SampleSound
	EXPECT_TRUE(mVoice->canPlaySound(mSound.get())) << "Voice should be able to play SampleSound";
}


TEST_F(ArticulationVoiceTest, CannotPlayNullSound)
{
	// Should not be able to play null sound
	EXPECT_FALSE(mVoice->canPlaySound(nullptr)) << "Voice should not play null sound";
}


TEST_F(ArticulationVoiceTest, StartNoteInitializesVoice)
{
	int	  midiNote	 = 72;	 // C4
	float velocity	 = 0.8f;
	int	  pitchWheel = 8192; // Center position

	// Start the note
	EXPECT_NO_THROW(mVoice->startNote(midiNote, velocity, mSound.get(), pitchWheel));

	// Voice should now be in playing state
	// (This is internal state, but we can test by checking if renderNextBlock works)
}


TEST_F(ArticulationVoiceTest, StartNoteWithDifferentVelocities)
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


TEST_F(ArticulationVoiceTest, StopNoteWithoutTailOff)
{
	int midiNote   = 72;
	int pitchWheel = 8192;

	mVoice->startNote(midiNote, 0.8f, mSound.get(), pitchWheel);

	// Stop without tail-off
	EXPECT_NO_THROW(mVoice->stopNote(0.0f, false));
}


TEST_F(ArticulationVoiceTest, StopNoteWithTailOff)
{
	int midiNote   = 72;
	int pitchWheel = 8192;

	mVoice->startNote(midiNote, 0.8f, mSound.get(), pitchWheel);

	// Stop with tail-off
	EXPECT_NO_THROW(mVoice->stopNote(0.5f, true));
}


TEST_F(ArticulationVoiceTest, ControllerMovedCC1)
{
	// Set mCC1 (modulation) to various values
	EXPECT_NO_THROW(mVoice->controllerMoved(1, 0));
	EXPECT_NO_THROW(mVoice->controllerMoved(1, 64));
	EXPECT_NO_THROW(mVoice->controllerMoved(1, 127));
}


TEST_F(ArticulationVoiceTest, ControllerMovedCC11)
{
	// Set mCC11 (expression) to various values
	EXPECT_NO_THROW(mVoice->controllerMoved(11, 0));
	EXPECT_NO_THROW(mVoice->controllerMoved(11, 64));
	EXPECT_NO_THROW(mVoice->controllerMoved(11, 127));
}


TEST_F(ArticulationVoiceTest, PitchWheelMovedDoesNotCrash)
{
	// Pitch wheel is not implemented but should not crash
	EXPECT_NO_THROW(mVoice->pitchWheelMoved(0));
	EXPECT_NO_THROW(mVoice->pitchWheelMoved(8192));
	EXPECT_NO_THROW(mVoice->pitchWheelMoved(16383));
}


TEST_F(ArticulationVoiceTest, RenderNextBlockWithoutStartingNote)
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


TEST_F(ArticulationVoiceTest, RenderNextBlockAfterStartingNote)
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


TEST_F(ArticulationVoiceTest, ShortArticulationBehavior)
{
	// Create a sound with short articulation
	auto			  shortSound = std::make_unique<SampleSound>(60, 84, 72);

	RoundRobinBuffers buffers;
	buffers.push_back(std::make_unique<juce::AudioBuffer<float>>(2, 44100));

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


TEST_F(ArticulationVoiceTest, PitchShiftingAtDifferentNotes)
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

} // namespace SamplerTests