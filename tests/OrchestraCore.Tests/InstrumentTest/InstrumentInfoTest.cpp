/*
  ==============================================================================
	Module          InstrumentProfile Tests
	Description     Testing the InstrumentProfile and related structs
  ==============================================================================
*/

#include <gtest/gtest.h>
#include "InstrumentInfo.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace InstrumentTests
{

// ============================================================================
// InstrumentRange Tests
// ============================================================================

class InstrumentRangeTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(InstrumentRangeTest, DefaultConstructorInitializesEmptyState)
{
	InstrumentRange range;

	EXPECT_EQ(range.getHigherRange(), "");
	EXPECT_EQ(range.getLowerRange(), "");
	EXPECT_EQ(range.getHigherRangeNoteValue(), 0);
	EXPECT_EQ(range.getLowerRangeNoteValue(), 0);
	EXPECT_EQ(range.getTransposition(), "");
}

TEST_F(InstrumentRangeTest, DeserializesWrittenRangeFromJSON)
{
	json			j	  = R"({
		"written": {
			"low": "C3",
			"high": "C6"
		}
	})"_json;

	InstrumentRange range = j.get<InstrumentRange>();

	EXPECT_EQ(range.getLowerRange(), "C3");
	EXPECT_EQ(range.getHigherRange(), "C6");
	EXPECT_EQ(range.getLowerRangeNoteValue(), 48);	// C3 MIDI note
	EXPECT_EQ(range.getHigherRangeNoteValue(), 84); // C6 MIDI note
}

TEST_F(InstrumentRangeTest, DeserializesWithTransposition)
{
	json			j	  = R"({
		"written": {
			"low": "F2",
			"high": "C6"
		},
		"transposition": "F: Sounds a perfect 5th lower"
	})"_json;

	InstrumentRange range = j.get<InstrumentRange>();

	EXPECT_EQ(range.getTransposition(), "F: Sounds a perfect 5th lower");
}

TEST_F(InstrumentRangeTest, DeserializesWithDisplayedRange)
{
	json			j	  = R"({
		"written": {
			"low": "D2",
			"high": "C4"
		},
		"displayed": {
			"low": "D1",
			"high": "A1"
		}
	})"_json;

	InstrumentRange range = j.get<InstrumentRange>();

	EXPECT_EQ(range.getLowerRange(), "D2");
	EXPECT_EQ(range.getHigherRange(), "C4");
	EXPECT_EQ(range.getDisplayedLowerRange(), "D1");
	EXPECT_EQ(range.getDisplayedHigherRange(), "A1");
}

TEST_F(InstrumentRangeTest, DefaultsDisplayedRangeToWritten)
{
	json			j	  = R"({
		"written": {
			"low": "G3",
			"high": "A7"
		}
	})"_json;

	InstrumentRange range = j.get<InstrumentRange>();

	EXPECT_EQ(range.getDisplayedLowerRange(), range.getLowerRange());
	EXPECT_EQ(range.getDisplayedHigherRange(), range.getHigherRange());
}

TEST_F(InstrumentRangeTest, EqualityOperatorComparesCorrectly)
{
	json			j1	   = R"({"written": {"low": "C3", "high": "C6"}})"_json;
	json			j2	   = R"({"written": {"low": "C3", "high": "C6"}})"_json;
	json			j3	   = R"({"written": {"low": "G3", "high": "A7"}})"_json;

	InstrumentRange range1 = j1.get<InstrumentRange>();
	InstrumentRange range2 = j2.get<InstrumentRange>();
	InstrumentRange range3 = j3.get<InstrumentRange>();

	EXPECT_EQ(range1, range2);
	EXPECT_FALSE(range1 == range3);
}

TEST_F(InstrumentRangeTest, SerializesToJSON)
{
	json			j	  = R"({
		"written": {
			"low": "C3",
			"high": "C6"
		},
		"transposition": "Bb: Major 2nd lower"
	})"_json;

	InstrumentRange range = j.get<InstrumentRange>();
	json			output;
	to_json(output, range);

	EXPECT_EQ(output["written"]["low"], "C3");
	EXPECT_EQ(output["written"]["high"], "C6");
	EXPECT_EQ(output["transposition"], "Bb: Major 2nd lower");
}

// ============================================================================
// RegisterQuality Tests
// ============================================================================

class RegisterQualityTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(RegisterQualityTest, DefaultConstructorInitializesEmptyState)
{
	InstrumentRegister quality;

	EXPECT_EQ(quality.getLowerRange(), "");
	EXPECT_EQ(quality.getHigherRange(), "");
	EXPECT_EQ(quality.getDescription(), "");
	EXPECT_EQ(quality.getLowerNoteValue(), 0);
	EXPECT_EQ(quality.getHigherNoteValue(), 0);
}

TEST_F(RegisterQualityTest, DeserializesFromJSON)
{
	json			j		= R"({
		"range": {
			"low": "C3",
			"high": "E3"
		},
		"description": "Rich and resonant"
	})"_json;

	InstrumentRegister quality = j.get<InstrumentRegister>();

	EXPECT_EQ(quality.getLowerRange(), "C3");
	EXPECT_EQ(quality.getHigherRange(), "E3");
	EXPECT_EQ(quality.getDescription(), "Rich and resonant");
	EXPECT_EQ(quality.getLowerNoteValue(), 48);	 // C3 MIDI
	EXPECT_EQ(quality.getHigherNoteValue(), 52); // E3 MIDI
}

TEST_F(RegisterQualityTest, HandlesSingleNoteRange)
{
	json			j		= R"({
		"range": {
			"low": "G3",
			"high": "G3"
		},
		"description": "Warm and dark"
	})"_json;

	InstrumentRegister quality = j.get<InstrumentRegister>();

	EXPECT_EQ(quality.getLowerRange(), "G3");
	EXPECT_EQ(quality.getHigherRange(), "G3");
	EXPECT_EQ(quality.getLowerNoteValue(), quality.getHigherNoteValue());
}

TEST_F(RegisterQualityTest, EqualityOperatorWorks)
{
	json			j1 = R"({"range": {"low": "C3", "high": "E3"}, "description": "Test"})"_json;
	json			j2 = R"({"range": {"low": "C3", "high": "E3"}, "description": "Test"})"_json;
	json			j3 = R"({"range": {"low": "F3", "high": "A3"}, "description": "Different"})"_json;

	InstrumentRegister q1 = j1.get<InstrumentRegister>();
	InstrumentRegister q2 = j2.get<InstrumentRegister>();
	InstrumentRegister q3 = j3.get<InstrumentRegister>();

	EXPECT_EQ(q1, q2);
	EXPECT_FALSE(q1 == q3);
}

TEST_F(RegisterQualityTest, SerializesToJSON)
{
	json			j		= R"({
		"range": {"low": "C3", "high": "E3"},
		"description": "Rich and resonant"
	})"_json;

	InstrumentRegister quality = j.get<InstrumentRegister>();
	json			output;
	to_json(output, quality);

	EXPECT_EQ(output["range"]["low"], "C3");
	EXPECT_EQ(output["range"]["high"], "E3");
	EXPECT_EQ(output["description"], "Rich and resonant");
}

// ============================================================================
// PlayingTechnique Tests
// ============================================================================

class PlayingTechniqueTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(PlayingTechniqueTest, DefaultConstructorInitializesEmpty)
{
	PlayingTechnique technique;

	EXPECT_EQ(technique.getName(), "");
	EXPECT_EQ(technique.getDescription(), "");
}

TEST_F(PlayingTechniqueTest, DeserializesFromJSON)
{
	json			 j		   = R"({
		"name": "Pizzicato",
		"description": "Plucking the strings with fingers"
	})"_json;

	PlayingTechnique technique = j.get<PlayingTechnique>();

	EXPECT_EQ(technique.getName(), "Pizzicato");
	EXPECT_EQ(technique.getDescription(), "Plucking the strings with fingers");
}

TEST_F(PlayingTechniqueTest, EqualityOperatorWorks)
{
	json			 j1 = R"({"name": "Pizzicato", "description": "Plucking"})"_json;
	json			 j2 = R"({"name": "Pizzicato", "description": "Plucking"})"_json;
	json			 j3 = R"({"name": "Arco", "description": "Using the bow"})"_json;

	PlayingTechnique t1 = j1.get<PlayingTechnique>();
	PlayingTechnique t2 = j2.get<PlayingTechnique>();
	PlayingTechnique t3 = j3.get<PlayingTechnique>();

	EXPECT_EQ(t1, t2);
	EXPECT_FALSE(t1 == t3);
}

TEST_F(PlayingTechniqueTest, SerializesToJSON)
{
	json			 j		   = R"({
		"name": "Tremolo",
		"description": "Rapid back-and-forth bowing"
	})"_json;

	PlayingTechnique technique = j.get<PlayingTechnique>();
	json			 output;
	to_json(output, technique);

	EXPECT_EQ(output["name"], "Tremolo");
	EXPECT_EQ(output["description"], "Rapid back-and-forth bowing");
}

// ============================================================================
// SignatureWork Tests
// ============================================================================

class SignatureWorkTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(SignatureWorkTest, DefaultConstructorInitializesEmpty)
{
	SignatureWork work;

	EXPECT_EQ(work.getComposer(), "");
	EXPECT_EQ(work.getTitle(), "");
	EXPECT_EQ(work.getWork(), " - "); // composer + " - " + title
}

TEST_F(SignatureWorkTest, DeserializesFromJSON)
{
	json		  j	   = R"({
		"composer": "Beethoven",
		"title": "Symphony No. 9"
	})"_json;

	SignatureWork work = j.get<SignatureWork>();

	EXPECT_EQ(work.getComposer(), "Beethoven");
	EXPECT_EQ(work.getTitle(), "Symphony No. 9");
	EXPECT_EQ(work.getWork(), "Beethoven - Symphony No. 9");
}

TEST_F(SignatureWorkTest, EqualityOperatorWorks)
{
	json		  j1 = R"({"composer": "Mozart", "title": "Requiem"})"_json;
	json		  j2 = R"({"composer": "Mozart", "title": "Requiem"})"_json;
	json		  j3 = R"({"composer": "Bach", "title": "Mass in B minor"})"_json;

	SignatureWork w1 = j1.get<SignatureWork>();
	SignatureWork w2 = j2.get<SignatureWork>();
	SignatureWork w3 = j3.get<SignatureWork>();

	EXPECT_EQ(w1, w2);
	EXPECT_FALSE(w1 == w3);
}

TEST_F(SignatureWorkTest, SerializesToJSON)
{
	json		  j	   = R"({
		"composer": "Tchaikovsky",
		"title": "1812 Overture"
	})"_json;

	SignatureWork work = j.get<SignatureWork>();
	json		  output;
	to_json(output, work);

	EXPECT_EQ(output["composer"], "Tchaikovsky");
	EXPECT_EQ(output["title"], "1812 Overture");
}

// ============================================================================
// OrchestrationRole Tests
// ============================================================================

class OrchestrationRoleTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(OrchestrationRoleTest, DefaultConstructorInitializesEmpty)
{
	OrchestrationRole role;

	EXPECT_EQ(role.getRole(), "");
}

TEST_F(OrchestrationRoleTest, ParameterizedConstructor)
{
	OrchestrationRole role("Leads with melody");

	EXPECT_EQ(role.getRole(), "Leads with melody");
}

TEST_F(OrchestrationRoleTest, DeserializesFromJSONString)
{
	json			  j	   = "Provides harmonic support";

	OrchestrationRole role = j.get<OrchestrationRole>();

	EXPECT_EQ(role.getRole(), "Provides harmonic support");
}

TEST_F(OrchestrationRoleTest, EqualityOperatorWorks)
{
	OrchestrationRole r1("Same role");
	OrchestrationRole r2("Same role");
	OrchestrationRole r3("Different role");

	EXPECT_EQ(r1, r2);
	EXPECT_FALSE(r1 == r3);
}

// ============================================================================
// InstrumentProfile Tests
// ============================================================================

class InstrumentProfileTest : public ::testing::Test
{
protected:
	void			  SetUp() override {}
	void			  TearDown() override {}

	InstrumentProfile createTestInstrument()
	{
		json			   rangeJson = R"({"written": {"low": "C3", "high": "C6"}})"_json;
		InstrumentRange	   range	 = rangeJson.get<InstrumentRange>();

		InstrumentRegisters  qualities;
		OrchestrationRoles roles;
		roles.push_back(OrchestrationRole("Test role"));
		SignatureWorks	  works;
		PlayingTechniques techniques;

		return InstrumentProfile("TestInstrument", 301, range, qualities, roles, works, techniques, false);
	}
};

TEST_F(InstrumentProfileTest, DefaultConstructorInitializesEmpty)
{
	InstrumentProfile profile;

	EXPECT_EQ(profile.getName(), "");
	EXPECT_EQ(profile.getInstrumentID(), 0);
	EXPECT_FALSE(profile.isRhythmicPercussion());
	EXPECT_FALSE(profile.isValid());
}

TEST_F(InstrumentProfileTest, ParameterizedConstructorSetsAllFields)
{
	auto profile = createTestInstrument();

	EXPECT_EQ(profile.getName(), "TestInstrument");
	EXPECT_EQ(profile.getInstrumentID(), 301);
	EXPECT_FALSE(profile.isRhythmicPercussion());
	EXPECT_TRUE(profile.isValid());
}

TEST_F(InstrumentProfileTest, IsValidReturnsTrueForValidInstrument)
{
	auto profile = createTestInstrument();

	EXPECT_TRUE(profile.isValid());
}

TEST_F(InstrumentProfileTest, IsValidReturnsFalseForEmptyName)
{
	json			  rangeJson = R"({"written": {"low": "C3", "high": "C6"}})"_json;
	InstrumentRange	  range		= rangeJson.get<InstrumentRange>();

	InstrumentProfile profile("", 301, range, {}, {}, {}, {}, false);

	EXPECT_FALSE(profile.isValid());
}

TEST_F(InstrumentProfileTest, IsValidReturnsFalseForZeroKey)
{
	json			  rangeJson = R"({"written": {"low": "C3", "high": "C6"}})"_json;
	InstrumentRange	  range		= rangeJson.get<InstrumentRange>();

	InstrumentProfile profile("ValidName", 0, range, {}, {}, {}, {}, false);

	EXPECT_FALSE(profile.isValid());
}

TEST_F(InstrumentProfileTest, RhythmicPercussionFlagWorks)
{
	json			  rangeJson = R"({"written": {"low": "D2", "high": "C4"}})"_json;
	InstrumentRange	  range		= rangeJson.get<InstrumentRange>();

	InstrumentProfile profile("Timpani", 403, range, {}, {}, {}, {}, true);

	EXPECT_TRUE(profile.isRhythmicPercussion());
}

TEST_F(InstrumentProfileTest, GettersReturnCorrectValues)
{
	json			  rangeJson	  = R"({"written": {"low": "G3", "high": "A7"}})"_json;
	InstrumentRange	  range		  = rangeJson.get<InstrumentRange>();

	json			  qualityJson = R"({"range": {"low": "G3", "high": "G3"}, "description": "Rich"})"_json;
	InstrumentRegisters qualities;
	qualities.push_back(qualityJson.get<InstrumentRegister>());

	OrchestrationRoles roles;
	roles.push_back(OrchestrationRole("Leads melody"));

	json		   workJson = R"({"composer": "Beethoven", "title": "Violin Concerto"})"_json;
	SignatureWorks works;
	works.push_back(workJson.get<SignatureWork>());

	json			  techJson = R"({"name": "Pizzicato", "description": "Plucking"})"_json;
	PlayingTechniques techniques;
	techniques.push_back(techJson.get<PlayingTechnique>());

	InstrumentProfile profile("Violin", 301, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(profile.getName(), "Violin");
	EXPECT_EQ(profile.getInstrumentID(), 301);
	EXPECT_EQ(profile.getRegisters().size(), 1);
	EXPECT_EQ(profile.getRoles().size(), 1);
	EXPECT_EQ(profile.getFamousWorks().size(), 1);
	EXPECT_EQ(profile.getTechniques().size(), 1);
}

TEST_F(InstrumentProfileTest, EqualityOperatorComparesKeyAndName)
{
	auto			  p1		= createTestInstrument();
	auto			  p2		= createTestInstrument();

	json			  rangeJson = R"({"written": {"low": "C3", "high": "E6"}})"_json;
	InstrumentRange	  range		= rangeJson.get<InstrumentRange>();
	InstrumentProfile p3("DifferentInstrument", 302, range, {}, {}, {}, {}, false);

	EXPECT_EQ(p1, p2);
	EXPECT_FALSE(p1 == p3);
}

TEST_F(InstrumentProfileTest, CanStoreEmptyCollections)
{
	json			  rangeJson = R"({"written": {"low": "C3", "high": "C6"}})"_json;
	InstrumentRange	  range		= rangeJson.get<InstrumentRange>();

	InstrumentProfile profile("Test", 100, range, {}, {}, {}, {}, false);

	EXPECT_EQ(profile.getRegisters().size(), 0);
	EXPECT_EQ(profile.getRoles().size(), 0);
	EXPECT_EQ(profile.getFamousWorks().size(), 0);
	EXPECT_EQ(profile.getTechniques().size(), 0);
}

TEST_F(InstrumentProfileTest, CanStoreLargeCollections)
{
	json			  rangeJson = R"({"written": {"low": "C3", "high": "C6"}})"_json;
	InstrumentRange	  range		= rangeJson.get<InstrumentRange>();

	InstrumentRegisters qualities;
	for (int i = 0; i < 10; ++i)
	{
		json j = nlohmann::json::parse(R"({"range": {"low": "C3", "high": "E3"}, "description": "Quality )" + std::to_string(i) + R"("})");
		qualities.push_back(j.get<InstrumentRegister>());
	}

	OrchestrationRoles roles;
	for (int i = 0; i < 5; ++i)
		roles.push_back(OrchestrationRole("Role " + std::to_string(i)));

	SignatureWorks works;
	for (int i = 0; i < 15; ++i)
	{
		json j = nlohmann::json::parse(R"({"composer": "Composer )" + std::to_string(i) + R"(", "title": "Work )" + std::to_string(i) + R"("})");
		works.push_back(j.get<SignatureWork>());
	}

	PlayingTechniques techniques;
	for (int i = 0; i < 8; ++i)
	{
		json j = nlohmann::json::parse(R"({"name": "Tech)" + std::to_string(i) + R"(", "description": "Description )" + std::to_string(i) + R"("})");
		techniques.push_back(j.get<PlayingTechnique>());
	}

	InstrumentProfile profile("Test", 100, range, qualities, roles, works, techniques, false);

	EXPECT_EQ(profile.getRegisters().size(), 10);
	EXPECT_EQ(profile.getRoles().size(), 5);
	EXPECT_EQ(profile.getFamousWorks().size(), 15);
	EXPECT_EQ(profile.getTechniques().size(), 8);
}

// ============================================================================
// Integration Tests - Full JSON Deserialization
// ============================================================================

class IntegrationTest : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(IntegrationTest, DeserializesCompleteViolinProfileFromJSON)
{
	json			  j		= R"({
		"name": "Violin",
		"range": {
			"written": {
				"low": "G3",
				"high": "A7"
			}
		},
		"qualities": [
			{
				"range": {"low": "G3", "high": "G3"},
				"description": "Rich and resonant"
			},
			{
				"range": {"low": "D4", "high": "D4"},
				"description": "Subtly vibrant"
			}
		],
		"roles": [
			"Leads with melody",
			"Provides harmonic support"
		],
		"famousWorks": [
			{
				"composer": "Beethoven",
				"title": "Violin Concerto in D major, Op. 61"
			}
		],
		"techniques": [
			{
				"name": "Pizzicato",
				"description": "Plucking the strings with fingers"
			}
		],
		"isRhythmicPercussion": false
	})"_json;

	// Manually construct from parsed JSON (simulating InstrumentController logic)
	std::string		  name	= j["name"];
	InstrumentRange	  range = j["range"].get<InstrumentRange>();

	InstrumentRegisters qualities;
	for (const auto &q : j["qualities"])
		qualities.push_back(q.get<InstrumentRegister>());

	OrchestrationRoles roles;
	for (const auto &r : j["roles"])
		roles.push_back(r.get<OrchestrationRole>());

	SignatureWorks works;
	for (const auto &w : j["famousWorks"])
		works.push_back(w.get<SignatureWork>());

	PlayingTechniques techniques;
	for (const auto &t : j["techniques"])
		techniques.push_back(t.get<PlayingTechnique>());

	bool			  isRhythmic = j["isRhythmicPercussion"];

	InstrumentProfile profile(name, 301, range, qualities, roles, works, techniques, isRhythmic);

	EXPECT_EQ(profile.getName(), "Violin");
	EXPECT_EQ(profile.getInstrumentID(), 301);
	EXPECT_EQ(profile.getRegisters().size(), 2);
	EXPECT_EQ(profile.getRoles().size(), 2);
	EXPECT_EQ(profile.getFamousWorks().size(), 1);
	EXPECT_EQ(profile.getTechniques().size(), 1);
	EXPECT_FALSE(profile.isRhythmicPercussion());
	EXPECT_TRUE(profile.isValid());
}

TEST_F(IntegrationTest, DeserializesTimpaniWithDisplayedRange)
{
	json			  j		= R"({
		"name": "Timpani",
		"range": {
			"written": {
				"low": "D2",
				"high": "C4"
			},
			"displayed": {
				"low": "D1",
				"high": "A1"
			}
		},
		"qualities": [
			{
				"range": {"low": "D1", "high": "A1"},
				"description": "Deep and thunderous"
			}
		],
		"roles": ["Provides rhythmic foundation"],
		"famousWorks": [
			{
				"composer": "Beethoven",
				"title": "Symphony No. 9"
			}
		],
		"techniques": [],
		"isRhythmicPercussion": true
	})"_json;

	std::string		  name	= j["name"];
	InstrumentRange	  range = j["range"].get<InstrumentRange>();

	InstrumentRegisters qualities;
	for (const auto &q : j["qualities"])
		qualities.push_back(q.get<InstrumentRegister>());

	OrchestrationRoles roles;
	for (const auto &r : j["roles"])
		roles.push_back(r.get<OrchestrationRole>());

	SignatureWorks works;
	for (const auto &w : j["famousWorks"])
		works.push_back(w.get<SignatureWork>());

	PlayingTechniques techniques;

	InstrumentProfile profile(name, 403, range, qualities, roles, works, techniques, true);

	EXPECT_EQ(profile.getName(), "Timpani");
	EXPECT_TRUE(profile.isRhythmicPercussion());
	EXPECT_NE(range.getDisplayedLowerRange(), range.getLowerRange());
	EXPECT_EQ(range.getDisplayedLowerRange(), "D1");
}

} // namespace InstrumentTests
