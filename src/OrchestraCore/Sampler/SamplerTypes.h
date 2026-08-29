/*
  ==============================================================================
	Module			SamplerTypes
	Description		Shared type aliases used across the Sampler modules
  ==============================================================================
*/

#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "JuceIncludes.h"


// A single decoded audio sample (owned)
using AudioBufferPtr	 = std::unique_ptr<juce::AudioBuffer<float>>;

// A round-robin group of decoded audio samples belonging to one dynamic layer
using RoundRobinBuffers	 = std::vector<AudioBufferPtr>;

using DynamicToFileMap	 = std::map<int, std::vector<fs::path>>;
using NoteDynamicMap	 = std::map<int, DynamicToFileMap>;

using AudioBufferView	 = const juce::AudioBuffer<float> *;



using SampleLoadCallback = std::function<void(bool)>;