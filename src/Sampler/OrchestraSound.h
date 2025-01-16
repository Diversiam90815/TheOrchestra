/*
  ==============================================================================

	Module			OrchestraSound
	Description		Custom sound class holding multiple dynamic layers & round-robins per single MIDI note/range

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Parameters.h"
#include "SamplesManagement.h"


//// Enum for the different Dynamics
//enum class dynamics
//{
//	pianissimo = 1,
//	piano,
//	mezzoPiano,
//	mezzoForte,
//	forte,
//	fortissimo
//};


class OrchestraSound : public juce::SynthesiserSound
{
public:
	struct DynamicLayer
	{
		dynamics								   dynamicValue;
		juce::OwnedArray<juce::AudioBuffer<float>> roundRobinSamples;
	};

	/**
	@brief	Create an OrchestraSound for a specific note or note range.
	@param	[IN] noteRangeStart			-> Minimum MIDI note
	@param	[IN] noteRangeEnd			-> Maximum MIDI note
	*/
	OrchestraSound(int noteRangeStart, int noteRangeEnd);

	~OrchestraSound() override;

	void						   addDynamicLayer(dynamics dynamicValue, juce::OwnedArray<juce::AudioBuffer<float>> &&rrSamples);

	bool						   appliesToNote(int midiNoteNumber) override;

	bool						   appliesToChannel(int midiChannel) override;

	juce::OwnedArray<DynamicLayer> dynamicLayers;

private:
	static juce::BigInteger getNoteRangeBit(int start, int end);

	int						noteRangeStart;
	int						noteRangeEnd;
};
