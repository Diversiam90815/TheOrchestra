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


class Sampler
{
public:
	Sampler();
	~Sampler();

	void init();

private:
	std::vector<std::unique_ptr<Sample>> getSamplesForNote(const int key, const String &note);

	std::unique_ptr<SamplesManagement> mSamplesManager;
};