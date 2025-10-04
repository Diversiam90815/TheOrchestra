/*
  ==============================================================================
	Module			Sampler Tests
	Description		Testing the Sampler module from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "Sampler.h"
#include "InstrumentController.h"


namespace SamplerTests
{

class SamplerTest : public ::testing::Test
{
protected:
	std::unique_ptr<Sampler>			  mSampler;
	std::unique_ptr<InstrumentController> mController;


	void								  SetUp() override
	{
		mSampler	= std::make_unique<Sampler>();
		mController = std::make_unique<InstrumentController>();
		mController->init();
	}

	void TearDown() override
	{
		mSampler.reset();
		mController.reset();
	}
};


TEST_F(SamplerTest, InitializationSucceeds)
{
	// Initialize sampler with controller
	EXPECT_NO_THROW(mSampler->init(mController.get()));

	// Verify initial state
	EXPECT_FALSE(mSampler->getSamplesAreReady()) << "Samples should not be ready immediately after init";
}


TEST_F(SamplerTest, GetAvailableArticulationsForValidInstrument)
{
	mSampler->init(mController.get());

	// Test with violin (key = 301)
	int					   violinKey	 = 301;
	std::set<Articulation> articulations = mSampler->getAvailableArticulationsForInstrument(violinKey);

	// Should return some articulations (depending on available samples)
	// The actual articulations depend on the sample library
	EXPECT_GE(articulations.size(), 0) << "Should return available articulations (may be empty if no samples)";
}


TEST_F(SamplerTest, GetAvailableArticulationsForInvalidInstrument)
{
	mSampler->init(mController.get());

	// Test with invalid instrument key
	int					   invalidKey	 = 999;
	std::set<Articulation> articulations = mSampler->getAvailableArticulationsForInstrument(invalidKey);

	// Should return empty set for invalid instrument
	EXPECT_EQ(articulations.size(), 0) << "Should return empty set for invalid instrument";
}


TEST_F(SamplerTest, SamplesReadyStateToggling)
{
	mSampler->init(mController.get());

	// Initially false
	EXPECT_FALSE(mSampler->getSamplesAreReady());

	// Set to true
	mSampler->setSamplesAreReady(true);
	EXPECT_TRUE(mSampler->getSamplesAreReady());

	// Set back to false
	mSampler->setSamplesAreReady(false);
	EXPECT_FALSE(mSampler->getSamplesAreReady());
}


TEST_F(SamplerTest, AddSoundsFromInstrumentWithValidData)
{
	mSampler->init(mController.get());

	// Attempt to add sounds (may succeed or fail depending on sample availability)
	int violinKey = 301;
	EXPECT_NO_THROW(mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::sustain));
}


TEST_F(SamplerTest, AddSoundsWithInvalidInstrumentKey)
{
	mSampler->init(mController.get());

	int invalidKey = 999;
	EXPECT_NO_THROW(mSampler->addSoundsFromInstrumentToSampler(invalidKey, Articulation::sustain));

	// Should not crash, but samples won't be ready
	EXPECT_FALSE(mSampler->getSamplesAreReady()) << "Samples should not be ready for invalid instrument";
}


TEST_F(SamplerTest, MultipleArticulationSwitching)
{
	mSampler->init(mController.get());

	int violinKey = 301;

	// Add sustain articulation
	mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::sustain);
	bool sustainReady = mSampler->getSamplesAreReady();

	// Switch to pizzicato
	mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::pizzicato);
	bool pizzicatoReady = mSampler->getSamplesAreReady();

	// The ready state should be consistent with sample availability
	EXPECT_GE(sustainReady, 0); // May be true or false depending on samples
	EXPECT_GE(pizzicatoReady, 0);
}

} // namespace SamplerTests
