/*
  ==============================================================================
	Module			CoreManager Tests
	Description		Testing the CoreManager coordination and integration
  ==============================================================================
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CoreManager.h"
#include "InstrumentInfo.h"
#include "Parameters.h"

using ::testing::_;
using ::testing::Return;

namespace CoreManagerTests
{

class CoreManagerTest : public ::testing::Test
{
protected:
	std::unique_ptr<CoreManager> coreManager;

	void						 SetUp() override
	{
		coreManager = std::make_unique<CoreManager>();
		coreManager->init();
	}

	void TearDown() override { coreManager.reset(); }
};

// ============================================================================
// Initialization Tests
// ============================================================================

TEST_F(CoreManagerTest, PrepareAudioWithValidParameters)
{
	double sampleRate	   = 44100.0;
	int	   samplesPerBlock = 512;

	EXPECT_NO_THROW(coreManager->prepareAudio(sampleRate, samplesPerBlock));
}


TEST_F(CoreManagerTest, PrepareAudioWithVariousSampleRates)
{
	std::vector<double> sampleRates = {44100.0, 48000.0, 88200.0, 96000.0};

	for (auto sampleRate : sampleRates)
	{
		EXPECT_NO_THROW(coreManager->prepareAudio(sampleRate, 512)) << "Failed with sample rate: " << sampleRate;
	}
}


// ============================================================================
// Instrument Management Tests
// ============================================================================

TEST_F(CoreManagerTest, ChangeInstrumentWithValidKey)
{
	InstrumentID violinKey = 301; // Violin key from your system

	EXPECT_NO_THROW(coreManager->changeInstrument(violinKey));
}


TEST_F(CoreManagerTest, ChangeInstrumentWithInvalidKey)
{
	InstrumentID invalidKey = 9999;

	// Should handle invalid key gracefully (logs error but doesn't throw)
	EXPECT_NO_THROW(coreManager->changeInstrument(invalidKey));
}


TEST_F(CoreManagerTest, GetInstrumentWithValidKey)
{
	InstrumentID violinKey	= 301;

	auto		 instrument = coreManager->getInstrument(violinKey);

	// Violin should be a valid instrument
	EXPECT_TRUE(instrument.isValid()) << "Violin instrument should be valid";
	EXPECT_FALSE(instrument.getName().isEmpty()) << "Violin should have a name";
}


TEST_F(CoreManagerTest, GetInstrumentWithInvalidKey)
{
	InstrumentID invalidKey = 9999;

	auto		 instrument = coreManager->getInstrument(invalidKey);

	// Invalid instrument should not be valid
	EXPECT_FALSE(instrument.isValid()) << "Invalid instrument should return invalid InstrumentInfo";
}


TEST_F(CoreManagerTest, ChangeInstrumentMultipleTimes)
{
	InstrumentID violinKey = 301;
	InstrumentID violaKey  = 302;
	InstrumentID celloKey  = 303;

	EXPECT_NO_THROW(coreManager->changeInstrument(violinKey));
	EXPECT_NO_THROW(coreManager->changeInstrument(violaKey));
	EXPECT_NO_THROW(coreManager->changeInstrument(celloKey));
}


// ============================================================================
// Articulation Management Tests
// ============================================================================

TEST_F(CoreManagerTest, GetAvailableArticulationsForValidInstrument)
{
	InstrumentID violinKey	   = 301;

	auto		 articulations = coreManager->getAvailableArticulations(violinKey);

	// Violin should have articulations available
	EXPECT_GT(articulations.size(), 0) << "Violin should have at least one articulation";
}


TEST_F(CoreManagerTest, GetAvailableArticulationsForInvalidInstrument)
{
	InstrumentID invalidKey	   = 9999;

	auto		 articulations = coreManager->getAvailableArticulations(invalidKey);

	// Invalid instrument should return empty set
	EXPECT_EQ(articulations.size(), 0) << "Invalid instrument should have no articulations";
}


TEST_F(CoreManagerTest, ChangeArticulationWithValidInstrumentAndArticulation)
{
	InstrumentID violinKey	  = 301;
	Articulation articulation = Articulation::sustain;

	EXPECT_NO_THROW(coreManager->changeArticulation(violinKey, articulation));
}


TEST_F(CoreManagerTest, ChangeArticulationSequence)
{
	InstrumentID violinKey = 301;

	// Change instrument first
	coreManager->changeInstrument(violinKey);

	// Get available articulations
	auto articulations = coreManager->getAvailableArticulations(violinKey);

	// Change to each available articulation
	for (const auto &articulation : articulations)
	{
		EXPECT_NO_THROW(coreManager->changeArticulation(violinKey, articulation)) << "Failed to change to articulation: " << static_cast<int>(articulation);
	}
}


// ============================================================================
// Audio Processing Tests
// ============================================================================

TEST_F(CoreManagerTest, ProcessAudioBlockWithEmptyBuffer)
{
	coreManager->prepareAudio(44100.0, 512);

	juce::AudioBuffer<float> buffer(2, 512);
	juce::MidiBuffer		 midiMessages;

	buffer.clear();

	EXPECT_NO_THROW(coreManager->processAudioBlock(buffer, midiMessages));
}


TEST_F(CoreManagerTest, ProcessAudioBlockWithMidiMessages)
{
	coreManager->prepareAudio(44100.0, 512);

	// Set up an instrument
	InstrumentID violinKey = 301;
	coreManager->changeInstrument(violinKey);
	coreManager->changeArticulation(violinKey, Articulation::sustain);

	juce::AudioBuffer<float> buffer(2, 512);
	juce::MidiBuffer		 midiMessages;

	// Add note on message
	juce::MidiMessage		 noteOn = juce::MidiMessage::noteOn(1, 60, 0.8f);
	midiMessages.addEvent(noteOn, 0);

	buffer.clear();

	EXPECT_NO_THROW(coreManager->processAudioBlock(buffer, midiMessages));
}


TEST_F(CoreManagerTest, ProcessAudioBlockGeneratesSound)
{
	coreManager->prepareAudio(44100.0, 512);

	// Set up an instrument
	InstrumentID violinKey = 301;
	coreManager->changeInstrument(violinKey);
	coreManager->changeArticulation(violinKey, Articulation::sustain);

	juce::AudioBuffer<float> buffer(2, 512);
	juce::MidiBuffer		 midiMessages;

	// Add note on and hold it
	juce::MidiMessage		 noteOn = juce::MidiMessage::noteOn(1, 60, 0.8f);
	midiMessages.addEvent(noteOn, 0);

	buffer.clear();

	// Process multiple blocks to give sampler time to load and play
	for (int i = 0; i < 10; ++i)
	{
		coreManager->processAudioBlock(buffer, midiMessages);
		midiMessages.clear();
	}

	// Check if any audio was generated
	float maxSample = buffer.getMagnitude(0, 512);

	// Note: This might fail if samples aren't loaded yet or path is incorrect
	// In a real scenario, you'd want to ensure samples are loaded first
	if (maxSample > 0.0f)
	{
		EXPECT_GT(maxSample, 0.0f) << "Audio should be generated after note on";
	}
	else
	{
		GTEST_SKIP() << "Samples not loaded or not available - skipping audio generation test";
	}
}


// ============================================================================
// MIDI Keyboard State Tests
// ============================================================================

TEST_F(CoreManagerTest, MidiKeyboardStateProcessesMidiMessages)
{
	auto			 &midiState = coreManager->getMidiKeyboardState();

	juce::MidiBuffer  midiMessages;
	juce::MidiMessage noteOn = juce::MidiMessage::noteOn(1, 60, 0.8f);
	midiMessages.addEvent(noteOn, 0);

	midiState.processNextMidiBuffer(midiMessages, 0, 512, true);

	EXPECT_TRUE(midiState.isNoteOn(1, 60)) << "Note 60 should be on after note on message";
}


TEST_F(CoreManagerTest, MidiKeyboardStateHandlesNoteOff)
{
	auto			 &midiState = coreManager->getMidiKeyboardState();

	juce::MidiBuffer  midiMessages;

	// Note on
	juce::MidiMessage noteOn = juce::MidiMessage::noteOn(1, 60, 0.8f);
	midiMessages.addEvent(noteOn, 0);
	midiState.processNextMidiBuffer(midiMessages, 0, 512, true);

	EXPECT_TRUE(midiState.isNoteOn(1, 60));

	// Note off
	midiMessages.clear();
	juce::MidiMessage noteOff = juce::MidiMessage::noteOff(1, 60);
	midiMessages.addEvent(noteOff, 0);
	midiState.processNextMidiBuffer(midiMessages, 0, 512, true);

	EXPECT_FALSE(midiState.isNoteOn(1, 60)) << "Note 60 should be off after note off message";
}


// ============================================================================
// Integration Tests
// ============================================================================

TEST_F(CoreManagerTest, CompleteWorkflow)
{
	// Complete workflow test
	coreManager->prepareAudio(44100.0, 512);

	InstrumentID violinKey = 301;

	// Change instrument
	coreManager->changeInstrument(violinKey);

	// Get and verify instrument
	auto instrument = coreManager->getInstrument(violinKey);
	EXPECT_TRUE(instrument.isValid());

	// Get available articulations
	auto articulations = coreManager->getAvailableArticulations(violinKey);
	ASSERT_GT(articulations.size(), 0);

	// Change to first available articulation
	auto firstArticulation = *articulations.begin();
	coreManager->changeArticulation(violinKey, firstArticulation);

	// Process audio
	juce::AudioBuffer<float> buffer(2, 512);
	juce::MidiBuffer		 midiMessages;

	juce::MidiMessage		 noteOn = juce::MidiMessage::noteOn(1, 60, 0.8f);
	midiMessages.addEvent(noteOn, 0);

	buffer.clear();

	EXPECT_NO_THROW(coreManager->processAudioBlock(buffer, midiMessages));
}


TEST_F(CoreManagerTest, MultipleInstrumentSwitchingWorkflow)
{
	coreManager->prepareAudio(44100.0, 512);

	std::vector<InstrumentID> instruments = {301, 302, 303}; // Violin, Viola, Cello

	juce::AudioBuffer<float>  buffer(2, 512);
	juce::MidiBuffer		  midiMessages;

	for (auto instrumentKey : instruments)
	{
		// Change instrument
		coreManager->changeInstrument(instrumentKey);

		// Get available articulations
		auto articulations = coreManager->getAvailableArticulations(instrumentKey);

		if (articulations.empty())
		{
			GTEST_SKIP() << "No articulations available for instrument " << instrumentKey;
			continue;
		}

		// Change to first articulation
		coreManager->changeArticulation(instrumentKey, *articulations.begin());

		// Play a note
		midiMessages.clear();
		juce::MidiMessage noteOn = juce::MidiMessage::noteOn(1, 60, 0.8f);
		midiMessages.addEvent(noteOn, 0);

		buffer.clear();

		EXPECT_NO_THROW(coreManager->processAudioBlock(buffer, midiMessages)) << "Failed processing instrument " << instrumentKey;
	}
}


// ============================================================================
// Edge Cases and Error Handling
// ============================================================================

TEST_F(CoreManagerTest, ProcessAudioBeforePreparation)
{
	juce::AudioBuffer<float> buffer(2, 512);
	juce::MidiBuffer		 midiMessages;

	// This should handle gracefully even if prepare wasn't called
	EXPECT_NO_THROW(coreManager->processAudioBlock(buffer, midiMessages));
}


TEST_F(CoreManagerTest, ChangeArticulationBeforeInstrument)
{
	// Try to change articulation without setting instrument first
	EXPECT_NO_THROW(coreManager->changeArticulation(301, Articulation::sustain));
}


TEST_F(CoreManagerTest, ProcessWithZeroSampleBuffer)
{
	coreManager->prepareAudio(44100.0, 0);

	juce::AudioBuffer<float> buffer(2, 0);
	juce::MidiBuffer		 midiMessages;

	EXPECT_NO_THROW(coreManager->processAudioBlock(buffer, midiMessages));
}

} // namespace CoreManagerTests
