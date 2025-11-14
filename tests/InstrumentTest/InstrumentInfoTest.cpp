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

// ============================================================================
// Range Tests
// ============================================================================

TEST(RangeTest, DefaultConstructorInitializesEmptyState)
{
	InstrumentRange range;

	EXPECT_EQ(range.getHigherRange(), "");
	EXPECT_EQ(range.getLowerRange(), "");
	EXPECT_EQ(range.getHigherRangeNoteValue(), 0);
	EXPECT_EQ(range.getLowerRangeNoteValue(), 0);
	EXPECT_EQ(range.getTransposition(), "");
}

TEST(RangeTest, SingleArgumentConstructorParsesRange)
{
	InstrumentRange range("G3:A7");

	EXPECT_NE(range.getLowerRange(), "");
	EXPECT_NE(range.getHigherRange(), "");
	EXPECT_GT(range.getHigherRangeNoteValue(), range.getLowerRangeNoteValue());
	EXPECT_EQ(range.getTransposition(), "");
}

TEST(RangeTest, TwoArgumentConstructorHandlesDisplayedRange)
{
	InstrumentRange range("G3:A7", "G2:A6");

	EXPECT_NE(range.getLowerRange(), "");
	EXPECT_NE(range.getHigherRange(), "");
	EXPECT_NE(range.getDisplayedLowerRange(), "");
	EXPECT_NE(range.getDisplayedHigherRange(), "");
}

TEST(RangeTest, ThreeArgumentConstructorIncludesTransposition)
{
	std::string transposition = "Bb: Sounds a major 2nd lower";
	InstrumentRange range("G3:A7", "G3:A7", transposition);

	EXPECT_EQ(range.getTransposition(), transposition);
}

TEST(RangeTest, EqualityOperatorComparesRanges)
{
	InstrumentRange range1("G3:A7");
	InstrumentRange range2("G3:A7");
	InstrumentRange range3("C4:C6");

	EXPECT_EQ(range1, range2);
	EXPECT_FALSE(range1 == range3);
}

TEST(RangeTest, DisplayedRangeCanDifferFromActualRange)
{
	InstrumentRange range("C2:C4", "C1:C3");

	EXPECT_NE(range.getDisplayedLowerRange(), range.getLowerRange());
	EXPECT_NE(range.getDisplayedHigherRange(), range.getHigherRange());
}

// ============================================================================
// FamousWork Tests
// ============================================================================

TEST(FamousWorkTest, DefaultConstructorInitializesEmpty)
{
	FamousWork work;

	EXPECT_EQ(work.getWork(), "");
}

TEST(FamousWorkTest, ConstructorStoresWorkString)
{
	std::string workName = "Test Symphony";
	FamousWork	work(workName);

	EXPECT_EQ(work.getWork(), workName);
}

// ============================================================================
// PlayingTechnique Tests
// ============================================================================

TEST(PlayingTechniqueTest, DefaultConstructorInitializesEmpty)
{
	PlayingTechnique technique;

	EXPECT_EQ(technique.getName(), "");
	EXPECT_EQ(technique.getDescription(), "");
}

TEST(PlayingTechniqueTest, ConstructorParsesColonizedString)
{
	PlayingTechnique technique("TechniqueName:Technique description");

	EXPECT_EQ(technique.getName(), "TechniqueName");
	EXPECT_EQ(technique.getDescription(), "Technique description");
}

TEST(PlayingTechniqueTest, HandlesMultipleColons)
{
	PlayingTechnique technique("Name:Description: with: colons");

	EXPECT_EQ(technique.getName(), "Name");
	EXPECT_FALSE(technique.getDescription().empty());
}

// ============================================================================
// Quality Tests
// ============================================================================

TEST(QualityTest, DefaultConstructorInitializesEmpty)
{
	Quality quality;

	EXPECT_EQ(quality.getLowerRange(), "");
	EXPECT_EQ(quality.getHigherRange(), "");
	EXPECT_EQ(quality.getDescription(), "");
}

TEST(QualityTest, ConstructorParsesRangeAndDescription)
{
	Quality quality("C3-G4:Test quality description");

	EXPECT_FALSE(quality.getLowerRange().empty());
	EXPECT_FALSE(quality.getHigherRange().empty());
	EXPECT_FALSE(quality.getDescription().empty());
}

TEST(QualityTest, HandlesSingleNoteRange)
{
	Quality quality("C4:Single note description");

	EXPECT_EQ(quality.getLowerRange(), quality.getHigherRange());
	EXPECT_FALSE(quality.getDescription().empty());
}

// ============================================================================
// Role Tests
// ============================================================================

TEST(RoleTest, DefaultConstructorInitializesEmpty)
{
	Role role;

	EXPECT_EQ(role.getRole(), "");
}

TEST(RoleTest, ConstructorStoresRoleString)
{
	std::string roleText = "Test role";
	Role		role(roleText);

	EXPECT_EQ(role.getRole(), roleText);
}

// ============================================================================
// InstrumentInfo Tests - Structure and API
// ============================================================================

TEST(InstrumentInfoTest, DefaultConstructorInitializesEmptyState)
{
	InstrumentInfo info;

	EXPECT_EQ(info.getName(), "");
	EXPECT_EQ(info.getKey(), 0);
	EXPECT_FALSE(info.isRhythmicPercussion());
	EXPECT_EQ(info.getQualities().size(), 0);
	EXPECT_EQ(info.getRoles().size(), 0);
	EXPECT_EQ(info.getFamousWorks().size(), 0);
	EXPECT_EQ(info.getTechniques().size(), 0);
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsName)
{
	std::string	   name = "TestInstrument";
	InstrumentID   key	= 100;
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info(name, key, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getName(), name);
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsKey)
{
	InstrumentID   key = 301;
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", key, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getKey(), key);
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsRange)
{
	InstrumentRange range("G3:A7");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getRange().getLowerRange(), range.getLowerRange());
	EXPECT_EQ(info.getRange().getHigherRange(), range.getHigherRange());
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsQualities)
{
	InstrumentRange range("C3:C5");
	Qualities qualities;
	qualities.push_back(Quality("C3-E3:Low"));
	qualities.push_back(Quality("F3-C5:High"));
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getQualities().size(), 2);
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsRoles)
{
	InstrumentRange range("C3:C5");
	Qualities qualities;
	Roles	  roles;
	roles.push_back(Role("Role 1"));
	roles.push_back(Role("Role 2"));
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getRoles().size(), 2);
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsFamousWorks)
{
	InstrumentRange range("C3:C5");
	Qualities	qualities;
	Roles		roles;
	FamousWorks works;
	works.push_back(FamousWork("Work 1"));
	works.push_back(FamousWork("Work 2"));
	works.push_back(FamousWork("Work 3"));
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getFamousWorks().size(), 3);
}

TEST(InstrumentInfoTest, ParameterizedConstructorSetsTechniques)
{
	InstrumentRange range("C3:C5");
	Qualities	qualities;
	Roles		roles;
	FamousWorks works;
	Techniques	techniques;
	techniques.push_back(PlayingTechnique("Tech1:Description 1"));
	techniques.push_back(PlayingTechnique("Tech2:Description 2"));

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getTechniques().size(), 2);
}

TEST(InstrumentInfoTest, RhythmicPercussionFlagDefaultsToFalse)
{
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques);

	EXPECT_FALSE(info.isRhythmicPercussion());
}

TEST(InstrumentInfoTest, RhythmicPercussionFlagCanBeSetTrue)
{
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, true);

	EXPECT_TRUE(info.isRhythmicPercussion());
}

TEST(InstrumentInfoTest, IsValidReturnsTrueForValidInstrument)
{
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("ValidName", 301, range, qualities, roles, works, techniques, false);

	EXPECT_TRUE(info.isValid());
}

TEST(InstrumentInfoTest, IsValidReturnsFalseForEmptyName)
{
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("", 301, range, qualities, roles, works, techniques, false);

	EXPECT_FALSE(info.isValid());
}

TEST(InstrumentInfoTest, IsValidReturnsFalseForZeroKey)
{
	InstrumentRange range("C3:C5");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("ValidName", 0, range, qualities, roles, works, techniques, false);

	EXPECT_FALSE(info.isValid());
}

TEST(InstrumentInfoTest, IsValidReturnsFalseForDefaultConstructed)
{
	InstrumentInfo info;

	EXPECT_FALSE(info.isValid());
}

TEST(InstrumentInfoTest, CanStoreEmptyCollections)
{
	InstrumentRange range("C3:C5");
	Qualities	   qualities;  // empty
	Roles		   roles;	   // empty
	FamousWorks	   works;	   // empty
	Techniques	   techniques; // empty

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getQualities().size(), 0);
	EXPECT_EQ(info.getRoles().size(), 0);
	EXPECT_EQ(info.getFamousWorks().size(), 0);
	EXPECT_EQ(info.getTechniques().size(), 0);
}

TEST(InstrumentInfoTest, CanStoreLargeCollections)
{
	InstrumentRange range("C3:C5");

	Qualities qualities;
	for (int i = 0; i < 10; ++i)
		qualities.push_back(Quality("C3-C4:Quality " + std::to_string(i)));

	Roles roles;
	for (int i = 0; i < 5; ++i)
		roles.push_back(Role("Role " + std::to_string(i)));

	FamousWorks works;
	for (int i = 0; i < 15; ++i)
		works.push_back(FamousWork("Work " + std::to_string(i)));

	Techniques techniques;
	for (int i = 0; i < 8; ++i)
		techniques.push_back(PlayingTechnique("Tech" + std::to_string(i) + ":Description"));

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getQualities().size(), 10);
	EXPECT_EQ(info.getRoles().size(), 5);
	EXPECT_EQ(info.getFamousWorks().size(), 15);
	EXPECT_EQ(info.getTechniques().size(), 8);
}

// ============================================================================
// Integration Tests - Verify data integrity
// ============================================================================

TEST(InstrumentInfoTest, RetrievedQualitiesMatchInput)
{
	InstrumentRange range("C3:C5");
	Qualities qualities;
	qualities.push_back(Quality("C3-E3:Lower register"));
	qualities.push_back(Quality("F3-C5:Upper register"));
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	auto		   retrieved = info.getQualities();
	ASSERT_EQ(retrieved.size(), 2);
	EXPECT_FALSE(retrieved[0].getDescription().empty());
	EXPECT_FALSE(retrieved[1].getDescription().empty());
}

TEST(InstrumentInfoTest, RetrievedTechniquesMatchInput)
{
	InstrumentRange range("C3:C5");
	Qualities	qualities;
	Roles		roles;
	FamousWorks works;
	Techniques	techniques;
	techniques.push_back(PlayingTechnique("Legato:Smooth connection"));
	techniques.push_back(PlayingTechnique("Staccato:Short and detached"));

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	auto		   retrieved = info.getTechniques();
	ASSERT_EQ(retrieved.size(), 2);
	EXPECT_EQ(retrieved[0].getName(), "Legato");
	EXPECT_EQ(retrieved[1].getName(), "Staccato");
}

TEST(InstrumentInfoTest, RangeWithTranspositionPreservesTransposition)
{
	InstrumentRange range("C3:C5", "C3:C5", "Bb: Sounds a major 2nd lower");
	Qualities	   qualities;
	Roles		   roles;
	FamousWorks	   works;
	Techniques	   techniques;

	InstrumentInfo info("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(info.getRange().getTransposition(), "Bb: Sounds a major 2nd lower");
}


} // namespace InstrumentTests
