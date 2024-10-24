/*
  ==============================================================================

	Module			InstrumentInfoModel
	Description		Managing instrument data for the whole orchestra

  ==============================================================================
*/


#pragma once
#include <JuceHeader.h>
#include <map>
#include "InstrumentInfo.h"


class InstrumentInfoModel
{
public:
    //==============================================================================
    //                          CONSTRUCTOR - DESTRUCTOR
    //==============================================================================
	InstrumentInfoModel();
	~InstrumentInfoModel();
    

    //==============================================================================
    //                          PUBLIC METHODS
    //==============================================================================
    
    /*
     @brief                 Returns the InstrumentInfo object of an instrument identified by a key
     @param                 [IN] key -> key of the instrument (see 'getInstrumentKey()')
     @return                InstrumentInfo object holding various information of the instrument
    */
	InstrumentInfo getInstrument(int key);

    /*
     @brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and the other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
     @param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
     @param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentInfo.h'
     @return                int value of the 3 digit key
    */
    static int	   getInstrumentKey(int family, int instrument);
    
    /*
     @brief                 Returns the key identifying an instrument given by the family and instrument. The key is 3 digit int where the first digit represents the family and the other 2 digits represent the instrument. Usually, if the instrument digit remains below 10, the middle digit remains 0.
     @param                 [IN] String of the family
     @param                 [IN] String of the instrument
     @return                int value of the 3 digit key
    */
	static int	   getInstrumentKey(String &family, String &instrument);


private:

	//==============================================================================
	//                          PRIVATE METHODS
	//==============================================================================
    
    /*
     @brief                 Adding the String Family instruments to the instruments map
    */
	void		   addStringInstruments();
    
    /*
     @brief                 Adding the Woodwind Family instruments to the instruments map
    */
	void		   addWoodwindInstruments();

    /*
     @brief                 Adding the Brass Family instruments to the instruments map
    */
	void		   addBrassInstruments();

    /*
     @brief                 Adding the Percussion Family instruments to the instruments map
    */
	void		   addPercussionInstruments();
    
    /*
     @brief                 Adding an instrument to the instruments map
     @param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
     @param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentInfo.h'
     @param                 [IN] InstrumentInfo object holding various information of the instrument
    */
	void		   addInstrument(Family family, int instrumentId, const InstrumentInfo &info);
    

    //==============================================================================
    //                          PRIVATE OBJECTS
    //==============================================================================
    
	std::map<int, InstrumentInfo>	instruments;            //Mapping the instrument's key to the corresponding InstrumentInfo object

	static std::map<String, Family> familyMap;              //Mapping the instrument families enum to their juce::String names
    
	static std::map<String, int>	instrumentMap;          //Mapping the instruments enums to their juce::String names
};
