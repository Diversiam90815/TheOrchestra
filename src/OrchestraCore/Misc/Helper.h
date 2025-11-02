/*
  ==============================================================================
	Module			Helper
	Description		Providing helper functions used project-wide
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"


static std::map<std::string, Family>	   familyMap	   = {{std::string(StringsName), Family::Strings},
															  {std::string(WoodwindsName), Family::Woodwinds},
															  {std::string(BrassName), Family::Brass},
															  {std::string(PercussionName), Family::Percussion}};


static std::map<std::string, int>		   instrumentMap   = {{std::string(ViolinName), static_cast<int>(Strings::Violin)},
															  {std::string(ViolaName), static_cast<int>(Strings::Viola)},
															  {std::string(VioloncelloName), static_cast<int>(Strings::Violoncello)},
															  {std::string(DoubleBassName), static_cast<int>(Strings::DoubleBass)},
															  {std::string(FrenchHornName), static_cast<int>(Brass::FrenchHorn)},
															  {std::string(TenorTromboneName), static_cast<int>(Brass::TenorTrombone)},
															  {std::string(BassTromboneName), static_cast<int>(Brass::BassTrombone)},
															  {std::string(CimbassoName), static_cast<int>(Brass::Cimbasso)},
															  {std::string(TrumpetName), static_cast<int>(Brass::Trumpet)},
															  {std::string(TubaName), static_cast<int>(Brass::Tuba)},
															  {std::string(FluteName), static_cast<int>(Woodwinds::Flute)},
															  {std::string(ClarinetName), static_cast<int>(Woodwinds::Clarinet)},
															  {std::string(OboeName), static_cast<int>(Woodwinds::Oboe)},
															  {std::string(BassClarinetName), static_cast<int>(Woodwinds::BassClarinet)},
															  {std::string(PiccoloName), static_cast<int>(Woodwinds::Piccolo)},
															  {std::string(CorAnglaisName), static_cast<int>(Woodwinds::CorAnglais)},
															  {std::string(BassoonName), static_cast<int>(Woodwinds::Bassoon)},
															  {std::string(ContrabassoonName), static_cast<int>(Woodwinds::Contrabassoon)},
															  {std::string(TimpaniName), static_cast<int>(Percussion::Timpani)},
															  {std::string(CelesteName), static_cast<int>(Percussion::Celeste)},
															  {std::string(MarimbaName), static_cast<int>(Percussion::Marimba)},
															  {std::string(HarpName), static_cast<int>(Percussion::Harp)}};


static std::map<std::string, Articulation> articulationMap = {
	{std::string(SustainArticulation), Articulation::sustain},	 {std::string(StaccatoArticulation), Articulation::staccato},
	{std::string(SpiccatoArticulation), Articulation::spiccato}, {std::string(PizzicatoArticulation), Articulation::pizzicato},
	{std::string(MutedArticulation), Articulation::mute},		 {std::string(VibratoArticulation), Articulation::vibrato},
	{std::string(TremoloArticulation), Articulation::tremolo},	 {std::string(HitsArticulation), Articulation::hits},
	{std::string(RollsArticulation), Articulation::rolls}};

static std::map<Articulation, std::string> articulationReverseMap = {
	{Articulation::sustain, std::string(SustainArticulation)},	 {Articulation::staccato, std::string(StaccatoArticulation)},
	{Articulation::spiccato, std::string(SpiccatoArticulation)}, {Articulation::pizzicato, std::string(PizzicatoArticulation)},
	{Articulation::mute, std::string(MutedArticulation)},		 {Articulation::vibrato, std::string(VibratoArticulation)},
	{Articulation::tremolo, std::string(TremoloArticulation)},	 {Articulation::hits, std::string(HitsArticulation)},
	{Articulation::rolls, std::string(RollsArticulation)}};


static std::map<std::string, Dynamics> dynamicMap		= {{std::string(PianissimoDynamic), Dynamics::pianissimo}, {std::string(PianoDynamic), Dynamics::piano},
														   {std::string(MezzoPianoDynamic), Dynamics::mezzoPiano}, {std::string(MezzoForteDynamic), Dynamics::mezzoForte},
														   {std::string(ForteDynamic), Dynamics::forte},		   {std::string(FortissimoDynamic), Dynamics::fortissimo}};


// Some samples have the velocity layer in their name instead of the dynamic value, so we set them to default values
static std::map<std::string, Dynamics> velocityLayerMap = {
	{std::string("v1"), Dynamics::mezzoPiano}, {std::string("v2"), Dynamics::mezzoForte}, {std::string("v3"), Dynamics::forte}, {std::string("v4"), Dynamics::fortissimo}};


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and the
   other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
	@param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
	@param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentInfo.h'
	@return                int value of the 3 digit key
*/
template <typename InstrumentEnum>
static InstrumentID getInstrumentKey(Family family, InstrumentEnum instrument)
{
	InstrumentID key = static_cast<InstrumentID>(family) * 100 + static_cast<InstrumentID>(instrument);
	return key;
}


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and
	the other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
	@param                 [IN] String of the family
	@param                 [IN] String of the instrument
	@return                int value of the 3 digit key
*/
static InstrumentID getInstrumentKey(std::string &family, std::string &instrument)
{
	Family familyKey;
	int	   instrumentKey{0};

	familyKey	  = familyMap.at(family);

	instrumentKey = instrumentMap.at(instrument);

	switch (familyKey)
	{
	case Family::Strings: return getInstrumentKey(familyKey, static_cast<Strings>(instrumentKey));
	case Family::Woodwinds: return getInstrumentKey(familyKey, static_cast<Woodwinds>(instrumentKey));
	case Family::Brass: return getInstrumentKey(familyKey, static_cast<Brass>(instrumentKey));
	case Family::Percussion: return getInstrumentKey(familyKey, static_cast<Percussion>(instrumentKey));
	default: return 0;
	}
}


static std::map<Family, std::string> reverseFamilyMap = {
	{Family::Strings, StringsName}, {Family::Woodwinds, WoodwindsName}, {Family::Brass, BrassName}, {Family::Percussion, PercussionName}};



// Reverse instrument map using the full key:
static std::map<InstrumentID, std::string> reverseInstrumentMap = {{getInstrumentKey(Family::Strings, Strings::Violin), std::string(ViolinName)},
																   {getInstrumentKey(Family::Strings, Strings::Viola), std::string(ViolaName)},
																   {getInstrumentKey(Family::Strings, Strings::Violoncello), std::string(VioloncelloName)},
																   {getInstrumentKey(Family::Strings, Strings::DoubleBass), std::string(DoubleBassName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::Piccolo), std::string(PiccoloName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::Flute), std::string(FluteName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::Oboe), std::string(OboeName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::CorAnglais), std::string(CorAnglaisName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::Clarinet), std::string(ClarinetName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::BassClarinet), std::string(BassClarinetName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::Bassoon), std::string(BassoonName)},
																   {getInstrumentKey(Family::Woodwinds, Woodwinds::Contrabassoon), std::string(ContrabassoonName)},
																   {getInstrumentKey(Family::Brass, Brass::FrenchHorn), std::string(FrenchHornName)},
																   {getInstrumentKey(Family::Brass, Brass::Trumpet), std::string(TrumpetName)},
																   {getInstrumentKey(Family::Brass, Brass::TenorTrombone), std::string(TenorTromboneName)},
																   {getInstrumentKey(Family::Brass, Brass::BassTrombone), std::string(BassTromboneName)},
																   {getInstrumentKey(Family::Brass, Brass::Cimbasso), std::string(CimbassoName)},
																   {getInstrumentKey(Family::Brass, Brass::Tuba), std::string(TubaName)},
																   {getInstrumentKey(Family::Percussion, Percussion::Harp), std::string(HarpName)},
																   {getInstrumentKey(Family::Percussion, Percussion::Celeste), std::string(CelesteName)},
																   {getInstrumentKey(Family::Percussion, Percussion::Timpani), std::string(TimpaniName)},
																   {getInstrumentKey(Family::Percussion, Percussion::Marimba), std::string(MarimbaName)}};



static std::string						   getInstrumentNameFromKey(InstrumentID key)
{
	return reverseInstrumentMap.at(key);
}


static std::string getFamilyNameFromKey(InstrumentID key)
{
	int familyVal = key / 100;
	return reverseFamilyMap.at(static_cast<Family>(familyVal));
}


/*
	@brief                 Splits a String containing a range into the lower and higher note
	@param                 [IN] range -> Range of notes (e.g. G4 - E6)
	@param                 [IN] getLower -> if true, the lower note will be returned, false otherwise
	@return                Note Value as a String
*/
static std::string getLowerOrHigherNote(const std::string &range, bool getLower)
{
	// Split range into two parts (lower and higher note)
	juce::StringArray rangeParts = juce::StringArray::fromTokens(range, "-", "");

	if (rangeParts.size() != 2)
		return {};

	// Trim whitespaces
	std::string lowerNote  = rangeParts[0].trim().toStdString();
	std::string higherNote = rangeParts[1].trim().toStdString();

	return getLower ? lowerNote : higherNote;
}


/*
	@brief                 Splits a by a colon separated String into two parts
	@param                 [IN] Colonized String ( part A : part B)
	@param                 [IN] firstPart -> if true, the left part will be returned, false otherwise
	@return                Left or right value as a String
*/
static std::string splitColonizedStrings(const std::string &colonizedString, bool firstPart)
{
	// Find the colon (:) and split the string
	juce::StringArray parts = juce::StringArray::fromTokens(colonizedString, ":", "");

	if (parts.size() != 2)
		return {};

	// Trim whitespaces
	std::string leftPart  = parts[0].trim().toStdString();
	std::string rightPart = parts[1].trim().toStdString();

	return firstPart ? leftPart : rightPart;
}


/*
@brief                 Turns the note name in accordance with the octave in form of E4, C3,.. to the corresponding midi note value. Middle C (C4) corresponds to a midi note value
of 60.
@param                 [IN] notename -> The name of the note and the octave -> E4, C6, C#2, Gb3,...
@return                Midi note value as an int of the note given. If there an error occured, it returns -1.
*/
static int turnNotenameIntoMidinumber(juce::String notename)
{
	wchar_t					   wOctave				 = notename.getLastCharacter();
	int						   octave				 = wOctave - '0';

	juce::String			   juceNoteWithoutOctave = notename.dropLastCharacters(1);
	std::string				   noteWithoutOctave	 = juceNoteWithoutOctave.toStdString();

	std::map<std::string, int> noteToMidi			 = {{"C", 0},  {"C#", 1}, {"Db", 1}, {"D", 2},	{"D#", 3}, {"Eb", 3},  {"E", 4},   {"F", 5}, {"F#", 6},
														{"Gb", 6}, {"G", 7},  {"G#", 8}, {"Ab", 8}, {"A", 9},  {"A#", 10}, {"Bb", 10}, {"B", 11}};

	int						   noteValue			 = 0;

	if (noteToMidi.find(noteWithoutOctave) != noteToMidi.end())
	{
		noteValue = noteToMidi[noteWithoutOctave];
	}

	else
		return -1;

	int midiNumber = 12 * (octave + 1) + noteValue;

	return midiNumber;
}
