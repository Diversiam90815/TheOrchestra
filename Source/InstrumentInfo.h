/*
  ==============================================================================

	InstrumentInfo.h
	Created: 1 Apr 2024 3:50:07pm
	Author:  jerry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Parameters.h"
#include "InstrumentData.h"


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


/*
 @brief             Class defining an instrument and it's information (info can be found in InstrumentData.h)
*/
class InstrumentInfo
{
public:
	InstrumentInfo();
	InstrumentInfo(const String		 &name,
				   const String		 &range,
				   const StringArray &qualities,
				   const StringArray &roles,
				   const StringArray &famousWorks,
				   const String		 &transposition,
				   const StringArray &playingTechniques);
	~InstrumentInfo();

    
private:
	String		mName;                          //Name of the instrument
	String		mRange;                         //Range of notes (lowest to highest playable note)
	StringArray mQualities;                     //Sound characteristics of each section within the range
	StringArray mUsefulInformation;             //Any useful information of the instrument
	StringArray mFamousWorks;                   //Famous works presenting the qualitiy of the instrument
	String		mTransposition;                 //Information about the transposition of the instrument, if it applies
	StringArray mPlayingTechniques;             //Different playing techniques featured within the instrument's family

	friend class InstrumentInfoModel;
	friend class InstrumentInfoView;
};
