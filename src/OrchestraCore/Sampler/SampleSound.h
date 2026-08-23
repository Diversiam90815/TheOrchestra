/*
  ==============================================================================
	Module			SampleSound
	Description		Custom sound class holding multiple dynamic layers & round-robins per single MIDI note/range
  ==============================================================================
*/

#pragma once

#include <atomic>

#include "JuceIncludes.h"
#include "Parameters.h"
#include "SampleCatalog.h"
#include "SamplerStructs.h"


class SampleSound : public juce::SynthesiserSound
{
public:
	SampleSound(int noteRangeStart, int noteRangeEnd, int rootNote);
	~SampleSound() = default;

	void						   addDynamicLayer(Dynamics dynamicValue, juce::OwnedArray<juce::AudioBuffer<float>> &&rrSamples);

	bool						   appliesToNote(int midiNoteNumber) override;
	bool						   appliesToChannel(int midiChannel) override; // TODO: Create settings to store value

	int							   getRootNote() const;

	void						   setArticulation(const Articulation art);
	Articulation				   getArticulation() const;

	juce::OwnedArray<DynamicLayer> dynamicLayers;

private:
	Articulation articulation = Articulation::sustain; // Default value -> will be set at creation

	int			 noteRangeStart;
	int			 noteRangeEnd;
	int			 rootNote;
};
