/*
  ==============================================================================

	Module			Helper
	Description		Providing helper functions used project-wide

  ==============================================================================
*/

#pragma once

#include "InstrumentInfo.h"
#include "Parameters.h"


static std::map<String, Family> familyMap = {{StringsName, Family::Strings}, {WoodwindsName, Family::Woodwinds}, {BrassName, Family::Brass}, {PercussionName, Family::Percussion}};


static std::map<String, int>	instrumentMap		  = {{ViolinName, static_cast<int>(Strings::Violin)},
														 {ViolaName, static_cast<int>(Strings::Viola)},
														 {VioloncelloName, static_cast<int>(Strings::Violoncello)},
														 {DoubleBassName, static_cast<int>(Strings::DoubleBass)},
														 {FrenchHornName, static_cast<int>(Brass::FrenchHorn)},
														 {TenorTromboneName, static_cast<int>(Brass::TenorTrombone)},
														 {BassTromboneName, static_cast<int>(Brass::BassTrombone)},
														 {CimbassoName, static_cast<int>(Brass::Cimbasso)},
														 {TrumpetName, static_cast<int>(Brass::Trumpet)},
														 {TubaName, static_cast<int>(Brass::Tuba)},
														 {FluteName, static_cast<int>(Woodwinds::Flute)},
														 {ClarinetName, static_cast<int>(Woodwinds::Clarinet)},
														 {OboeName, static_cast<int>(Woodwinds::Oboe)},
														 {BassClarinetName, static_cast<int>(Woodwinds::BassClarinet)},
														 {PiccoloName, static_cast<int>(Woodwinds::Piccolo)},
														 {CorAnglaisName, static_cast<int>(Woodwinds::CorAnglais)},
														 {BassoonName, static_cast<int>(Woodwinds::Bassoon)},
														 {ContrabassoonName, static_cast<int>(Woodwinds::Contrabassoon)},
														 {TimpaniName, static_cast<int>(Percussion::Timpani)},
														 {CelesteName, static_cast<int>(Percussion::Celeste)},
														 {MarimbaName, static_cast<int>(Percussion::Marimba)},
														 {HarpName, static_cast<int>(Percussion::Harp)}};


static std::map<String, Articulation> articulationMap = {
	{SustainArticulation, Articulation::sustain},	  {StaccatoArticulation, Articulation::staccato}, {SpiccatoArticulation, Articulation::spiccato},
	{PizzicatoArticulation, Articulation::pizzicato}, {MutedArticulation, Articulation::mute},		  {VibratoArticulation, Articulation::vibrato},
	{TremoloArticulation, Articulation::tremolo},	  {HitsArticulation, Articulation::hits},		  {RollsArticulation, Articulation::rolls}};


static std::map<String, Dynamics> dynamicMap = {{PianissimoDynamic, Dynamics::pianissimo}, {PianoDynamic, Dynamics::piano}, {MezzoPianoDynamic, Dynamics::mezzoPiano},
												{MezzoForteDynamic, Dynamics::mezzoForte}, {ForteDynamic, Dynamics::forte}, {FortissimoDynamic, Dynamics::fortissimo}};


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and the
   other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
	@param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
	@param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentInfo.h'
	@return                int value of the 3 digit key
*/
template <typename InstrumentEnum>
static int getInstrumentKey(Family family, InstrumentEnum instrument)
{
	int key = static_cast<int>(family) * 100 + static_cast<int>(instrument);
	return key;
}


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and
	the other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
	@param                 [IN] String of the family
	@param                 [IN] String of the instrument
	@return                int value of the 3 digit key
*/
static int getInstrumentKey(String &family, String &instrument)
{
	Family		   familyKey;
	int instrumentKey{0};

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


static std::map<Family, String> reverseFamilyMap = {
	{Family::Strings, StringsName}, {Family::Woodwinds, WoodwindsName}, {Family::Brass, BrassName}, {Family::Percussion, PercussionName}};



// Reverse instrument map using the full key:
static std::map<int, String> reverseInstrumentMap = {
	{getInstrumentKey(Family::Strings, Strings::Violin), ViolinName},			{getInstrumentKey(Family::Strings, Strings::Viola), ViolaName},
	{getInstrumentKey(Family::Strings, Strings::Violoncello), VioloncelloName}, {getInstrumentKey(Family::Strings, Strings::DoubleBass), DoubleBassName},
	{getInstrumentKey(Family::Woodwinds, Woodwinds::Piccolo), PiccoloName},		{getInstrumentKey(Family::Woodwinds, Woodwinds::Flute), FluteName},
	{getInstrumentKey(Family::Woodwinds, Woodwinds::Oboe), OboeName},			{getInstrumentKey(Family::Woodwinds, Woodwinds::CorAnglais), CorAnglaisName},
	{getInstrumentKey(Family::Woodwinds, Woodwinds::Clarinet), ClarinetName},	{getInstrumentKey(Family::Woodwinds, Woodwinds::BassClarinet), BassClarinetName},
	{getInstrumentKey(Family::Woodwinds, Woodwinds::Bassoon), BassoonName},		{getInstrumentKey(Family::Woodwinds, Woodwinds::Contrabassoon), ContrabassoonName},
	{getInstrumentKey(Family::Brass, Brass::FrenchHorn), FrenchHornName},		{getInstrumentKey(Family::Brass, Brass::Trumpet), TrumpetName},
	{getInstrumentKey(Family::Brass, Brass::TenorTrombone), TenorTromboneName}, {getInstrumentKey(Family::Brass, Brass::BassTrombone), BassTromboneName},
	{getInstrumentKey(Family::Brass, Brass::Cimbasso), CimbassoName},			{getInstrumentKey(Family::Brass, Brass::Tuba), TubaName},
	{getInstrumentKey(Family::Percussion, Percussion::Harp), HarpName},			{getInstrumentKey(Family::Percussion, Percussion::Celeste), CelesteName},
	{getInstrumentKey(Family::Percussion, Percussion::Timpani), TimpaniName},	{getInstrumentKey(Family::Percussion, Percussion::Marimba), MarimbaName}};



static std::string getInstrumentNameFromKey(int key)
{
	return reverseInstrumentMap.at(key).toStdString();
}


static std::string getFamilyNameFromKey(int key)
{
	int familyVal = key / 100;
	return reverseFamilyMap.at(static_cast<Family>(familyVal)).toStdString();
}


/*
	@brief                 Splits a String containing a range into the lower and higher note
	@param                 [IN] range -> Range of notes (e.g. G4 - E6)
	@param                 [IN] getLower -> if true, the lower note will be returned, false otherwise
	@return                Note Value as a String
*/
static String getLowerOrHigherNote(const String &range, bool getLower)
{
	// Split range into two parts (lower and higher note)
	StringArray rangeParts = StringArray::fromTokens(range, "-", "");

	if (rangeParts.size() != 2)
		return {};

	// Trim whitespaces
	String lowerNote  = rangeParts[0].trim();
	String higherNote = rangeParts[1].trim();

	return getLower ? lowerNote : higherNote;
}


/*
	@brief                 Splits a by a colon separated String into two parts
	@param                 [IN] Colonized String ( part A : part B)
	@param                 [IN] firstPart -> if true, the left part will be returned, false otherwise
	@return                Left or right value as a String
*/
static String splitColonizedStrings(String &colonizedString, bool firstPart)
{
	// Find the colon (:) and split the string
	StringArray parts = StringArray::fromTokens(colonizedString, ":", "");

	if (parts.size() != 2)
		return {};

	// Trim whitespaces
	String leftPart	 = parts[0].trim();
	String rightPart = parts[1].trim();

	return firstPart ? leftPart : rightPart;
}