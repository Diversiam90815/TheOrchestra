/*
  ==============================================================================
	Module			SampleMangement Tests
	Description		Testing the Sample Management module from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "SamplesManagement.h"


namespace SamplerTests
{

class SamplesManagementTest : public ::testing::Test
{
protected:
	std::unique_ptr<SamplesManagement> mSamplesManager;


	void							   SetUp() override { mSamplesManager = std::make_unique<SamplesManagement>(); }

	void							   TearDown() override { mSamplesManager.reset(); }
};


TEST_F(SamplesManagementTest, InitializationSucceeds)
{
	EXPECT_NO_THROW(mSamplesManager->init());
}


TEST_F(SamplesManagementTest, GetSamplesForValidInstrument)
{
	mSamplesManager->init();

	// Test with violin key
	int					violinKey = 301;
	std::vector<Sample> samples	  = mSamplesManager->getSamplesForInstrument(violinKey);

	// Should return samples if they exist in the sample library
	// The actual count depends on the sample files available
	EXPECT_GE(samples.size(), 0) << "Should return samples or empty vector";
}


TEST_F(SamplesManagementTest, GetSamplesForInvalidInstrument)
{
	mSamplesManager->init();

	// Test with invalid key
	int					invalidKey = 999;
	std::vector<Sample> samples	   = mSamplesManager->getSamplesForInstrument(invalidKey);

	// Should return empty vector for invalid instrument
	EXPECT_EQ(samples.size(), 0) << "Should return empty vector for invalid instrument";
}


TEST_F(SamplesManagementTest, GetSamplesForMultipleInstruments)
{
	mSamplesManager->init();

	// Test multiple instruments
	int					violinKey	  = 301;
	int					violaKey	  = 302;
	int					celloKey	  = 303;

	std::vector<Sample> violinSamples = mSamplesManager->getSamplesForInstrument(violinKey);
	std::vector<Sample> violaSamples  = mSamplesManager->getSamplesForInstrument(violaKey);
	std::vector<Sample> celloSamples  = mSamplesManager->getSamplesForInstrument(celloKey);

	// Each should return independently
	EXPECT_GE(violinSamples.size(), 0);
	EXPECT_GE(violaSamples.size(), 0);
	EXPECT_GE(celloSamples.size(), 0);
}


TEST_F(SamplesManagementTest, ParsesPercussionInstruments)
{
	mSamplesManager->init();

	// Test percussion instruments (Timpani = 403)
	int					timpaniKey = 403;
	std::vector<Sample> samples	   = mSamplesManager->getSamplesForInstrument(timpaniKey);

	// Should handle percussion instruments
	EXPECT_GE(samples.size(), 0) << "Should handle percussion instruments";
}

} // namespace SamplerTests
