/*
  ==============================================================================

    Parameters.h
    Created: 1 Apr 2024 4:57:13pm
    Author:  jerry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//Families

constexpr auto StringsName = "Strings";
constexpr auto BrassName = "Brass";
constexpr auto WoodwindsName = "Woodwinds";
constexpr auto PercussionName = "Percussion";


//Instruments

constexpr auto ViolinName = "Violin";
constexpr auto ViolaName = "Viola";
constexpr auto VioloncelloName = "Violoncello";
constexpr auto DoubleBassName = "Double Bass";

constexpr auto FrenchHornName = "French Horn";
constexpr auto TrumpetName = "Trumpet";
constexpr auto TenorTromboneName = "Tenor Trombone";
constexpr auto BassTromboneName = "Bass Trombone";
constexpr auto CimbassoName = "Cimbasso";
constexpr auto TubaName = "Tuba";

constexpr auto PiccoloName = "Piccolo";
constexpr auto FluteName = "Flute";
constexpr auto OboeName = "Oboe";
constexpr auto CorAnglaisName = "Cor Anglais";
constexpr auto ClarinetName = "Clarinet";
constexpr auto BassClarinetName = "Bass Clarinet";
constexpr auto BassoonName = "Bassoon";
constexpr auto ContrabassonName = "Contrabasson";

constexpr auto HarpName = "Harp";
constexpr auto CelesteName = "Celeste";
constexpr auto TimpaniName = "Timpani";
constexpr auto MarimbaName = "Marimba";


//Values 
constexpr int defaultInstrument = 100;

std::vector<Colour> mQualityColours =
{
    Colours::lightblue,   // For the first range
    Colours::lightgreen,  // For the second range
    Colours::lightcoral,  // For the third range
    Colours::gold         // Additional ranges, etc.
};