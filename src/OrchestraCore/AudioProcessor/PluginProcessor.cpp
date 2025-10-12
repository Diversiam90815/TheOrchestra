/*
  ==============================================================================
	Module			PluginProcessor
	Description		Audio Plugin Processor
  ==============================================================================
*/


#include "PluginProcessor.h"
#include "Logging.h"
#include "buildinfo.h"


OrchestraProcessor::OrchestraProcessor()
	: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true)),
	  mCoreManager(std::make_unique<CoreManager>())
{
	mCoreManager->init();
}


CoreManager &OrchestraProcessor::getCoreManager()
{
	return *mCoreManager;
}


void OrchestraProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	LOG_INFO("Prepare to play called with Samplerate = {} and SamplesPerBlock = {}.", sampleRate, samplesPerBlock);
	mCoreManager->prepareAudio(sampleRate, samplesPerBlock);
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool OrchestraProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	return true;
}
#endif


void OrchestraProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto			  totalNumInputChannels	 = getTotalNumInputChannels();
	auto			  totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	mCoreManager->processAudioBlock(buffer, midiMessages);
}


AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new OrchestraProcessor();
}
