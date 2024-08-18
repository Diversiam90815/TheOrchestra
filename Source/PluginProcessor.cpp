

//==============================================================================
//				INCLUDES
//==============================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
//				AUDIO PROCESSOR
//==============================================================================


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
}

OrchestraProcessor::~OrchestraProcessor()
{
}


void OrchestraProcessor::init()
{
	mOrchestraSampler.init();
	//mOrchestraSampler.mSampler.getSound()
}



//==============================================================================
//				JUCE Overrides
//==============================================================================

const String OrchestraProcessor::getName() const
{
	return JucePlugin_Name;
}


bool OrchestraProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}


bool OrchestraProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}


bool OrchestraProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}


double OrchestraProcessor::getTailLengthSeconds() const
{
	return 0.0;
}


int OrchestraProcessor::getNumPrograms()
{
	return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
			  // so this should be at least 1, even if you're not really implementing programs.
}


int OrchestraProcessor::getCurrentProgram()
{
	return 0;
}


void OrchestraProcessor::setCurrentProgram(int index)
{
}


const String OrchestraProcessor::getProgramName(int index)
{
	return {};
}


void OrchestraProcessor::changeProgramName(int index, const String &newName)
{
}


void OrchestraProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	mOrchestraSampler.mSampler.setCurrentPlaybackSampleRate(sampleRate);
}


void OrchestraProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}


#ifndef JucePlugin_PreferredChannelConfigurations
bool OrchestraProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

		// This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif


void OrchestraProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto			  totalNumInputChannels	 = getTotalNumInputChannels();
	auto			  totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	if (!mOrchestraSampler.getSamplesAreReady())
		return;

	mOrchestraSampler.mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}



bool OrchestraProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}


AudioProcessorEditor *OrchestraProcessor::createEditor()
{
	return new OrchestraEditor(*this);
}


void OrchestraProcessor::getStateInformation(MemoryBlock &destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}


void OrchestraProcessor::setStateInformation(const void *data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}


AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new OrchestraProcessor();
}
