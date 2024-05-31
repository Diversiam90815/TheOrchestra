/*
  ==============================================================================

	Sampler.cpp
	Created: 31 May 2024 12:43:50pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#include "Sampler.h"


Sampler::Sampler()
{
}


Sampler::~Sampler()
{
}


void Sampler::init()
{
	mSamplesManager = std::make_unique<SamplesManagement>();
	mSamplesManager->init();
}


std::vector<std::unique_ptr<Sample>> Sampler::getSamplesForNote(const int key, const String &note)
{
	auto								 allSamplesForInstrument = mSamplesManager->getSamplesForInstrument(key);
	std::vector<std::unique_ptr<Sample>> samples;

	for (auto &singleSample : allSamplesForInstrument)
	{
		if (singleSample.note != note)
			continue;

		auto sample = std::make_unique<Sample>(singleSample);
		samples.push_back(sample);
	}

	if (samples.size() > 0)
	{
		return samples;
	}
}
