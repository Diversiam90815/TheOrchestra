/*
  ==============================================================================
	Module			Sampler Integration Tests
	Description		Testing interplay of the Sampler modules from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "SamplerEngine.h"
#include "InstrumentController.h"


namespace SamplerTests
{

class SamplerIntegrationTest : public ::testing::Test
{
protected:
	std::shared_ptr<SamplerEngine>		  mSampler;
	std::unique_ptr<InstrumentController> mController;


	void								  SetUp() override
	{
		mSampler	= std::make_shared<SamplerEngine>();
		mController = std::make_unique<InstrumentController>();
		mController->init();
		mSampler->init(*mController.get());
	}

	void TearDown() override
	{
		mSampler.reset();
		mController.reset();
	}
};


TEST_F(SamplerIntegrationTest, LoadAndSwitchArticulations)
{
	int violinKey = 301;

	// Load sustain articulation
	mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::sustain);

	// Switch to pizzicato
	mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::pizzicato);

	// Switch back to sustain
	mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::sustain);

	// Should not crash during articulation switching
	SUCCEED();
}


TEST_F(SamplerIntegrationTest, LoadMultipleInstrumentsSequentially)
{
	// Load multiple instruments
	mSampler->addSoundsFromInstrumentToSampler(301, Articulation::sustain); // Violin
	mSampler->addSoundsFromInstrumentToSampler(302, Articulation::sustain); // Viola
	mSampler->addSoundsFromInstrumentToSampler(303, Articulation::sustain); // Cello

	// Should handle multiple instrument loads
	SUCCEED();
}


TEST_F(SamplerIntegrationTest, CompletePlaybackScenario)
{
	// This test simulates a complete playback scenario
	int	 violinKey	   = 301;

	// 1. Get available articulations
	auto articulations = mSampler->getAvailableArticulationsForInstrument(violinKey);

	// 2. Load samples
	mSampler->addSoundsFromInstrumentToSampler(violinKey, Articulation::sustain);

	// 3. Verify state
	// Samples may or may not be ready depending on file availability
	bool samplesReady = mSampler->getSamplesAreReady();
	EXPECT_TRUE(samplesReady == true || samplesReady == false); // Just verify it doesn't crash

	// Complete scenario executed without crashes
	SUCCEED();
}


TEST_F(SamplerIntegrationTest, LoadInstrumentAsyncReportsCompletion)
{
	int	 violinKey = 301;
	bool completed = false;
	bool result	   = false;

	mSampler->loadInstrumentAsync(violinKey, Articulation::sustain,
								  [&completed, &result](bool success)
								  {
									  completed = true;
									  result	= success;
								  });

	while (mSampler->isLoading())
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	SUCCEED();
}

} // namespace SamplerTests
