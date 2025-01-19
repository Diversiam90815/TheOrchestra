/*
  ==============================================================================

	Module			Parameters
	Description		Storing (mostly compile time) constants

  ==============================================================================
*/

#pragma once


//==============================================================================
//                          FAMILIES
//==============================================================================

enum class Family
{
	Woodwinds = 1,
	Brass,
	Strings,
	Percussion
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
	Violin = 1,
	Viola,
	Violoncello,
	DoubleBass
};

constexpr auto ViolinName	   = "Violin";
constexpr auto ViolaName	   = "Viola";
constexpr auto VioloncelloName = "Violoncello";
constexpr auto DoubleBassName  = "Double Bass";

enum class Brass
{
	FrenchHorn = 1,
	Trumpet,
	TenorTrombone,
	BassTrombone,
	Cimbasso,
	Tuba
};

constexpr auto FrenchHornName	 = "French Horn";
constexpr auto TrumpetName		 = "Trumpet";
constexpr auto TenorTromboneName = "Tenor Trombone";
constexpr auto BassTromboneName	 = "Bass Trombone";
constexpr auto CimbassoName		 = "Cimbasso";
constexpr auto TubaName			 = "Tuba";

enum class Woodwinds
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
	Harp = 1,
	Celeste,
	Timpani,
	Marimba
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
	sustain,
	staccato,
	spiccato,
	pizzicato,
	mute,
	vibrato,
	tremolo,
	hits,
	rolls
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
	piano,
	mezzoPiano,
	mezzoForte,
	forte,
	fortissimo
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
