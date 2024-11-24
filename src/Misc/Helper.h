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


static std::map<String, int>	instrumentMap = {{ViolinName, Strings::Violin},
												 {ViolaName, Strings::Viola},
												 {VioloncelloName, Strings::Violoncello},
												 {DoubleBassName, Strings::DoubleBass},
												 {FrenchHornName, Brass::FrenchHorn},
												 {TenorTromboneName, Brass::TenorTrombone},
												 {BassTromboneName, Brass::BassTrombone},
												 {TrumpetName, Brass::Trumpet},
												 {TubaName, Brass::Tuba},
												 {FluteName, Woodwinds::Flute},
												 {ClarinetName, Woodwinds::Clarinet},
												 {OboeName, Woodwinds::Oboe},
												 {BassClarinetName, Woodwinds::BassClarinet},
												 {PiccoloName, Woodwinds::Piccolo},
												 {CorAnglaisName, Woodwinds::CorAnglais},
												 {BassoonName, Woodwinds::Bassoon},
												 {ContrabassoonName, Woodwinds::Contrabassoon},
												 {TimpaniName, Percussion::Timpani},
												 {CelesteName, Percussion::Celeste},
												 {MarimbaName, Percussion::Marimba},
												 {HarpName, Percussion::Harp}};


/*
	@brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and the
   other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
	@param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
	@param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentInfo.h'
	@return                int value of the 3 digit key
*/
static int						getInstrumentKey(int family, int instrument)
{
	int key = family * 100 + instrument;
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
	int familyKey	  = 0;
	int instrumentKey = 0;

	familyKey		  = familyMap.at(family);
	instrumentKey	  = instrumentMap.at(instrument);

	if (familyKey == 0 && instrumentKey == 0)
		return 0;

	return getInstrumentKey(familyKey, instrumentKey);
}
