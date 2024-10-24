/*
  ==============================================================================

	Module			SamplesManagerment
	Description		Managing the samples

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


// Enum for the different Dynamics
enum dynamics
{
	pianissimo = 1,
	piano,
	mezzoPiano,
	mezzoForte,
	forte,
	fortissimo
};

//
//// Mapping each Dynamic from enum to the short abbrevations used in notation
// std::map<String, dynamics> dynamicMap = {{"pp", dynamics::pianissimo}, {"p", dynamics::piano}, {"mp", dynamics::mezzoPiano},
//										 {"mf", dynamics::mezzoForte}, {"f", dynamics::forte}, {"ff", dynamics::fortissimo}};


/*
 @brief             Struct holding information of the AudioSamples, such as Instrument Name, the individual note, the round robin instance,                   the dynmic of the
 recording and the actual buffer holding the audio samples
*/
struct Sample
{
	Sample(const String &instrument, const String &note, const int &roundRobin, const int &dynamic, const File &file)
		: instrument(instrument), note(note), roundRobin(roundRobin), dynamic(dynamic), file(file)
	{
	}

	String instrument;
	String note;
	int	   roundRobin;
	int	   dynamic;
	File   file;
};


/*
 @brief             Managing the Samples and the according files
*/
class SamplesManagement
{
public:
	//==============================================================================
	//                          CONSTRUCTOR - DESTRUCTOR
	//==============================================================================

	SamplesManagement();
	~SamplesManagement() = default;

	//==============================================================================
	//                          PUBLIC METHODS
	//==============================================================================

	/*
	 @brief             Initializes the AudioFormatManager and sets the SamplesFolder of this project
	*/
	void				init();

	/*
	 @brief             Returns a vector of Sample structs for a given instrument identified by the instrument key
	 @param             [IN] reference to an instrumentKey (see InstrumentInfoModel::getInstrumentKey)
	 @return            Vector collecting all Sample objects of an instrument (containing all notes and round robins)
	*/
	std::vector<Sample> getSamplesForInstrument(const int &instrumentKey) const;


private:
	//==============================================================================
	//                          PRIVATE METHODS
	//==============================================================================

	/*
	 @brief             Iterates through each section and their instruments and add the samples calls the 'addSample' method
	*/
	void							   parseSampleFiles();

	/*
	 @brief             Creates a Sample object of the current instrument and samples and adds it to the map mInstrumentSamples
	 @param             [IN] file -> reference to the file of the Samples
	 @param             [IN] key -> reference to the key of the instrument used (see InstrumentInfoModel::getInstrumentKey)
	*/
	void							   addSample(const File &file, const int &key);

	/*
	 @brief             Gets the path of the samples within the samples folder for a given instrument
	 @param             [IN] key -> reference to the key of the instrument used (see InstrumentInfoModel::getInstrumentKey)
	 @return            juce::File of the instrument samples path, empty file if the instrument is not found
	*/
	File							   getInstrumentSamplesPath(const int &instrumentKey);

	/*
	 @brief             Returns the value of the dynamic within the enum 'dynamics'
	 @param             [IN] Dynamic as used in notation (pp, p, mp, mf, f, ff)
	 @return            int value of the dynamic from the enum 'dynamics'
	*/
	int								   getIndexOfDynamics(const String &dynamicsString);


	//==============================================================================
	//                          PRIVATE OBJECTS
	//==============================================================================

	File							   mSamplesFolder;	   // Folder of the samples folder ( /Assets/Samples)

	std::map<int, std::vector<Sample>> mInstrumentSamples; // Map of the instrument (identified by their key) and their assigned 'Sample'


	std::map<String, dynamics>		   dynamicMap = {
													{"pp", dynamics::pianissimo}, 
													{"p", dynamics::piano}, 
													{"mp", dynamics::mezzoPiano},
													{"mf", dynamics::mezzoForte}, 
													{"f", dynamics::forte}, 
													{"ff", dynamics::fortissimo}
													}; // Mapping each Dynamic from enum to the short abbrevations used in notation
};
