/*
  ==============================================================================
	Module          Helper Functions Tests
	Description     Testing core helper functions for instrument management
  ==============================================================================
*/

#include <gtest/gtest.h>
#include "Helper.h"


namespace InstrumentTests
{

class HelperTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};


TEST_F(HelperTest, GetInstrumentKeyWithEnums)
{
	// Test string instruments
	int violinKey = getInstrumentKey(Family::Strings, Strings::Violin);
	EXPECT_EQ(violinKey, 301) << "Violin should have key 301 (3*100 + 1)";

	int violaKey = getInstrumentKey(Family::Strings, Strings::Viola);
	EXPECT_EQ(violaKey, 302) << "Viola should have key 302 (3*100 + 2)";

	// Test brass instruments
	int trumpetKey = getInstrumentKey(Family::Brass, Brass::Trumpet);
	EXPECT_EQ(trumpetKey, 202) << "Trumpet should have key 202 (2*100 + 2)";

	// Test woodwinds
	int fluteKey = getInstrumentKey(Family::Woodwinds, Woodwinds::Flute);
	EXPECT_EQ(fluteKey, 102) << "Flute should have key 102 (1*100 + 2)";

	// Test percussion
	int timpaniKey = getInstrumentKey(Family::Percussion, Percussion::Timpani);
	EXPECT_EQ(timpaniKey, 403) << "Timpani should have key 403 (4*100 + 3)";
}


TEST_F(HelperTest, GetInstrumentKeyWithStrings)
{
	String violinFamily		= StringsName;
	String violinInstrument = ViolinName;

	int	   key				= getInstrumentKey(violinFamily, violinInstrument);
	EXPECT_EQ(key, 301) << "String-based key generation should match enum-based";

	String brassFamily		 = BrassName;
	String trumpetInstrument = TrumpetName;

	key						 = getInstrumentKey(brassFamily, trumpetInstrument);
	EXPECT_EQ(key, 202) << "Brass trumpet key should be 202";
}


TEST_F(HelperTest, GetInstrumentNameFromKey)
{
	EXPECT_EQ(getInstrumentNameFromKey(301), "Violin");
	EXPECT_EQ(getInstrumentNameFromKey(202), "Trumpet");
	EXPECT_EQ(getInstrumentNameFromKey(403), "Timpani");
}


TEST_F(HelperTest, GetFamilyNameFromKey)
{
	EXPECT_EQ(getFamilyNameFromKey(301), "Strings");
	EXPECT_EQ(getFamilyNameFromKey(202), "Brass");
	EXPECT_EQ(getFamilyNameFromKey(102), "Woodwinds");
	EXPECT_EQ(getFamilyNameFromKey(403), "Percussion");
}


TEST_F(HelperTest, GetLowerOrHigherNoteValidRange)
{
	String range	  = "C3 - E6";

	String lowerNote  = getLowerOrHigherNote(range, true);
	String higherNote = getLowerOrHigherNote(range, false);

	EXPECT_EQ(lowerNote, "C3") << "Should extract lower note correctly";
	EXPECT_EQ(higherNote, "E6") << "Should extract higher note correctly";
}


TEST_F(HelperTest, GetLowerOrHigherNoteWithSpaces)
{
	String range	  = "  G4  -  A7  ";

	String lowerNote  = getLowerOrHigherNote(range, true);
	String higherNote = getLowerOrHigherNote(range, false);

	EXPECT_EQ(lowerNote, "G4") << "Should trim whitespace from lower note";
	EXPECT_EQ(higherNote, "A7") << "Should trim whitespace from higher note";
}


TEST_F(HelperTest, GetLowerOrHigherNoteInvalidRange)
{
	String invalidRange = "InvalidRange";

	String result		= getLowerOrHigherNote(invalidRange, true);
	EXPECT_TRUE(result.isEmpty()) << "Should return empty string for invalid range";
}


TEST_F(HelperTest, SplitColonizedStrings)
{
	String colonized = "Left Part : Right Part";

	String leftPart	 = splitColonizedStrings(colonized, true);
	String rightPart = splitColonizedStrings(colonized, false);

	EXPECT_EQ(leftPart, "Left Part") << "Should extract left part correctly";
	EXPECT_EQ(rightPart, "Right Part") << "Should extract right part correctly";
}


TEST_F(HelperTest, SplitColonizedStringsWithSpaces)
{
	String colonized = "  First  :  Second  ";

	String leftPart	 = splitColonizedStrings(colonized, true);
	String rightPart = splitColonizedStrings(colonized, false);

	EXPECT_EQ(leftPart, "First") << "Should trim whitespace from left part";
	EXPECT_EQ(rightPart, "Second") << "Should trim whitespace from right part";
}


TEST_F(HelperTest, SplitColonizedStringsInvalid)
{
	String invalid = "NoColonHere";

	String result  = splitColonizedStrings(invalid, true);
	EXPECT_TRUE(result.isEmpty()) << "Should return empty for strings without colon";
}


TEST_F(HelperTest, TurnNotenameIntoMidinumberValidNotes)
{
	// Middle C should be 60
	EXPECT_EQ(turnNotenameIntoMidinumber("C4"), 60) << "Middle C (C4) should be MIDI note 60";

	// Test various notes
	EXPECT_EQ(turnNotenameIntoMidinumber("C0"), 12) << "C0 should be MIDI note 12";
	EXPECT_EQ(turnNotenameIntoMidinumber("A4"), 69) << "A4 (440Hz) should be MIDI note 69";
	EXPECT_EQ(turnNotenameIntoMidinumber("C8"), 108) << "C8 should be MIDI note 108";
}


TEST_F(HelperTest, TurnNotenameIntoMidinumberSharpsAndFlats)
{
	// Test sharps
	EXPECT_EQ(turnNotenameIntoMidinumber("C#4"), 61) << "C#4 should be MIDI note 61";
	EXPECT_EQ(turnNotenameIntoMidinumber("F#4"), 66) << "F#4 should be MIDI note 66";

	// Test flats
	EXPECT_EQ(turnNotenameIntoMidinumber("Db4"), 61) << "Db4 should equal C#4 (MIDI note 61)";
	EXPECT_EQ(turnNotenameIntoMidinumber("Bb4"), 70) << "Bb4 should be MIDI note 70";
}


TEST_F(HelperTest, TurnNotenameIntoMidinumberInvalidInput)
{
	EXPECT_EQ(turnNotenameIntoMidinumber("Invalid"), -1) << "Should return -1 for invalid note";
	EXPECT_EQ(turnNotenameIntoMidinumber("X4"), -1) << "Should return -1 for invalid note name";
	EXPECT_EQ(turnNotenameIntoMidinumber("C"), -1) << "Should return -1 for missing octave";
}


TEST_F(HelperTest, ArticulationMapsConsistency)
{
	// Test forward and reverse mapping consistency
	for (const auto &pair : articulationMap)
	{
		Articulation articulation = pair.second;
		String		 originalName = pair.first;

		auto		 reverseIt	  = articulationReverseMap.find(articulation);
		ASSERT_NE(reverseIt, articulationReverseMap.end()) << "Articulation " << originalName.toStdString() << " missing from reverse map";

		EXPECT_EQ(reverseIt->second, originalName) << "Reverse mapping inconsistent for " << originalName.toStdString();
	}
}


TEST_F(HelperTest, DynamicMapsConsistency)
{
	// Verify dynamic mappings contain expected values
	EXPECT_EQ(dynamicMap.at(PianissimoDynamic), Dynamics::pianissimo);
	EXPECT_EQ(dynamicMap.at(FortissimoDynamic), Dynamics::fortissimo);

	// Test velocity layer fallbacks
	EXPECT_EQ(velocityLayerMap.at("v1"), Dynamics::mezzoPiano);
	EXPECT_EQ(velocityLayerMap.at("v4"), Dynamics::fortissimo);
}


TEST_F(HelperTest, FamilyMapsConsistency)
{
	// Test forward and reverse family mapping
	for (const auto &pair : familyMap)
	{
		Family family	  = pair.second;
		String familyName = pair.first;

		auto   reverseIt  = reverseFamilyMap.find(family);
		ASSERT_NE(reverseIt, reverseFamilyMap.end()) << "Family " << familyName.toStdString() << " missing from reverse map";

		EXPECT_EQ(reverseIt->second, familyName) << "Reverse family mapping inconsistent";
	}
}

} // namespace InstrumentTests
