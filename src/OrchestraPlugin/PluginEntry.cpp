/*
  ==============================================================================
	Module			PluginEntry
	Description		Plugin entry point for the VST3 build
  ==============================================================================
*/

#include "PluginProcessor.h"


juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new OrchestraProcessor();
}
