/*
  ==============================================================================
	Module			SamplerStructs
	Description		Helper structs used for the Sampler modules
  ==============================================================================
*/

#pragma once

#include <filesystem>

#include "Parameters.h"
#include "JuceIncludes.h"


struct Sample
{
	Sample(
		const std::string &instrument, const std::string &note, const int &roundRobin, const Dynamics &dynamic, const Articulation &articulation, const std::filesystem::path &file)
		: instrument(instrument), note(note), roundRobin(roundRobin), dynamic(dynamic), articulation(articulation), file(file)
	{
		noteMidiValue = turnNotenameIntoMidinumber(note);
	}

	std::string			  instrument;
	std::string			  note;
	int					  noteMidiValue = 0;
	int					  roundRobin;
	Dynamics			  dynamic;
	Articulation		  articulation;
	std::filesystem::path file;
};


struct PercussionSample : public Sample
{
	PercussionSample(const std::string			 &instrument,
					 const std::string			 &note,
					 const int					 &roundRobin,
					 const Dynamics				 &dynamic,
					 const Articulation			 &articulation,
					 const std::filesystem::path &file,
					 int						  specificMidiNote)
		: Sample(instrument, note, roundRobin, dynamic, articulation, file)
	{
		noteMidiValue = specificMidiNote; // Override the noteMidiValue with the specific value for a percussion sound
	}

	std::string percussionElementName;	  // Name of the percussion element
};


struct DynamicLayer
{
	Dynamics											   dynamicValue;
	std::vector<std::unique_ptr<juce::AudioBuffer<float>>> roundRobinSamples;
	std::atomic<unsigned>								   roundRobinCounter{0};
};


// Last-seen value of the continuous controllers the sampler responds to.
struct ControllerState
{
	std::atomic<float> cc1{0.0f};	 // modulation
	std::atomic<float> cc11{127.0f}; // expression
};


struct StereoSample
{
	float left	= 0.0f;
	float right = 0.0f;
};
