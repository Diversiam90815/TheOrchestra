/*
  ==============================================================================

	Sampler.h
	Created: 31 May 2024 12:43:50pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SamplesManagement.h"
#include "CustomPianoRoll.h"


class Sampler
{
public:
	Sampler();
	~Sampler();

	void									   init();

	std::vector<std::unique_ptr<SamplerSound>> getSoundsFromInstrument(const int key);

private:
	Synthesiser							 mSampler;

	juce::SamplerSound	 createSoundFromSample(const Sample &sample);

	std::vector<Sample> filterSamplesFromNote(const int key, const String &note = "");

	std::unique_ptr<SamplesManagement>	 mSamplesManager;
};
