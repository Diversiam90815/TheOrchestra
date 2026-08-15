/*
  ==============================================================================
	Module          NotationGeometry Tests
	Description     Staff placement, ottava escalation and transposition naming
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "NotationGeometry.h"

namespace NotationGeometryTests
{

//==============================================================================
// clefFromString
//==============================================================================

TEST(ClefFromStringTest, ParsesEveryDeclaredClef)
{
	EXPECT_EQ(clefFromString("Treble"), Clef::Treble);
	EXPECT_EQ(clefFromString("Bass"), Clef::Bass);
	EXPECT_EQ(clefFromString("Alto"), Clef::Alto);
	EXPECT_EQ(clefFromString("Tenor"), Clef::Tenor);
}


TEST(ClefFromStringTest, FallsBackToTrebleForUnknownNames)
{
	EXPECT_EQ(clefFromString(""), Clef::Treble);
	EXPECT_EQ(clefFromString("Soprano"), Clef::Treble);
	EXPECT_EQ(clefFromString("treble"), Clef::Treble) << "Matching is case sensitive, so this is the fallback rather than a hit";
}


//==============================================================================
// midiNoteToStaffPosition
//
// Positions run downward: 0 is the top line, 8 the bottom line, and each step
// of 1 is half a space.
//==============================================================================

TEST(StaffPositionTest, TrebleClefReferenceNotes)
{
	// F5 (77) sits on the top line, E4 (64) on the bottom line.
	EXPECT_EQ(midiNoteToStaffPosition(77, Clef::Treble), 0) << "F5 should be the treble top line";
	EXPECT_EQ(midiNoteToStaffPosition(64, Clef::Treble), 8) << "E4 should be the treble bottom line";

	// B4 (71) is the middle line.
	EXPECT_EQ(midiNoteToStaffPosition(71, Clef::Treble), 4) << "B4 should be the treble middle line";
}


TEST(StaffPositionTest, BassClefReferenceNotes)
{
	// A3 (57) top line, G2 (43) bottom line, D3 (50) middle line.
	EXPECT_EQ(midiNoteToStaffPosition(57, Clef::Bass), 0) << "A3 should be the bass top line";
	EXPECT_EQ(midiNoteToStaffPosition(43, Clef::Bass), 8) << "G2 should be the bass bottom line";
	EXPECT_EQ(midiNoteToStaffPosition(50, Clef::Bass), 4) << "D3 should be the bass middle line";
}


TEST(StaffPositionTest, AltoClefCentresMiddleC)
{
	// The defining property of alto clef: C4 on the middle line.
	EXPECT_EQ(midiNoteToStaffPosition(60, Clef::Alto), 4) << "C4 should be the alto middle line";
}


TEST(StaffPositionTest, TenorClefCentresA3)
{
	EXPECT_EQ(midiNoteToStaffPosition(57, Clef::Tenor), 4) << "A3 should be the tenor middle line";
}


TEST(StaffPositionTest, MiddleCSitsOneLedgerBelowTreble)
{
	// C4 is one ledger line below the treble staff: position 10.
	EXPECT_EQ(midiNoteToStaffPosition(60, Clef::Treble), 10);

	// And one ledger line above the bass staff: position -2.
	EXPECT_EQ(midiNoteToStaffPosition(60, Clef::Bass), -2);
}


TEST(StaffPositionTest, AccidentalsShareTheNaturalsPosition)
{
	// C#4 is drawn on C4's position with a sharp glyph, not a step higher.
	EXPECT_EQ(midiNoteToStaffPosition(61, Clef::Treble), midiNoteToStaffPosition(60, Clef::Treble));

	// F#5 shares F5's line.
	EXPECT_EQ(midiNoteToStaffPosition(78, Clef::Treble), midiNoteToStaffPosition(77, Clef::Treble));
}


TEST(StaffPositionTest, AnOctaveIsSevenDiatonicSteps)
{
	for (int midi = 24; midi <= 96; midi += 12)
	{
		EXPECT_EQ(midiNoteToStaffPosition(midi, Clef::Treble) - midiNoteToStaffPosition(midi + 12, Clef::Treble), 7)
			<< "An octave up should move exactly 7 positions toward the top of the staff (midi " << midi << ")";
	}
}


//==============================================================================
// ledgerOverflow
//==============================================================================

TEST(LedgerOverflowTest, NotesOnTheStaffHaveNoOverflow)
{
	// Every position from the top line to the bottom line.
	for (int midi = 64; midi <= 77; ++midi)
		EXPECT_EQ(ledgerOverflow(midi, Clef::Treble), 0) << "MIDI " << midi << " sits within the treble staff";
}


TEST(LedgerOverflowTest, GrowsWithDistanceFromTheStaff)
{
	// C4 is 2 positions below the treble staff, A3 is 5.
	EXPECT_EQ(ledgerOverflow(60, Clef::Treble), 2);
	EXPECT_EQ(ledgerOverflow(57, Clef::Treble), 4);

	EXPECT_GT(ledgerOverflow(48, Clef::Treble), ledgerOverflow(57, Clef::Treble)) << "Lower notes should overflow further";
}


TEST(LedgerOverflowTest, PicksTheClefThatKeepsNotesClosest)
{
	// The practical use: a cello low C reads better in bass than treble.
	EXPECT_LT(ledgerOverflow(36, Clef::Bass), ledgerOverflow(36, Clef::Treble));

	// A violin's top E reads better in treble than bass.
	EXPECT_LT(ledgerOverflow(88, Clef::Treble), ledgerOverflow(88, Clef::Bass));
}


//==============================================================================
// determineOttava
//==============================================================================

TEST(OttavaTest, NotesNearTheStaffNeedNoMarking)
{
	EXPECT_EQ(determineOttava(71, Clef::Treble), OttavaType::None) << "B4 is on the staff";
	EXPECT_EQ(determineOttava(60, Clef::Treble), OttavaType::None) << "C4 is one ledger line below";
}


TEST(OttavaTest, StaysNoneUpToThreeLedgerLines)
{
	// maxLedgerLines is 3, i.e. 6 half-positions past the staff edge.
	const int lastPlainPositionBelow = Staff::bottomLine + Staff::maxLedgerLines * 2;

	for (int midi = 40; midi <= 100; ++midi)
	{
		const int pos = midiNoteToStaffPosition(midi, Clef::Treble);

		if (pos >= Staff::topLine - Staff::maxLedgerLines * 2 && pos <= lastPlainPositionBelow)
			EXPECT_EQ(determineOttava(midi, Clef::Treble), OttavaType::None) << "MIDI " << midi << " is within the ledger-line budget";
	}
}


TEST(OttavaTest, EscalatesUpwardForVeryHighNotes)
{
	// Piccolo territory: high enough to need 8va, then 15ma.
	EXPECT_EQ(determineOttava(96, Clef::Treble), OttavaType::Ottava8va) << "C7 should call for 8va";
	EXPECT_EQ(determineOttava(108, Clef::Treble), OttavaType::Ottava15ma) << "C8 should escalate to 15ma";
}


TEST(OttavaTest, EscalatesDownwardForVeryLowNotes)
{
	// Double bass / contrabassoon territory in bass clef.
	EXPECT_EQ(determineOttava(28, Clef::Bass), OttavaType::Ottava8vb) << "E1 should call for 8vb";
	EXPECT_EQ(determineOttava(16, Clef::Bass), OttavaType::Ottava15mb) << "E0 should escalate to 15mb";
}


TEST(OttavaTest, DisplacementBringsTheNoteBackTowardTheStaff)
{
	// The point of an ottava: after displacing, the drawn note needs fewer
	// ledger lines than the real one did.
	const int highNotes[] = {96, 100, 103, 108};

	for (int midi : highNotes)
	{
		const auto ottava = determineOttava(midi, Clef::Treble);
		ASSERT_NE(ottava, OttavaType::None) << "MIDI " << midi << " should need an ottava";

		const int drawnMidi = midi + ottavaDisplacement(ottava);
		EXPECT_LT(ledgerOverflow(drawnMidi, Clef::Treble), ledgerOverflow(midi, Clef::Treble)) << "Displacing MIDI " << midi << " should reduce its ledger lines";
	}
}


TEST(OttavaTest, DisplacementDirectionsAreCorrect)
{
	EXPECT_EQ(ottavaDisplacement(OttavaType::None), 0);
	EXPECT_EQ(ottavaDisplacement(OttavaType::Ottava8va), -12) << "8va draws the note an octave lower";
	EXPECT_EQ(ottavaDisplacement(OttavaType::Ottava8vb), 12) << "8vb draws the note an octave higher";
	EXPECT_EQ(ottavaDisplacement(OttavaType::Ottava15ma), -24);
	EXPECT_EQ(ottavaDisplacement(OttavaType::Ottava15mb), 24);
}


//==============================================================================
// deriveTranspositionLabel
//==============================================================================

TEST(TranspositionLabelTest, NamesTheCommonTransposingInstruments)
{
	// Bb trumpet: written C4 sounds Bb3 (a major second lower).
	EXPECT_EQ(deriveTranspositionLabel("C4", "A#3"), "in Bb");

	// F horn: written C4 sounds F3 (a perfect fifth lower).
	EXPECT_EQ(deriveTranspositionLabel("C4", "F3"), "in F");

	// Eb clarinet: written C4 sounds Eb4 (a minor third higher).
	EXPECT_EQ(deriveTranspositionLabel("C4", "D#4"), "in Eb");
}


TEST(TranspositionLabelTest, NonTransposingReadsAsC)
{
	EXPECT_EQ(deriveTranspositionLabel("C4", "C4"), "in C");
	EXPECT_EQ(deriveTranspositionLabel("G3", "G3"), "in C");
}


TEST(TranspositionLabelTest, WholeOctavesReadAsDisplacement)
{
	// Piccolo sounds an octave higher than written.
	EXPECT_EQ(deriveTranspositionLabel("C4", "C5"), "8va");

	// Double bass and contrabassoon sound an octave lower than written.
	EXPECT_EQ(deriveTranspositionLabel("C4", "C3"), "8vb");

	// Two octaves still reads as a displacement, not as "in C".
	EXPECT_EQ(deriveTranspositionLabel("C4", "C6"), "8va");
}


TEST(TranspositionLabelTest, UnparseableNotesFallBackToGenericLabel)
{
	EXPECT_EQ(deriveTranspositionLabel("nonsense", "C4"), "Transposing");
	EXPECT_EQ(deriveTranspositionLabel("C4", ""), "Transposing");
	EXPECT_EQ(deriveTranspositionLabel("H4", "C4"), "Transposing") << "H is not a note name in this scheme";
}

} // namespace NotationGeometryTests
