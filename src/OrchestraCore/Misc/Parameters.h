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

namespace FamilyNames
{
constexpr auto Strings	  = "Strings";
constexpr auto Brass	  = "Brass";
constexpr auto Woodwinds  = "Woodwinds";
constexpr auto Percussion = "Percussion";
} // namespace FamilyNames


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

enum class Brass
{
	FrenchHorn	  = 1,
	Trumpet		  = 2,
	TenorTrombone = 3,
	BassTrombone  = 4,
	Cimbasso	  = 5,
	Tuba		  = 6
};

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

enum class Percussion
{
	Harp	= 1,
	Celeste = 2,
	Timpani = 3,
	Marimba = 4
};

namespace InstrumentNames
{

namespace Strings
{
constexpr auto Violin	   = "Violin";
constexpr auto Viola	   = "Viola";
constexpr auto Violoncello = "Violoncello";
constexpr auto DoubleBass  = "Double Bass";
} // namespace Strings

namespace Brass
{
constexpr auto FrenchHorn	 = "French Horn";
constexpr auto Trumpet		 = "Trumpet";
constexpr auto TenorTrombone = "Tenor Trombone";
constexpr auto BassTrombone	 = "Bass Trombone";
constexpr auto Cimbasso		 = "Cimbasso";
constexpr auto Tuba			 = "Tuba";
} // namespace Brass

namespace Woodwinds
{
constexpr auto Piccolo		 = "Piccolo";
constexpr auto Flute		 = "Flute";
constexpr auto Oboe			 = "Oboe";
constexpr auto CorAnglais	 = "Cor Anglais";
constexpr auto Clarinet		 = "Clarinet";
constexpr auto BassClarinet	 = "Bass Clarinet";
constexpr auto Bassoon		 = "Bassoon";
constexpr auto Contrabassoon = "Contrabassoon";
} // namespace Woodwinds

namespace Percussion
{
constexpr auto Harp	   = "Harp";
constexpr auto Celeste = "Celeste";
constexpr auto Timpani = "Timpani";
constexpr auto Marimba = "Marimba";
} // namespace Percussion

} // namespace InstrumentNames



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

namespace ArticulationNames
{
constexpr auto Sustain	 = "Sustain";
constexpr auto Staccato	 = "Staccato";
constexpr auto Spiccato	 = "Spiccato";
constexpr auto Pizzicato = "Pizzicato";
constexpr auto Muted	 = "Mute";
constexpr auto Vibrato	 = "Vibrato";
constexpr auto Tremolo	 = "Tremolo";
constexpr auto Hits		 = "Hits";
constexpr auto Rolls	 = "Rolls";
} // namespace ArticulationNames


//==============================================================================
//                          DYNAMICS
//==============================================================================

enum class Dynamics
{
	pianissimo	  = 1,
	piano		  = 2,
	mezzoPiano	  = 3,
	mezzoForte	  = 4,
	forte		  = 5,
	fortissimo	  = 6,
	fortississimo = 7
};

namespace DynamicNames
{
constexpr auto Pianissimo	 = "pp";
constexpr auto Piano		 = "p";
constexpr auto MezzoPiano	 = "mp";
constexpr auto MezzoForte	 = "mf";
constexpr auto Forte		 = "f";
constexpr auto Fortissimo	 = "ff";
constexpr auto Fortississimo = "fff";
} // namespace DynamicNames


//==============================================================================
//                          MIDI
//==============================================================================

constexpr int kModWheelCc	= 1;  // drives the dynamic-layer crossfade
constexpr int kExpressionCc = 11; // drives output level

constexpr int kMinCcValue	= 0;
constexpr int kMaxCcValue	= 127;


//==============================================================================
//                          FOLDERS / FILES
//==============================================================================

namespace Files
{
constexpr auto ProjectName		= "TheOrchestra";
constexpr auto TestProjectName	= "TheOrchestra-Tests";
constexpr auto LogFolderName	= "Logs";
constexpr auto LogFile			= "Orchestra.log";
constexpr auto ConfigFolderName = "Config";
constexpr auto ConfigFile		= "config.json";
} // namespace Files


//==============================================================================
//                          TYPES
//==============================================================================

// The key is 3 digit int where the first digit represents the family and the other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle
// digit remains 0.
using InstrumentID = int;


namespace OrchestraVoiceConstant
{
static constexpr int   MaxDynamicLayers = 8;

static constexpr float AttackSeconds	= 0.002f;
static constexpr float ShortRelease		= 0.010f;
static constexpr float SustainRelease	= 0.120f;
} // namespace OrchestraVoiceConstant
