/*
  ==============================================================================
	Module			NotationGeometry
	Description		Pure staff maths - where a MIDI note lands on a staff, when
					an ottava is needed, and how a written/sounding pair reads
					as a transposition
  ==============================================================================
*/

#pragma once

#include <string>


enum class Clef
{
	Treble,
	Bass,
	Alto,
	Tenor,
};


enum class OttavaType
{
	None,
	Ottava8va,	// 8va  - display note one octave lower than actual
	Ottava8vb,	// 8vb  - display note one octave higher than actual
	Ottava15ma, // 15ma - display note two octaves lower than actual
	Ottava15mb, // 15mb - display note two octaves higher than actual
};


namespace Staff
{
constexpr int topLine		 = 0;
constexpr int bottomLine	 = 8;
constexpr int maxLedgerLines = 3;
} // namespace Staff


Clef		clefFromString(const std::string &name);

int			midiNoteToStaffPosition(int midiNote, Clef clef);

int			ledgerOverflow(int midiNote, Clef clef);

OttavaType	determineOttava(int midiNote, Clef clef);

int			ottavaDisplacement(OttavaType ottava);

std::string deriveTranspositionLabel(const std::string &writtenLow, const std::string &soundingLow);
