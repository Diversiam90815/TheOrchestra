
#include "JuceIncludes.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioProcessorEditor *OrchestraProcessor::createEditor()
{
	return new OrchestraEditor(*this);
}
