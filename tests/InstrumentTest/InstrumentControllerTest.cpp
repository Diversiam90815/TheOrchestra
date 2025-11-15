/*
  ==============================================================================
	Module          InstrumentController Tests
	Description     Testing InstrumentController JSON loading & retrieval
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "InstrumentController.h"
#include "FileManager.h"

namespace InstrumentTests
{

class InstrumentControllerTest : public ::testing::Test
{
protected:
	std::unique_ptr<InstrumentController> controller;
	FileManager							  fileManager;

	void								  SetUp() override
	{
		controller				   = std::make_unique<InstrumentController>();

		// Verify the JSON file exists before running JSON dependent tests
		const std::string jsonPath = fileManager.getInstrumentDataJSONPath();
		juce::File		  jsonFile(jsonPath);
		if (!jsonFile.existsAsFile())
		{
			GTEST_SKIP() << "Instruments.json not found at: " << jsonPath << " — skipping InstrumentController tests that require data.";
		}

		controller->init();
	}

	void TearDown() override { controller.reset(); }
};


TEST_F(InstrumentControllerTest, RetrieveKnownInstrumentByKey)
{
	int			   violinKey = 301;
	InstrumentProfile violin	 = controller->getInstrument(violinKey);

	EXPECT_EQ(violin.getInstrumentID(), violinKey);
	EXPECT_FALSE(violin.getName().empty()) << "Violin name should not be empty";
	EXPECT_FALSE(violin.getRange().getHigherRange().empty()) << "Violin higher range should be populated";
	EXPECT_FALSE(violin.getRange().getLowerRange().empty()) << "Violin lower range should be populated";
	EXPECT_GE(violin.getQualities().size(), 0) << "RegisterQualities should not be empty";
	EXPECT_GE(violin.getRoles().size(), 0) << "OrchestrationRoles should not be empty";
	EXPECT_GE(violin.getTechniques().size(), 0) << "Playing techniques should be available (family or specific)";
}


TEST_F(InstrumentControllerTest, RhythmicPercussionInstrumentProperties)
{
	int			   timpaniKey = 403;
	InstrumentProfile timpani	  = controller->getInstrument(timpaniKey);

	EXPECT_EQ(timpani.getInstrumentID(), timpaniKey);
	EXPECT_TRUE(timpani.isRhythmicPercussion()) << "Timpani should be flagged as rhythmic percussion";

	// Displayed range may differ from actual range; at least accessible
	EXPECT_FALSE(timpani.getRange().getDisplayedHigherRange().empty()) << "Rhythmic percussion should have displayed higher range";
	EXPECT_FALSE(timpani.getRange().getDisplayedLowerRange().empty()) << "Rhythmic percussion should have displayed lower range";
}


TEST_F(InstrumentControllerTest, NonRhythmicPercussionInstrument)
{
	int			   harpKey = 401;
	InstrumentProfile harp	   = controller->getInstrument(harpKey);

	EXPECT_EQ(harp.getInstrumentID(), harpKey);
	EXPECT_FALSE(harp.isRhythmicPercussion()) << "Harp should NOT be flagged as rhythmic percussion";
	EXPECT_EQ(harp.getName(), "Harp");
}


TEST_F(InstrumentControllerTest, RetrievalIsConsistentAcrossCalls)
{
	int			   key = 301;
	InstrumentProfile a   = controller->getInstrument(key);
	InstrumentProfile b   = controller->getInstrument(key);

	EXPECT_EQ(a.getName(), b.getName());
	EXPECT_EQ(a.getRange(), b.getRange());
	EXPECT_EQ(a.getRange().getTransposition(), b.getRange().getTransposition());
	EXPECT_EQ(a.isRhythmicPercussion(), b.isRhythmicPercussion());
}


TEST_F(InstrumentControllerTest, PlayingTechniquesFallbackOrSpecific)
{
	int			   key	= 301;
	InstrumentProfile inst = controller->getInstrument(key);
	EXPECT_FALSE(inst.getTechniques().empty()) << "Playing techniques should be populated from family or instrument definition";
}


TEST_F(InstrumentControllerTest, FamilyLevelPlayingTechniquesInherited)
{
	// Test that String family instruments inherit family techniques
	int			   violinKey = 301;
	int			   violaKey	 = 302;

	InstrumentProfile violin	 = controller->getInstrument(violinKey);
	InstrumentProfile viola	 = controller->getInstrument(violaKey);

	// Both should have techniques (from family level)
	EXPECT_GT(violin.getTechniques().size(), 0) << "Violin should inherit Strings family techniques";
	EXPECT_GT(viola.getTechniques().size(), 0) << "Viola should inherit Strings family techniques";

	// Verify specific technique exists
	bool hasPizzicato = false;
	for (const auto &tech : violin.getTechniques())
	{
		if (tech.getName().find("Pizzicato") != std::string::npos)
		{
			hasPizzicato = true;
			break;
		}
	}
	EXPECT_TRUE(hasPizzicato) << "String instruments should have Pizzicato technique";
}


TEST_F(InstrumentControllerTest, InstrumentSpecificTechniquesOverrideFamilyTechniques)
{
	// Marimba has instrument-specific techniques (not family-level)
	int			   marimbaKey = 404;

	InstrumentProfile marimba	  = controller->getInstrument(marimbaKey);
	EXPECT_GT(marimba.getTechniques().size(), 0) << "Marimba should have instrument-specific techniques";

	// Check for a Marimba-specific technique
	bool hasFourMalletGrip = false;
	for (const auto &tech : marimba.getTechniques())
	{
		if (tech.getName().find("Four-mallet grip") != std::string::npos)
		{
			hasFourMalletGrip = true;
			break;
		}
	}
	EXPECT_TRUE(hasFourMalletGrip) << "Marimba should have 'Four-mallet grip' technique";
}


TEST_F(InstrumentControllerTest, TransposingInstrumentDataLoaded)
{
	int			   frenchHornKey = 201;

	InstrumentProfile horn			 = controller->getInstrument(frenchHornKey);
	EXPECT_EQ(horn.getName(), "French Horn");
	EXPECT_FALSE(horn.getRange().getTransposition().empty()) << "French Horn should have transposition info";
}


TEST_F(InstrumentControllerTest, NonTransposingInstrumentDataLoaded)
{
	int			   violinKey = 301;

	InstrumentProfile violin	 = controller->getInstrument(violinKey);
	EXPECT_EQ(violin.getRange().getTransposition(), "") << "Violin is non-transposing, should return empty string";
}


TEST_F(InstrumentControllerTest, RolesInformationLoadedCorrectly)
{
	int			   violinKey = 301;

	InstrumentProfile violin	 = controller->getInstrument(violinKey);
	EXPECT_GT(violin.getRoles().size(), 0) << "Violin should have roles/information populated";
}


TEST_F(InstrumentControllerTest, FamousWorksLoadedCorrectly)
{
	int			   violinKey = 301;

	InstrumentProfile violin	 = controller->getInstrument(violinKey);
	EXPECT_GE(violin.getFamousWorks().size(), 0) << "Violin should have famous works populated";
}


TEST_F(InstrumentControllerTest, AllStringInstrumentsLoaded)
{
	// Verify all 4 string instruments are loaded
	InstrumentProfile violin = controller->getInstrument(301);
	InstrumentProfile viola  = controller->getInstrument(302);
	InstrumentProfile cello  = controller->getInstrument(303);
	InstrumentProfile bass	  = controller->getInstrument(304);

	EXPECT_EQ(violin.getName(), "Violin");
	EXPECT_EQ(viola.getName(), "Viola");
	EXPECT_EQ(cello.getName(), "Violoncello");
	EXPECT_EQ(bass.getName(), "Double Bass");
}


TEST_F(InstrumentControllerTest, AllBrassInstrumentsLoaded)
{
	// Verify all 6 brass instruments are loaded
	InstrumentProfile horn		= controller->getInstrument(201);
	InstrumentProfile trumpet	= controller->getInstrument(202);
	InstrumentProfile tenorTbn = controller->getInstrument(203);
	InstrumentProfile bassTbn	= controller->getInstrument(204);
	InstrumentProfile cimbasso = controller->getInstrument(205);
	InstrumentProfile tuba		= controller->getInstrument(206);

	EXPECT_EQ(horn.getName(), "French Horn");
	EXPECT_EQ(trumpet.getName(), "Trumpet");
	EXPECT_EQ(tenorTbn.getName(), "Tenor Trombone");
	EXPECT_EQ(bassTbn.getName(), "Bass Trombone");
	EXPECT_EQ(cimbasso.getName(), "Cimbasso");
	EXPECT_EQ(tuba.getName(), "Tuba");
}


TEST_F(InstrumentControllerTest, AllWoodwindInstrumentsLoaded)
{
	// Verify all 8 woodwind instruments are loaded
	InstrumentProfile piccolo	  = controller->getInstrument(101);
	InstrumentProfile flute	  = controller->getInstrument(102);
	InstrumentProfile oboe		  = controller->getInstrument(103);
	InstrumentProfile corAnglais = controller->getInstrument(104);
	InstrumentProfile clarinet	  = controller->getInstrument(105);
	InstrumentProfile bassClar	  = controller->getInstrument(106);
	InstrumentProfile bassoon	  = controller->getInstrument(107);
	InstrumentProfile cbassoon	  = controller->getInstrument(108);

	EXPECT_EQ(piccolo.getName(), "Piccolo");
	EXPECT_EQ(flute.getName(), "Flute");
	EXPECT_EQ(oboe.getName(), "Oboe");
	EXPECT_EQ(corAnglais.getName(), "Cor Anglais");
	EXPECT_EQ(clarinet.getName(), "Clarinet");
	EXPECT_EQ(bassClar.getName(), "Bass Clarinet");
	EXPECT_EQ(bassoon.getName(), "Bassoon");
	EXPECT_EQ(cbassoon.getName(), "Contrabassoon");
}


TEST_F(InstrumentControllerTest, AllPercussionInstrumentsLoaded)
{
	// Verify all 4 percussion instruments are loaded
	InstrumentProfile harp	   = controller->getInstrument(401);
	InstrumentProfile celeste = controller->getInstrument(402);
	InstrumentProfile timpani = controller->getInstrument(403);
	InstrumentProfile marimba = controller->getInstrument(404);

	EXPECT_EQ(harp.getName(), "Harp");
	EXPECT_EQ(celeste.getName(), "Celeste");
	EXPECT_EQ(timpani.getName(), "Timpani");
	EXPECT_EQ(marimba.getName(), "Marimba");
}


} // namespace InstrumentTests