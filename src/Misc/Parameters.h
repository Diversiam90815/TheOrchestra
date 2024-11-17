/*
  ==============================================================================

	Module			Parameters
	Description		Storing (mostly compile time) constants

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
//                          FAMILIES
//==============================================================================

constexpr auto StringsName		 = "Strings";
constexpr auto BrassName		 = "Brass";
constexpr auto WoodwindsName	 = "Woodwinds";
constexpr auto PercussionName	 = "Percussion";


//==============================================================================
//                          INSTRUMENTS
//==============================================================================

constexpr auto ViolinName		 = "Violin";
constexpr auto ViolaName		 = "Viola";
constexpr auto VioloncelloName	 = "Violoncello";
constexpr auto DoubleBassName	 = "Double Bass";

constexpr auto FrenchHornName	 = "French Horn";
constexpr auto TrumpetName		 = "Trumpet";
constexpr auto TenorTromboneName = "Tenor Trombone";
constexpr auto BassTromboneName	 = "Bass Trombone";
constexpr auto CimbassoName		 = "Cimbasso";
constexpr auto TubaName			 = "Tuba";

constexpr auto PiccoloName		 = "Piccolo";
constexpr auto FluteName		 = "Flute";
constexpr auto OboeName			 = "Oboe";
constexpr auto CorAnglaisName	 = "Cor Anglais";
constexpr auto ClarinetName		 = "Clarinet";
constexpr auto BassClarinetName	 = "Bass Clarinet";
constexpr auto BassoonName		 = "Bassoon";
constexpr auto ContrabassoonName = "Contrabassoon";

constexpr auto HarpName			 = "Harp";
constexpr auto CelesteName		 = "Celeste";
constexpr auto TimpaniName		 = "Timpani";
constexpr auto MarimbaName		 = "Marimba";


//==============================================================================
//                          VALUES
//==============================================================================

constexpr int  defaultInstrument = 100;


//==============================================================================
//                          ENUMS
//==============================================================================

// Enum for the orchestra families: Woodwinds, Brass, Strings and Percussion
enum Family
{
	Woodwinds = 1,
	Brass,
	Strings,
	Percussion
};

// Enum for the Strings family
enum Strings
{
	Violin = 1,
	Viola,
	Violoncello,
	DoubleBass
};

// Enum for the Woodwind family
enum Woodwinds
{
	Piccolo = 1,
	Flute,
	Oboe,
	CorAnglais,
	Clarinet,
	BassClarinet,
	Bassoon,
	Contrabassoon
};

// Enum for the Percussion family
enum Percussion
{
	Harp = 1,
	Celeste,
	Timpani,
	Marimba
};

// Enum for the Brass family
enum Brass
{
	FrenchHorn = 1,
	Trumpet,
	TenorTrombone,
	BassTrombone,
	Cimbasso,
	Tuba
};