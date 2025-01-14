/*
  ==============================================================================

	Module			OrchestraSound
	Description		Custom sound class holding multiple dynamic layers & round-robins per single MIDI note/range

  ==============================================================================
*/

#include "OrchestraSound.h"


OrchestraSound::OrchestraSound(int noteRangeStart, int noteRangeEnd) : noteRangeStart(noteRangeStart), noteRangeEnd(noteRangeEnd)
{
}


OrchestraSound::~OrchestraSound()
{
}



void OrchestraSound::addDynamicLayer(dynamics dynamicValue, juce::OwnedArray<juce::AudioBuffer<float>> &&rrSamples)
{
	auto *layer				 = new DynamicLayer();
	layer->dynamicValue		 = dynamicValue;
	layer->roundRobinSamples = std::move(rrSamples);
	dynamicLayers.add(layer);
}


bool OrchestraSound::appliesToNote(int midiNoteNumber)
{
	return (midiNoteNumber >= noteRangeStart) && (midiNoteNumber <= noteRangeEnd);
}


bool OrchestraSound::appliesToChannel(int midiChannel)
{
	return true; // Skip for now
}


juce::BigInteger OrchestraSound::getNoteRangeBit(int start, int end)
{
	juce::BigInteger notes;
	notes.setRange(start, end - start + 1, true);
	return notes;
}
