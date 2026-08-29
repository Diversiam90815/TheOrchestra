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

// Dynamic value -> file paths for that dynamic layer
using DynamicToFileMap	 = std::map<int, std::vector<fs::path>>;

// MIDI note -> (dynamic value -> file paths)
using NoteDynamicMap	 = std::map<int, DynamicToFileMap>;

// midi note -> (rangeLow, rangeHigh)
using NoteRangeMap		 = std::map<int, std::pair<int, int>>;

using AudioBufferView	 = const juce::AudioBuffer<float> *;

using SampleLoadCallback = std::function<void(bool)>;
using CatalogLoadCallback = std::function<void(bool)>;

// Result of a catalog scan/build: which instrument owns which parsed samples
using InstrumentSampleMap = std::map<InstrumentID, std::vector<struct Sample>>;

using ArticulationSet	 = std::set<Articulation>;
