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

struct DynamicLayer
{
	Dynamics								   dynamicValue;
	juce::OwnedArray<juce::AudioBuffer<float>> roundRobinSamples;
};


class OrchestraSound : public juce::SynthesiserSound
{
public:
	OrchestraSound(int noteRangeStart, int noteRangeEnd, int rootNote);

	~OrchestraSound() override;

	void						   addDynamicLayer(Dynamics dynamicValue, juce::OwnedArray<juce::AudioBuffer<float>> &&rrSamples);

	bool						   appliesToNote(int midiNoteNumber) override;

	bool						   appliesToChannel(int midiChannel) override;

	int							   getRootNote() const;

	void						   setArticulation(const Articulation art);
	Articulation				   getArticulation() const;

	juce::OwnedArray<DynamicLayer> dynamicLayers;

private:
	static juce::BigInteger getNoteRangeBit(int start, int end);

	Articulation			articulation = Articulation::sustain; // Default value -> will be set at creation



	int						noteRangeStart;

	int						noteRangeEnd;

	int						rootNote;
};
