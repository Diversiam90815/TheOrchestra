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

#include "JuceIncludes.h"
#include "Parameters.h"



inline const std::map<std::string, Family, std::less<>>		  familyMap			  = {{StringsName, Family::Strings},
																					 {WoodwindsName, Family::Woodwinds},
																					 {BrassName, Family::Brass},
																					 {PercussionName, Family::Percussion}};


inline const std::map<std::string, int, std::less<>>		  instrumentMap		  = {{ViolinName, static_cast<int>(Strings::Violin)},
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


inline const std::map<std::string, Articulation, std::less<>> articulationMap	  = {
	   {SustainArticulation, Articulation::sustain},   {StaccatoArticulation, Articulation::staccato}, {SpiccatoArticulation, Articulation::spiccato},
	   {PizzicatoArticulation, Articulation::pizzicato}, {MutedArticulation, Articulation::mute},		  {VibratoArticulation, Articulation::vibrato},
	   {TremoloArticulation, Articulation::tremolo},   {HitsArticulation, Articulation::hits},		  {RollsArticulation, Articulation::rolls}};


inline const std::map<Articulation, std::string>			  articulationReverseMap = {
				 {Articulation::sustain, SustainArticulation},	 {Articulation::staccato, StaccatoArticulation}, {Articulation::spiccato, SpiccatoArticulation},
				 {Articulation::pizzicato, PizzicatoArticulation}, {Articulation::mute, MutedArticulation},		 {Articulation::vibrato, VibratoArticulation},
				 {Articulation::tremolo, TremoloArticulation},	 {Articulation::hits, HitsArticulation},		 {Articulation::rolls, RollsArticulation}};


inline const std::map<std::string, Dynamics, std::less<>>	  dynamicMap		  = {{PianissimoDynamic, Dynamics::pianissimo}, {PianoDynamic, Dynamics::piano},
																					 {MezzoPianoDynamic, Dynamics::mezzoPiano}, {MezzoForteDynamic, Dynamics::mezzoForte},
																					 {ForteDynamic, Dynamics::forte},		   {FortissimoDynamic, Dynamics::fortissimo}};


// Some samples have the velocity layer in their name instead of the dynamic value, so we set them to default values
inline const std::map<std::string, Dynamics, std::less<>>	  velocityLayerMap	  = {
		{"v1", Dynamics::mezzoPiano}, {"v2", Dynamics::mezzoForte}, {"v3", Dynamics::forte}, {"v4", Dynamics::fortissimo}};


inline const std::map<Family, std::string>					  reverseFamilyMap	  = {
					 {Family::Strings, StringsName}, {Family::Woodwinds, WoodwindsName}, {Family::Brass, BrassName}, {Family::Percussion, PercussionName}};


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
inline const std::map<InstrumentID, std::string> reverseInstrumentMap = {{getInstrumentKey(Family::Strings, Strings::Violin), ViolinName},
																		 {getInstrumentKey(Family::Strings, Strings::Viola), ViolaName},
																		 {getInstrumentKey(Family::Strings, Strings::Violoncello), VioloncelloName},
																		 {getInstrumentKey(Family::Strings, Strings::DoubleBass), DoubleBassName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Piccolo), PiccoloName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Flute), FluteName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Oboe), OboeName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::CorAnglais), CorAnglaisName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Clarinet), ClarinetName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::BassClarinet), BassClarinetName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Bassoon), BassoonName},
																		 {getInstrumentKey(Family::Woodwinds, Woodwinds::Contrabassoon), ContrabassoonName},
																		 {getInstrumentKey(Family::Brass, Brass::FrenchHorn), FrenchHornName},
																		 {getInstrumentKey(Family::Brass, Brass::Trumpet), TrumpetName},
																		 {getInstrumentKey(Family::Brass, Brass::TenorTrombone), TenorTromboneName},
																		 {getInstrumentKey(Family::Brass, Brass::BassTrombone), BassTromboneName},
																		 {getInstrumentKey(Family::Brass, Brass::Cimbasso), CimbassoName},
																		 {getInstrumentKey(Family::Brass, Brass::Tuba), TubaName},
																		 {getInstrumentKey(Family::Percussion, Percussion::Harp), HarpName},
																		 {getInstrumentKey(Family::Percussion, Percussion::Celeste), CelesteName},
																		 {getInstrumentKey(Family::Percussion, Percussion::Timpani), TimpaniName},
																		 {getInstrumentKey(Family::Percussion, Percussion::Marimba), MarimbaName}};


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument names.
	@param                 [IN] String of the family
	@param                 [IN] String of the instrument
	@return                int value of the 3 digit key, or 0 if either name is unknown
*/
inline InstrumentID getInstrumentKey(const std::string &family, const std::string &instrument)
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

	const int				octave			 = octaveChar - '0';
	const std::string_view	noteWithoutOctave(notename.data(), notename.size() - 1);

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
