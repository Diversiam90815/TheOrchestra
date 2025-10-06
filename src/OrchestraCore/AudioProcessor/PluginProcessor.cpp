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
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
						 .withInput("Input", AudioChannelSet::stereo(), true)
#endif
						 .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	  )
#endif
{
	init();
}


void OrchestraProcessor::init()
{
	mInstrumentController.init();
	mOrchestraSampler.init(&mInstrumentController);
}


void OrchestraProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	LOG_INFO("Prepare to play called with Samplerate = {} and SamplesPerBlock = {}.", sampleRate, samplesPerBlock);
	mOrchestraSampler.mSampler.setCurrentPlaybackSampleRate(sampleRate);
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

	mKeyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	if (!mOrchestraSampler.getSamplesAreReady())
		return;

	mOrchestraSampler.mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


void OrchestraProcessor::setCurrentInstrument(int key, Articulation articulationUsed)
{
	mOrchestraSampler.addSoundsFromInstrumentToSampler(key, articulationUsed);
}


AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new OrchestraProcessor();
}
