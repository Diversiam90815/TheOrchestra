/*
  ==============================================================================
	Module			Orchestra Sound Tests
	Description		Testing the Orchestra Sound module from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "OrchestraSound.h"

namespace SamplerTests
{

class OrchestraSoundTest : public ::testing::Test
{
protected:
	std::unique_ptr<OrchestraSound> mSound;

	void							SetUp() override
	{
		// Create a sound with note range C3 (60) to C5 (84), root note C4 (72)
		mSound = std::make_unique<OrchestraSound>(60, 84, 72);
	}

	void TearDown() override { mSound.reset(); }
};


TEST_F(OrchestraSoundTest, ConstructorSetsCorrectValues)
{
	// Verify root note
	EXPECT_EQ(mSound->getRootNote(), 72) << "Root note should be C4 (72)";
}


TEST_F(OrchestraSoundTest, AppliesToNoteWithinRange)
{
	// Test notes within range
	EXPECT_TRUE(mSound->appliesToNote(60)) << "Should apply to lowest note in range";
	EXPECT_TRUE(mSound->appliesToNote(72)) << "Should apply to root note";
	EXPECT_TRUE(mSound->appliesToNote(84)) << "Should apply to highest note in range";
	EXPECT_TRUE(mSound->appliesToNote(70)) << "Should apply to note within range";
}


TEST_F(OrchestraSoundTest, AppliesToNoteOutsideRange)
{
	// Test notes outside range
	EXPECT_FALSE(mSound->appliesToNote(59)) << "Should not apply to note below range";
	EXPECT_FALSE(mSound->appliesToNote(85)) << "Should not apply to note above range";
	EXPECT_FALSE(mSound->appliesToNote(0)) << "Should not apply to very low note";
	EXPECT_FALSE(mSound->appliesToNote(127)) << "Should not apply to very high note";
}


TEST_F(OrchestraSoundTest, AppliesToChannelAlwaysReturnsTrue)
{
	// Channel check is not implemented, should always return true
	EXPECT_TRUE(mSound->appliesToChannel(1));
	EXPECT_TRUE(mSound->appliesToChannel(10));
	EXPECT_TRUE(mSound->appliesToChannel(16));
}


TEST_F(OrchestraSoundTest, ArticulationSetAndGet)
{
	// Default articulation should be sustain
	EXPECT_EQ(mSound->getArticulation(), Articulation::sustain);

	// Set to pizzicato
	mSound->setArticulation(Articulation::pizzicato);
	EXPECT_EQ(mSound->getArticulation(), Articulation::pizzicato);

	// Set to staccato
	mSound->setArticulation(Articulation::staccato);
	EXPECT_EQ(mSound->getArticulation(), Articulation::staccato);
}


TEST_F(OrchestraSoundTest, AddDynamicLayerWithEmptySamples)
{
	juce::OwnedArray<juce::AudioBuffer<float>> emptyBuffers;

	// Add empty dynamic layer
	EXPECT_NO_THROW(mSound->addDynamicLayer(Dynamics::mezzoForte, std::move(emptyBuffers)));

	// Verify layer was added
	EXPECT_EQ(mSound->dynamicLayers.size(), 1) << "Should have one dynamic layer";
}


TEST_F(OrchestraSoundTest, AddMultipleDynamicLayers)
{
	// Add multiple dynamic layers
	for (int i = 0; i < 6; ++i)
	{
		juce::OwnedArray<juce::AudioBuffer<float>> buffers;
		auto									  *buffer = new juce::AudioBuffer<float>(2, 1024);
		buffers.add(buffer);

		Dynamics dyn = static_cast<Dynamics>(i + 1);
		mSound->addDynamicLayer(dyn, std::move(buffers));
	}

	// Verify all layers were added
	EXPECT_EQ(mSound->dynamicLayers.size(), 6) << "Should have six dynamic layers";
}


TEST_F(OrchestraSoundTest, DynamicLayersStoreCorrectValues)
{
	juce::OwnedArray<juce::AudioBuffer<float>> buffers;
	auto									  *buffer = new juce::AudioBuffer<float>(2, 512);
	buffers.add(buffer);

	mSound->addDynamicLayer(Dynamics::fortissimo, std::move(buffers));

	// Verify the dynamic value
	EXPECT_EQ(mSound->dynamicLayers[0]->dynamicValue, Dynamics::fortissimo);
	EXPECT_EQ(mSound->dynamicLayers[0]->roundRobinSamples.size(), 1);
}


} // namespace SamplerTests
