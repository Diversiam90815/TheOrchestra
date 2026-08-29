/*
  ==============================================================================
	Module			Helper
	Description		Providing helper functions used project-wide
  ==============================================================================
*/

#pragma once

#include <array>
#include <map>
#include <string>
#include <string_view>

#include "Parameters.h"


// A string-keyed lookup map with transparent comparison
template <typename Value>
using StringKeyedMap						  = std::map<std::string, Value, std::less<>>;


inline const StringKeyedMap<Family> familyMap = {
	{FamilyNames::Strings, Family::Strings}, {FamilyNames::Woodwinds, Family::Woodwinds}, {FamilyNames::Brass, Family::Brass}, {FamilyNames::Percussion, Family::Percussion}};


inline const StringKeyedMap<int>		  instrumentMap	  = {{InstrumentNames::Strings::Violin, static_cast<int>(Strings::Violin)},
															 {InstrumentNames::Strings::Viola, static_cast<int>(Strings::Viola)},
															 {InstrumentNames::Strings::Violoncello, static_cast<int>(Strings::Violoncello)},
															 {InstrumentNames::Strings::DoubleBass, static_cast<int>(Strings::DoubleBass)},
															 {InstrumentNames::Brass::FrenchHorn, static_cast<int>(Brass::FrenchHorn)},
															 {InstrumentNames::Brass::TenorTrombone, static_cast<int>(Brass::TenorTrombone)},
															 {InstrumentNames::Brass::BassTrombone, static_cast<int>(Brass::BassTrombone)},
															 {InstrumentNames::Brass::Cimbasso, static_cast<int>(Brass::Cimbasso)},
															 {InstrumentNames::Brass::Trumpet, static_cast<int>(Brass::Trumpet)},
															 {InstrumentNames::Brass::Tuba, static_cast<int>(Brass::Tuba)},
															 {InstrumentNames::Woodwinds::Flute, static_cast<int>(Woodwinds::Flute)},
															 {InstrumentNames::Woodwinds::Clarinet, static_cast<int>(Woodwinds::Clarinet)},
															 {InstrumentNames::Woodwinds::Oboe, static_cast<int>(Woodwinds::Oboe)},
															 {InstrumentNames::Woodwinds::BassClarinet, static_cast<int>(Woodwinds::BassClarinet)},
															 {InstrumentNames::Woodwinds::Piccolo, static_cast<int>(Woodwinds::Piccolo)},
															 {InstrumentNames::Woodwinds::CorAnglais, static_cast<int>(Woodwinds::CorAnglais)},
															 {InstrumentNames::Woodwinds::Bassoon, static_cast<int>(Woodwinds::Bassoon)},
															 {InstrumentNames::Woodwinds::Contrabassoon, static_cast<int>(Woodwinds::Contrabassoon)},
															 {InstrumentNames::Percussion::Timpani, static_cast<int>(Percussion::Timpani)},
															 {InstrumentNames::Percussion::Celeste, static_cast<int>(Percussion::Celeste)},
															 {InstrumentNames::Percussion::Marimba, static_cast<int>(Percussion::Marimba)},
															 {InstrumentNames::Percussion::Harp, static_cast<int>(Percussion::Harp)}};


inline const StringKeyedMap<Articulation> articulationMap = {
	{ArticulationNames::Sustain, Articulation::sustain},	 {ArticulationNames::Staccato, Articulation::staccato}, {ArticulationNames::Spiccato, Articulation::spiccato},
	{ArticulationNames::Pizzicato, Articulation::pizzicato}, {ArticulationNames::Muted, Articulation::mute},		{ArticulationNames::Vibrato, Articulation::vibrato},
	{ArticulationNames::Tremolo, Articulation::tremolo},	 {ArticulationNames::Hits, Articulation::hits},			{ArticulationNames::Rolls, Articulation::rolls}};


inline const std::map<Articulation, std::string> articulationReverseMap = {
	{Articulation::sustain, ArticulationNames::Sustain},	 {Articulation::staccato, ArticulationNames::Staccato}, {Articulation::spiccato, ArticulationNames::Spiccato},
	{Articulation::pizzicato, ArticulationNames::Pizzicato}, {Articulation::mute, ArticulationNames::Muted},		{Articulation::vibrato, ArticulationNames::Vibrato},
	{Articulation::tremolo, ArticulationNames::Tremolo},	 {Articulation::hits, ArticulationNames::Hits},			{Articulation::rolls, ArticulationNames::Rolls}};


inline const StringKeyedMap<Dynamics> dynamicMap = {
	{DynamicNames::Pianissimo, Dynamics::pianissimo},	   {DynamicNames::Piano, Dynamics::piano}, {DynamicNames::MezzoPiano, Dynamics::mezzoPiano},
	{DynamicNames::MezzoForte, Dynamics::mezzoForte},	   {DynamicNames::Forte, Dynamics::forte}, {DynamicNames::Fortissimo, Dynamics::fortissimo},
	{DynamicNames::Fortississimo, Dynamics::fortississimo}};


// Some samples have the velocity layer in their name instead of the dynamic value, so we set them to default values
inline const StringKeyedMap<Dynamics>	   velocityLayerMap = {{"v1", Dynamics::mezzoPiano}, {"v2", Dynamics::mezzoForte}, {"v3", Dynamics::forte}, {"v4", Dynamics::fortissimo}};


inline const std::map<Family, std::string> reverseFamilyMap = {
	{Family::Strings, FamilyNames::Strings}, {Family::Woodwinds, FamilyNames::Woodwinds}, {Family::Brass, FamilyNames::Brass}, {Family::Percussion, FamilyNames::Percussion}};


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and the
   other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
	@param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
	@param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentProfile.h'
	@return                int value of the 3 digit key
*/
template <typename InstrumentEnum>
inline InstrumentID getInstrumentKey(Family family, InstrumentEnum instrument)
{
	return static_cast<InstrumentID>(family) * 100 + static_cast<InstrumentID>(instrument);
}


// Reverse instrument map using the full key:
inline const std::map<InstrumentID, std::string> reverseInstrumentMap = {{getInstrumentKey(Family::Strings, Strings::Violin), InstrumentNames::Strings::Violin},
																		 {getInstrumentKey(Family::Strings, Strings::Viola), InstrumentNames::Strings::Viola},
																		 {getInstrumentKey(Family::Strings, Strings::Violoncello), InstrumentNames::Strings::Violoncello},
																		 {getInstrumentKey(Family::Strings, Strings::DoubleBass), InstrumentNames::Strings::DoubleBass},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Piccolo), InstrumentNames::Woodwinds::Piccolo},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Flute), InstrumentNames::Woodwinds::Flute},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Oboe), InstrumentNames::Woodwinds::Oboe},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::CorAnglais), InstrumentNames::Woodwinds::CorAnglais},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Clarinet), InstrumentNames::Woodwinds::Clarinet},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::BassClarinet), InstrumentNames::Woodwinds::BassClarinet},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Bassoon), InstrumentNames::Woodwinds::Bassoon},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Contrabassoon), InstrumentNames::Woodwinds::Contrabassoon},
																		 {getInstrumentKey(Family::Brass, Brass::FrenchHorn), InstrumentNames::Brass::FrenchHorn},
																		 {getInstrumentKey(Family::Brass, Brass::Trumpet), InstrumentNames::Brass::Trumpet},
																		 {getInstrumentKey(Family::Brass, Brass::TenorTrombone), InstrumentNames::Brass::TenorTrombone},
																		 {getInstrumentKey(Family::Brass, Brass::BassTrombone), InstrumentNames::Brass::BassTrombone},
																		 {getInstrumentKey(Family::Brass, Brass::Cimbasso), InstrumentNames::Brass::Cimbasso},
																		 {getInstrumentKey(Family::Brass, Brass::Tuba), InstrumentNames::Brass::Tuba},
																		 {getInstrumentKey(Family::Percussion, Percussion::Harp), InstrumentNames::Percussion::Harp},
																		 {getInstrumentKey(Family::Percussion, Percussion::Celeste), InstrumentNames::Percussion::Celeste},
																		 {getInstrumentKey(Family::Percussion, Percussion::Timpani), InstrumentNames::Percussion::Timpani},
																		 {getInstrumentKey(Family::Percussion, Percussion::Marimba), InstrumentNames::Percussion::Marimba}};


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument names.
	@param                 [IN] String of the family
	@param                 [IN] String of the instrument
	@return                int value of the 3 digit key, or 0 if either name is unknown
*/
inline InstrumentID								 getInstrumentKey(const std::string &family, const std::string &instrument)
{
	const auto familyIt		= familyMap.find(family);
	const auto instrumentIt = instrumentMap.find(instrument);

	if (familyIt == familyMap.end() || instrumentIt == instrumentMap.end())
		return 0;

	const Family familyKey	   = familyIt->second;
	const int	 instrumentKey = instrumentIt->second;

	switch (familyKey)
	{
	case Family::Strings: return getInstrumentKey(familyKey, static_cast<Strings>(instrumentKey));
	case Family::Woodwinds: return getInstrumentKey(familyKey, static_cast<Woodwinds>(instrumentKey));
	case Family::Brass: return getInstrumentKey(familyKey, static_cast<Brass>(instrumentKey));
	case Family::Percussion: return getInstrumentKey(familyKey, static_cast<Percussion>(instrumentKey));
	default: return 0;
	}
}


/*
	@brief                 Looks up an instrument's display name by key.
	@return                The name, or an empty string if the key is unknown. Previously this
						   used map::at and threw std::out_of_range with no handler above it.
*/
inline std::string getInstrumentNameFromKey(InstrumentID key)
{
	const auto it = reverseInstrumentMap.find(key);
	return it != reverseInstrumentMap.end() ? it->second : std::string{};
}


/*
	@brief                 Looks up the family name from the leading digit of an instrument key.
	@return                The name, or an empty string if the key does not map to a family.
*/
inline std::string getFamilyNameFromKey(InstrumentID key)
{
	const auto it = reverseFamilyMap.find(static_cast<Family>(key / 100));
	return it != reverseFamilyMap.end() ? it->second : std::string{};
}


/*
@brief                 Turns the note name in accordance with the octave in form of E4, C3,.. to the corresponding midi note value. Middle C (C4) corresponds to a midi note value
of 60.
@param                 [IN] notename -> The name of the note and the octave -> E4, C6, C#2, Gb3,...
@return                Midi note value as an int of the note given. If an error occured, it returns -1.
*/
inline int turnNotenameIntoMidinumber(const std::string &notename)
{
	if (notename.size() < 2)
		return -1;

	const char octaveChar = notename.back();
	if (octaveChar < '0' || octaveChar > '9')
		return -1;

	const int			   octave = octaveChar - '0';
	const std::string_view noteWithoutOctave(notename.data(), notename.size() - 1);

	// A fixed table rather than a std::map rebuilt on every call - this runs once
	// per note name while parsing the instrument catalogue.
	struct NoteEntry
	{
		std::string_view name;
		int				 semitone;
	};

	static constexpr std::array<NoteEntry, 17> kNoteToMidi = {{{"C", 0},
															   {"C#", 1},
															   {"Db", 1},
															   {"D", 2},
															   {"D#", 3},
															   {"Eb", 3},
															   {"E", 4},
															   {"F", 5},
															   {"F#", 6},
															   {"Gb", 6},
															   {"G", 7},
															   {"G#", 8},
															   {"Ab", 8},
															   {"A", 9},
															   {"A#", 10},
															   {"Bb", 10},
															   {"B", 11}}};

	for (const auto &entry : kNoteToMidi)
	{
		if (entry.name == noteWithoutOctave)
			return 12 * (octave + 1) + entry.semitone;
	}

	return -1;
}
