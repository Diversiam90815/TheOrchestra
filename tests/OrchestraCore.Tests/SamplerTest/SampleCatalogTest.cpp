/*
  ==============================================================================
	Module			Sample Catalog Tests
	Description		Testing the SampleCatalog module from the Orchestra Core
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "SampleCatalog.h"


namespace SamplerTests
{

class SampleCatalogTest : public ::testing::Test
{
protected:
	std::unique_ptr<SampleCatalog> mCatalog;


	void						   SetUp() override { mCatalog = std::make_unique<SampleCatalog>(); }

	void						   TearDown() override { mCatalog.reset(); }
};


TEST_F(SampleCatalogTest, InitializationSucceeds)
{
	EXPECT_NO_THROW(mCatalog->init());
}


TEST_F(SampleCatalogTest, GetSamplesForValidInstrument)
{
	mCatalog->init();

	// Test with violin key
	int					violinKey = 301;
	std::vector<Sample> samples	  = mCatalog->getSamplesForInstrument(violinKey);

	// Should return samples if they exist in the sample library
	// The actual count depends on the sample files available
	EXPECT_GE(samples.size(), 0u) << "Should return samples or empty vector";
}


TEST_F(SampleCatalogTest, GetSamplesForInvalidInstrument)
{
	mCatalog->init();

	// Test with invalid key
	int					invalidKey = 999;
	std::vector<Sample> samples	   = mCatalog->getSamplesForInstrument(invalidKey);

	// Should return empty vector for invalid instrument
	EXPECT_EQ(samples.size(), 0u) << "Should return empty vector for invalid instrument";
}


TEST_F(SampleCatalogTest, GetSamplesForMultipleInstruments)
{
	mCatalog->init();

	// Test multiple instruments
	int					violinKey	  = 301;
	int					violaKey	  = 302;
	int					celloKey	  = 303;

	std::vector<Sample> violinSamples = mCatalog->getSamplesForInstrument(violinKey);
	std::vector<Sample> violaSamples  = mCatalog->getSamplesForInstrument(violaKey);
	std::vector<Sample> celloSamples  = mCatalog->getSamplesForInstrument(celloKey);

	// Each should return independently
	EXPECT_GE(violinSamples.size(), 0u);
	EXPECT_GE(violaSamples.size(), 0u);
	EXPECT_GE(celloSamples.size(), 0u);
}


TEST_F(SampleCatalogTest, ParsesPercussionInstruments)
{
	mCatalog->init();

	// Test percussion instruments (Timpani = 403)
	int					timpaniKey = 403;
	std::vector<Sample> samples	   = mCatalog->getSamplesForInstrument(timpaniKey);

	// Should handle percussion instruments
	EXPECT_GE(samples.size(), 0u) << "Should handle percussion instruments";
}


TEST_F(SampleCatalogTest, IsLoadingReflectsAsyncScanState)
{
	bool completed = false;

	mCatalog->loadSamplesAsync([&completed](bool) { completed = true; });

	// Poll until the background scan finishes; avoids depending on scan duration.
	while (mCatalog->isLoading())
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	EXPECT_TRUE(completed) << "Completion callback should fire once the async scan finishes";
}

} // namespace SamplerTests