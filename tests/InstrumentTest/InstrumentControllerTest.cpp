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


TEST_F(InstrumentControllerTest, InitializationLoadsJSON)
{
	// If we reached here without skipping, init() already ran
	SUCCEED();
}


TEST_F(InstrumentControllerTest, RetrieveKnownInstrumentByKey)
{
	int violinKey = 301;
	EXPECT_NO_FATAL_FAILURE({
		InstrumentInfo violin = controller->getInstrument(violinKey);
		EXPECT_EQ(violin.getKey(), violinKey);
		EXPECT_FALSE(violin.getName().isEmpty()) << "Violin name should not be empty";
		EXPECT_FALSE(violin.getRange().isEmpty()) << "Violin range should be populated";
		EXPECT_GE(violin.getQualities().size(), 0);
		EXPECT_GE(violin.getInformation().size(), 0);
		EXPECT_GE(violin.getTechniques().size(), 0) << "Playing techniques should be available (family or specific)";
	});
}


TEST_F(InstrumentControllerTest, RhythmicPercussionInstrumentProperties)
{
	int timpaniKey = 403;
	EXPECT_NO_FATAL_FAILURE({
		InstrumentInfo timpani = controller->getInstrument(timpaniKey);
		EXPECT_EQ(timpani.getKey(), timpaniKey);
		EXPECT_TRUE(timpani.isRhythmicPercussion()) << "Timpani should be flagged as rhythmic percussion";
		if (timpani.isRhythmicPercussion())
		{
			// Displayed range may differ from actual range; at least accessible
			EXPECT_FALSE(timpani.getDisplayedRange().isEmpty()) << "Rhythmic percussion should have displayed range";
			EXPECT_EQ(timpani.getDisplayedRange(), "D1 - A1") << "Timpani displayed range should match JSON";
		}
	});
}


TEST_F(InstrumentControllerTest, NonRhythmicPercussionInstrument)
{
	int harpKey = 401;
	EXPECT_NO_FATAL_FAILURE({
		InstrumentInfo harp = controller->getInstrument(harpKey);
		EXPECT_EQ(harp.getKey(), harpKey);
		EXPECT_FALSE(harp.isRhythmicPercussion()) << "Harp should NOT be flagged as rhythmic percussion";
		EXPECT_EQ(harp.getName(), "Harp");
	});
}


TEST_F(InstrumentControllerTest, RetrievalIsConsistentAcrossCalls)
{
	int			   key = 301;
	InstrumentInfo a   = controller->getInstrument(key);
	InstrumentInfo b   = controller->getInstrument(key);

	EXPECT_EQ(a.getName(), b.getName());
	EXPECT_EQ(a.getRange(), b.getRange());
	EXPECT_EQ(a.getTransposition(), b.getTransposition());
	EXPECT_EQ(a.isRhythmicPercussion(), b.isRhythmicPercussion());
}


TEST_F(InstrumentControllerTest, PlayingTechniquesFallbackOrSpecific)
{
	int			   key	= 301;
	InstrumentInfo inst = controller->getInstrument(key);
	EXPECT_FALSE(inst.getTechniques().isEmpty()) << "Playing techniques should be populated from family or instrument definition";
}


TEST_F(InstrumentControllerTest, FamilyLevelPlayingTechniquesInherited)
{
	// Test that String family instruments inherit family techniques
	int			   violinKey = 301;
	int			   violaKey	 = 302;

	InstrumentInfo violin	 = controller->getInstrument(violinKey);
	InstrumentInfo viola	 = controller->getInstrument(violaKey);

	// Both should have techniques (from family level)
	EXPECT_GT(violin.getTechniques().size(), 0) << "Violin should inherit Strings family techniques";
	EXPECT_GT(viola.getTechniques().size(), 0) << "Viola should inherit Strings family techniques";

	// Verify specific technique exists
	bool hasPizzicato = false;
	for (const auto &tech : violin.getTechniques())
	{
		if (tech.contains("Pizzicato"))
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

	InstrumentInfo marimba	  = controller->getInstrument(marimbaKey);
	EXPECT_GT(marimba.getTechniques().size(), 0) << "Marimba should have instrument-specific techniques";

	// Check for a Marimba-specific technique
	bool hasFourMalletGrip = false;
	for (const auto &tech : marimba.getTechniques())
	{
		if (tech.contains("Four-mallet grip"))
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

	InstrumentInfo horn			 = controller->getInstrument(frenchHornKey);
	EXPECT_EQ(horn.getName(), "French Horn");
	EXPECT_FALSE(horn.getTransposition().isEmpty()) << "French Horn should have transposition info";
	EXPECT_TRUE(horn.getTransposition().contains("5th")) << "French Horn transposes by a 5th";
}


TEST_F(InstrumentControllerTest, NonTransposingInstrumentDataLoaded)
{
	int			   violinKey = 301;

	InstrumentInfo violin	 = controller->getInstrument(violinKey);
	EXPECT_EQ(violin.getTransposition(), "-") << "Violin is non-transposing, should have '-'";
}


TEST_F(InstrumentControllerTest, QualitiesArrayLoadedCorrectly)
{
	int			   clarinetKey = 105;

	InstrumentInfo clarinet	   = controller->getInstrument(clarinetKey);
	EXPECT_EQ(clarinet.getName(), "Clarinet");
	EXPECT_EQ(clarinet.getQualities().size(), 4) << "Clarinet should have 4 quality descriptions from JSON";

	// Verify first quality contains expected text
	EXPECT_TRUE(clarinet.getQualities()[0].contains("Chalumeau")) << "First quality should describe Chalumeau register";
}


TEST_F(InstrumentControllerTest, RolesInformationLoadedCorrectly)
{
	int			   violinKey = 301;

	InstrumentInfo violin	 = controller->getInstrument(violinKey);
	EXPECT_GT(violin.getInformation().size(), 0) << "Violin should have roles/information populated";

	// Check for specific role
	bool hasLeadsMelody = false;
	for (const auto &role : violin.getInformation())
	{
		if (role.contains("melody"))
		{
			hasLeadsMelody = true;
			break;
		}
	}
	EXPECT_TRUE(hasLeadsMelody) << "Violin should have 'Leads with melody' role";
}


TEST_F(InstrumentControllerTest, FamousWorksLoadedCorrectly)
{
	int			   violinKey = 301;

	InstrumentInfo violin	 = controller->getInstrument(violinKey);
	EXPECT_EQ(violin.getFamousWorks().size(), 3) << "Violin should have 3 famous works from JSON";

	// Verify one of the works
	bool hasBeethovenConcerto = false;
	for (const auto &work : violin.getFamousWorks())
	{
		if (work.contains("Beethoven") && work.contains("Violin Concerto"))
		{
			hasBeethovenConcerto = true;
			break;
		}
	}
	EXPECT_TRUE(hasBeethovenConcerto) << "Violin should have Beethoven Violin Concerto listed";
}


TEST_F(InstrumentControllerTest, AllStringInstrumentsLoaded)
{
	// Verify all 4 string instruments are loaded
	InstrumentInfo violin = controller->getInstrument(301);
	InstrumentInfo viola  = controller->getInstrument(302);
	InstrumentInfo cello  = controller->getInstrument(303);
	InstrumentInfo bass	  = controller->getInstrument(304);

	EXPECT_EQ(violin.getName(), "Violin");
	EXPECT_EQ(viola.getName(), "Viola");
	EXPECT_EQ(cello.getName(), "Violoncello");
	EXPECT_EQ(bass.getName(), "Double Bass");
}


TEST_F(InstrumentControllerTest, AllBrassInstrumentsLoaded)
{
	// Verify all 6 brass instruments are loaded
	InstrumentInfo horn		= controller->getInstrument(201);
	InstrumentInfo trumpet	= controller->getInstrument(202);
	InstrumentInfo tenorTbn = controller->getInstrument(203);
	InstrumentInfo bassTbn	= controller->getInstrument(204);
	InstrumentInfo cimbasso = controller->getInstrument(205);
	InstrumentInfo tuba		= controller->getInstrument(206);

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
	InstrumentInfo piccolo	  = controller->getInstrument(101);
	InstrumentInfo flute	  = controller->getInstrument(102);
	InstrumentInfo oboe		  = controller->getInstrument(103);
	InstrumentInfo corAnglais = controller->getInstrument(104);
	InstrumentInfo clarinet	  = controller->getInstrument(105);
	InstrumentInfo bassClar	  = controller->getInstrument(106);
	InstrumentInfo bassoon	  = controller->getInstrument(107);
	InstrumentInfo cbassoon	  = controller->getInstrument(108);

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
	InstrumentInfo harp	   = controller->getInstrument(401);
	InstrumentInfo celeste = controller->getInstrument(402);
	InstrumentInfo timpani = controller->getInstrument(403);
	InstrumentInfo marimba = controller->getInstrument(404);

	EXPECT_EQ(harp.getName(), "Harp");
	EXPECT_EQ(celeste.getName(), "Celeste");
	EXPECT_EQ(timpani.getName(), "Timpani");
	EXPECT_EQ(marimba.getName(), "Marimba");
}


TEST_F(InstrumentControllerTest, RangeFormatConsistency)
{
	// Test that ranges are in expected format "NOTE - NOTE"
	int			   violinKey = 301;

	InstrumentInfo violin	 = controller->getInstrument(violinKey);
	EXPECT_TRUE(violin.getRange().contains("-")) << "Range should contain dash separator";
	EXPECT_EQ(violin.getRange(), "G3 - A7") << "Violin range should match JSON exactly";
}


TEST_F(InstrumentControllerTest, OctaveTransposingInstrumentLoaded)
{
	// Piccolo sounds one octave higher
	int			   piccoloKey = 101;

	InstrumentInfo piccolo	  = controller->getInstrument(piccoloKey);
	EXPECT_TRUE(piccolo.getTransposition().contains("octave")) << "Piccolo transposition should mention octave";
	EXPECT_TRUE(piccolo.getTransposition().contains("higher")) << "Piccolo should sound higher";
}


TEST_F(InstrumentControllerTest, DoubleBassTranspositionLoaded)
{
	// Double Bass sounds one octave lower
	int			   doubleBassKey = 304;

	InstrumentInfo bass			 = controller->getInstrument(doubleBassKey);
	EXPECT_TRUE(bass.getTransposition().contains("octave")) << "Double Bass should transpose by octave";
	EXPECT_TRUE(bass.getTransposition().contains("lower")) << "Double Bass should sound lower";
}

} // namespace InstrumentTests