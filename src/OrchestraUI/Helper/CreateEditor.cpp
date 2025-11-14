
#include "JuceIncludes.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"

juce::AudioProcessorEditor *OrchestraProcessor::createEditor()
{
	return new OrchestraEditor(*this);
}
