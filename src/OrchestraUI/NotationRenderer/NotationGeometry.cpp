/*
  ==============================================================================
	Module			NotationGeometry
	Description		Pure staff maths - where a MIDI note lands on a staff, when
					an ottava is needed, and how a written/sounding pair reads
					as a transposition
  ==============================================================================
*/

#include "NotationGeometry.h"
#include "Helper.h"

#include <array>


namespace
{
// Chromatic note class 
constexpr std::array<int, 12> kChromaticToDiatonic	  = {0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6};

constexpr int				  kDiatonicStepsPerOctave = 7;


struct ClefReference
{
	int staffPosition;	  // where the reference note sits on the staff
	int diatonicPosition; // absolute diatonic position of that note
};


ClefReference referenceFor(Clef clef)
{
	switch (clef)
	{
	// F5 on the top line. F5 = octave 5, F = diatonic 3.
	case Clef::Treble: return {0, 5 * kDiatonicStepsPerOctave + 3};

	// A3 on the top line. A3 = octave 3, A = diatonic 5.
	case Clef::Bass: return {0, 3 * kDiatonicStepsPerOctave + 5};

	// C4 on the middle line.
	case Clef::Alto: return {4, 4 * kDiatonicStepsPerOctave + 0};

	// A3 on the middle line.
	case Clef::Tenor: return {4, 3 * kDiatonicStepsPerOctave + 5};
	}

	return {0, 5 * kDiatonicStepsPerOctave + 3};
}
} // namespace


Clef clefFromString(const std::string &name)
{
	if (name == "Treble")
		return Clef::Treble;
	if (name == "Bass")
		return Clef::Bass;
	if (name == "Alto")
		return Clef::Alto;
	if (name == "Tenor")
		return Clef::Tenor;

	return Clef::Treble;
}


int midiNoteToStaffPosition(int midiNote, Clef clef)
{
	const int  noteClass				= ((midiNote % 12) + 12) % 12;
	const int  octave					= (midiNote / 12) - 1; // MIDI octave: C4 = 4
	const int  diatonicNote				= kChromaticToDiatonic[static_cast<size_t>(noteClass)];

	const int  absoluteDiatonicPosition = octave * kDiatonicStepsPerOctave + diatonicNote;

	const auto reference				= referenceFor(clef);

	// Positions increase downward, so subtract from the reference.
	return reference.staffPosition + (reference.diatonicPosition - absoluteDiatonicPosition);
}


int ledgerOverflow(int midiNote, Clef clef)
{
	const int staffPos = midiNoteToStaffPosition(midiNote, clef);

	if (staffPos < Staff::topLine)
		return Staff::topLine - staffPos;

	if (staffPos > Staff::bottomLine)
		return staffPos - Staff::bottomLine;

	return 0;
}


OttavaType determineOttava(int midiNote, Clef clef)
{
	// Every 2 staff positions past the staff edge is one more ledger line.
	const int threshold = Staff::maxLedgerLines * 2;
	const int staffPos	= midiNoteToStaffPosition(midiNote, clef);

	if (staffPos < Staff::topLine - threshold)
	{
		const int afterOneOctave = midiNoteToStaffPosition(midiNote - 12, clef);
		return (afterOneOctave < Staff::topLine - threshold) ? OttavaType::Ottava15ma : OttavaType::Ottava8va;
	}

	if (staffPos > Staff::bottomLine + threshold)
	{
		const int afterOneOctave = midiNoteToStaffPosition(midiNote + 12, clef);
		return (afterOneOctave > Staff::bottomLine + threshold) ? OttavaType::Ottava15mb : OttavaType::Ottava8vb;
	}

	return OttavaType::None;
}


int ottavaDisplacement(OttavaType ottava)
{
	switch (ottava)
	{
	case OttavaType::Ottava8va: return -12;
	case OttavaType::Ottava8vb: return 12;
	case OttavaType::Ottava15ma: return -24;
	case OttavaType::Ottava15mb: return 24;
	case OttavaType::None:
	default: return 0;
	}
}


std::string deriveTranspositionLabel(const std::string &writtenLow, const std::string &soundingLow)
{
	const int writtenMidi  = turnNotenameIntoMidinumber(writtenLow);
	const int soundingMidi = turnNotenameIntoMidinumber(soundingLow);

	// turnNotenameIntoMidinumber signals failure with -1; MIDI 0 (C-1) is valid.
	if (writtenMidi < 0 || soundingMidi < 0)
		return "Transposing";

	const int interval	 = writtenMidi - soundingMidi;
	const int normalised = ((interval % 12) + 12) % 12;

	// A whole number of octaves is a displacement, not a key.
	if (normalised == 0)
		return interval == 0 ? "in C" : (interval > 0 ? "8vb" : "8va");

	static constexpr std::array<const char *, 12> kKeyNames = {
		"in C",	 // 0
		"in B",	 // 1
		"in Bb", // 2  (Clarinet, Trumpet)
		"in A",	 // 3
		"in Ab", // 4
		"in G",	 // 5  (Alto Flute)
		"in Gb", // 6
		"in F",	 // 7  (French Horn, Cor Anglais)
		"in E",	 // 8
		"in Eb", // 9  (Alto Sax, Eb Clarinet)
		"in D",	 // 10
		"in Db", // 11
	};

	return kKeyNames[static_cast<size_t>(normalised)];
}
