/*
  ==============================================================================
	Module          InstrumentInfo Tests
	Description     Testing the InstrumentInfo value-type semantics
  ==============================================================================
*/

#include <gtest/gtest.h>
#include "InstrumentInfo.h"


namespace InstrumentTests
{

TEST(InstrumentInfoTest, DefaultConstructorInitializesEmptyState)
{
	InstrumentInfo info;

	EXPECT_TRUE(info.getName().isEmpty());
	EXPECT_TRUE(info.getRange().isEmpty());
	EXPECT_EQ(info.getKey(), 0);
	EXPECT_FALSE(info.isRhythmicPercussion());
	EXPECT_TRUE(info.getDisplayedRange().isEmpty());
	EXPECT_EQ(info.getQualities().size(), 0);
	EXPECT_EQ(info.getInformation().size(), 0);
	EXPECT_EQ(info.getFamousWorks().size(), 0);
	EXPECT_EQ(info.getTechniques().size(), 0);
	EXPECT_TRUE(info.getTransposition().isEmpty());
}


TEST(InstrumentInfoTest, ParameterizedConstructorSetsAllFields)
{
	String		name  = "Violin";
	String		range = "G3 - A7";
	StringArray qualities;
	qualities.add("Bright");
	qualities.add("Expressive");
	StringArray roles;
	roles.add("Melody");
	roles.add("Harmony");
	StringArray famous;
	famous.add("Concerto in D");
	famous.add("Symphony Feature");
	String		transposition = "Non-transposing";
	StringArray techniques;
	techniques.add("Legato");
	techniques.add("Pizzicato");
	int			   key			  = 301;
	bool		   rhythmic		  = false;
	String		   displayedRange = String(); // not used for non-percussion

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_EQ(info.getName(), name);
	EXPECT_EQ(info.getRange(), range);
	EXPECT_EQ(info.getKey(), key);
	EXPECT_FALSE(info.isRhythmicPercussion());
	EXPECT_EQ(info.getDisplayedRange(), displayedRange);
	EXPECT_EQ(info.getQualities().size(), 2);
	EXPECT_EQ(info.getInformation().size(), 2);
	EXPECT_EQ(info.getFamousWorks().size(), 2);
	EXPECT_EQ(info.getTechniques().size(), 2);
	EXPECT_EQ(info.getTransposition(), transposition);
}


TEST(InstrumentInfoTest, ParameterizedConstructorWithRhythmicPercussion)
{
	String		name  = "Timpani";
	String		range = "D2 - C4";
	StringArray qualities;
	qualities.add("Deep");
	qualities.add("Resonant");
	StringArray roles;
	roles.add("Rhythmic foundation");
	StringArray famous;
	famous.add("Beethoven Symphony No. 9");
	String		transposition = "-";
	StringArray techniques;
	techniques.add("Rolls");
	techniques.add("Muffling");
	int			   key			  = 403;
	bool		   rhythmic		  = true;
	String		   displayedRange = "D1 - A1";

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_TRUE(info.isRhythmicPercussion());
	EXPECT_EQ(info.getDisplayedRange(), displayedRange);
	EXPECT_NE(info.getDisplayedRange(), info.getRange()) << "Displayed range should differ from actual range for rhythmic percussion";
}


TEST(InstrumentInfoTest, TransposingInstrumentData)
{
	String		name		  = "French Horn";
	String		range		  = "F2 - C6";
	String		transposition = "F: Sounds a perfect 5th lower";
	StringArray qualities;
	qualities.add("Dark and mysterious");
	qualities.add("Heroic");
	StringArray roles;
	roles.add("Heroic themes");
	StringArray famous;
	famous.add("Mozart Horn Concerto");
	StringArray techniques;
	techniques.add("Stopped Horn");
	int			   key			  = 201;
	bool		   rhythmic		  = false;
	String		   displayedRange = String();

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_FALSE(info.getTransposition().isEmpty()) << "Transposing instruments should have transposition info";
	EXPECT_TRUE(info.getTransposition().contains("5th")) << "French Horn transposition should mention interval";
}


TEST(InstrumentInfoTest, NonTransposingInstrumentData)
{
	String		name		  = "Violin";
	String		range		  = "G3 - A7";
	String		transposition = "-";
	StringArray qualities;
	qualities.add("Bright");
	StringArray roles;
	roles.add("Melody");
	StringArray famous;
	famous.add("Beethoven Violin Concerto");
	StringArray techniques;
	techniques.add("Pizzicato");
	int			   key			  = 301;
	bool		   rhythmic		  = false;
	String		   displayedRange = String();

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_EQ(info.getTransposition(), "-") << "Non-transposing instruments should have '-' for transposition";
}


TEST(InstrumentInfoTest, QualitiesArrayPopulated)
{
	String		name  = "Clarinet";
	String		range = "E3 - C7";
	StringArray qualities;
	qualities.add("E3 - F#4: Chalumeau Register (deep, rich)");
	qualities.add("G4 - A#4: Throat Tones (rather pale)");
	qualities.add("B4 - C#6: Clarino Register (bright, incisive, expressive)");
	qualities.add("D6 - C7: Shrill, piercing");
	StringArray roles;
	roles.add("Lyrical passages");
	StringArray famous;
	famous.add("Mozart Clarinet Concerto");
	String		transposition = "Bb: Major 2nd lower";
	StringArray techniques;
	techniques.add("Flutter tonguing");
	int			   key			  = 105;
	bool		   rhythmic		  = false;
	String		   displayedRange = String();

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_EQ(info.getQualities().size(), 4) << "Clarinet should have 4 quality descriptions";
	EXPECT_TRUE(info.getQualities()[0].contains("Chalumeau")) << "First quality should describe Chalumeau register";
}


TEST(InstrumentInfoTest, FamousWorksArrayPopulated)
{
	String		name  = "Violin";
	String		range = "G3 - A7";
	StringArray qualities;
	qualities.add("Expressive");
	StringArray roles;
	roles.add("Melody");
	StringArray famous;
	famous.add("Beethoven - Violin Concerto in D major, Op. 61");
	famous.add("Tchaikovsky - Violin Concerto in D major, Op. 35");
	famous.add("Mendelssohn - Violin Concerto in E minor, Op. 64");
	String		transposition = "-";
	StringArray techniques;
	techniques.add("Vibrato");
	int			   key			  = 301;
	bool		   rhythmic		  = false;
	String		   displayedRange = String();

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_EQ(info.getFamousWorks().size(), 3) << "Violin should have 3 famous works listed";
	EXPECT_TRUE(info.getFamousWorks()[0].contains("Beethoven")) << "First work should be Beethoven";
}


TEST(InstrumentInfoTest, PlayingTechniquesPopulated)
{
	String		name  = "Violin";
	String		range = "G3 - A7";
	StringArray qualities;
	qualities.add("Bright");
	StringArray roles;
	roles.add("Melody");
	StringArray famous;
	famous.add("Beethoven Concerto");
	String		transposition = "-";
	StringArray techniques;
	techniques.add("Pizzicato: Plucking the strings with fingers");
	techniques.add("Arco: Using the bow to produce sound");
	techniques.add("Sul ponticello: Playing near the bridge for a tense sound");
	techniques.add("Tremolo: Rapid back-and-forth bowing");
	int			   key			  = 301;
	bool		   rhythmic		  = false;
	String		   displayedRange = String();

	InstrumentInfo info(name, range, qualities, roles, famous, transposition, techniques, key, rhythmic, displayedRange);

	EXPECT_GE(info.getTechniques().size(), 4) << "Violin should have at least 4 playing techniques";
	EXPECT_TRUE(info.getTechniques()[0].contains("Pizzicato")) << "First technique should be Pizzicato";
}

} // namespace InstrumentTests
