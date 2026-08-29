/*
  ==============================================================================
	Module			SampleSound
	Description		Custom sound class holding multiple dynamic layers & round-robins per single MIDI note/range
  ==============================================================================
*/

#include "SampleSound.h"


SampleSound::SampleSound(int noteRangeStart, int noteRangeEnd, int rootNote) : noteRangeStart(noteRangeStart), noteRangeEnd(noteRangeEnd), rootNote(rootNote) {}


void SampleSound::addDynamicLayer(Dynamics dynamicValue, RoundRobinBuffers &&rrSamples)
{
	auto *layer				 = new DynamicLayer();
	layer->dynamicValue		 = dynamicValue;
	layer->roundRobinSamples = std::move(rrSamples);
	dynamicLayers.add(layer);
}


bool SampleSound::appliesToNote(int midiNoteNumber)
{
	return (midiNoteNumber >= noteRangeStart) && (midiNoteNumber <= noteRangeEnd);
}


bool SampleSound::appliesToChannel(int midiChannel)
{
	return true; // Skip for now
}


int SampleSound::getRootNote() const
{
	return rootNote;
}


void SampleSound::setArticulation(const Articulation art)
{
	if (articulation != art)
	{
		articulation = art;
	}
}


Articulation SampleSound::getArticulation() const
{
	return articulation;
}
