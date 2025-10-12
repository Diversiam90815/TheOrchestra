/*
  ==============================================================================
	Module			Parameters
	Description		Storing constants
  ==============================================================================
*/

#pragma once


//==============================================================================
//                          FAMILIES
//==============================================================================

enum class Family
{
	Woodwinds  = 1,
	Brass	   = 2,
	Strings	   = 3,
	Percussion = 4
};

constexpr auto StringsName	  = "Strings";
constexpr auto BrassName	  = "Brass";
constexpr auto WoodwindsName  = "Woodwinds";
constexpr auto PercussionName = "Percussion";


//==============================================================================
//                          INSTRUMENTS
//==============================================================================

enum class Strings
{
	Violin		= 1,
	Viola		= 2,
	Violoncello = 3,
	DoubleBass	= 4
};

constexpr auto ViolinName	   = "Violin";
constexpr auto ViolaName	   = "Viola";
constexpr auto VioloncelloName = "Violoncello";
constexpr auto DoubleBassName  = "Double Bass";

enum class Brass
{
	FrenchHorn	  = 1,
	Trumpet		  = 2,
	TenorTrombone = 3,
	BassTrombone  = 4,
	Cimbasso	  = 5,
	Tuba		  = 6
};

constexpr auto FrenchHornName	 = "French Horn";
constexpr auto TrumpetName		 = "Trumpet";
constexpr auto TenorTromboneName = "Tenor Trombone";
constexpr auto BassTromboneName	 = "Bass Trombone";
constexpr auto CimbassoName		 = "Cimbasso";
constexpr auto TubaName			 = "Tuba";

enum class Woodwinds
{
	Piccolo		  = 1,
	Flute		  = 2,
	Oboe		  = 3,
	CorAnglais	  = 4,
	Clarinet	  = 5,
	BassClarinet  = 6,
	Bassoon		  = 7,
	Contrabassoon = 8
};

constexpr auto PiccoloName		 = "Piccolo";
constexpr auto FluteName		 = "Flute";
constexpr auto OboeName			 = "Oboe";
constexpr auto CorAnglaisName	 = "Cor Anglais";
constexpr auto ClarinetName		 = "Clarinet";
constexpr auto BassClarinetName	 = "Bass Clarinet";
constexpr auto BassoonName		 = "Bassoon";
constexpr auto ContrabassoonName = "Contrabassoon";

enum class Percussion
{
	Harp	= 1,
	Celeste = 2,
	Timpani = 3,
	Marimba = 4
};

constexpr auto HarpName	   = "Harp";
constexpr auto CelesteName = "Celeste";
constexpr auto TimpaniName = "Timpani";
constexpr auto MarimbaName = "Marimba";


//==============================================================================
//                          ARTICULATIONS
//==============================================================================

enum class Articulation
{
	sustain	  = 1,
	staccato  = 2,
	spiccato  = 3,
	pizzicato = 4,
	mute	  = 5,
	vibrato	  = 6,
	tremolo	  = 7,
	hits	  = 8,
	rolls	  = 9
};

constexpr auto SustainArticulation	 = "Sustain";
constexpr auto StaccatoArticulation	 = "Staccato";
constexpr auto SpiccatoArticulation	 = "Spiccato";
constexpr auto PizzicatoArticulation = "Pizzicato";
constexpr auto MutedArticulation	 = "Mute";
constexpr auto VibratoArticulation	 = "Vibrato";
constexpr auto TremoloArticulation	 = "Tremolo";
constexpr auto HitsArticulation		 = "Hits";
constexpr auto RollsArticulation	 = "Rolls";


//==============================================================================
//                          DYNAMICS
//==============================================================================

enum class Dynamics
{
	pianissimo = 1,
	piano	   = 2,
	mezzoPiano = 3,
	mezzoForte = 4,
	forte	   = 5,
	fortissimo = 6
};

constexpr auto PianissimoDynamic = "pp";
constexpr auto PianoDynamic		 = "p";
constexpr auto MezzoPianoDynamic = "mp";
constexpr auto MezzoForteDynamic = "mf";
constexpr auto ForteDynamic		 = "f";
constexpr auto FortissimoDynamic = "ff";


//==============================================================================
//                          FOLDERS / FILES
//==============================================================================

constexpr auto LogFileName		 = "Orchestra.log";
constexpr auto ProjectName		 = "TheOrchestra";
constexpr auto LogFolderName	 = "Logs";
constexpr auto LogFile			 = "Orchestra.log";


//==============================================================================
//                          TYPES
//==============================================================================

// The key is 3 digit int where the first digit represents the family and the other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle
// digit remains 0.
using InstrumentID				 = int;
