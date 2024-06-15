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

	std::unique_ptr<juce::SamplerSound>	 createSoundFromSample(const std::unique_ptr<Sample> &sample);

	std::vector<std::unique_ptr<Sample>> filterSamplesFromNote(const int key, const String &note = "");

	std::unique_ptr<SamplesManagement>	 mSamplesManager;
};
