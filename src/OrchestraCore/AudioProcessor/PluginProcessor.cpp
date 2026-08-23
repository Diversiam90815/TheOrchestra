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
	: juce::AudioProcessor(juce::AudioProcessor::BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)), mCoreManager(std::make_unique<CoreManager>())
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


bool OrchestraProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
	// Output only: mono or stereo.
	if (layouts.getMainInputChannels() != 0)
		return false;

	const auto &out = layouts.getMainOutputChannelSet();

	return out == juce::AudioChannelSet::mono() || out == juce::AudioChannelSet::stereo();
}


void OrchestraProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	juce::ScopedNoDenormals noDenormals;

	// The voices add into the buffer, so it has to start silent. There is no input bus to preserve.
	buffer.clear();

	mCoreManager->processAudioBlock(buffer, midiMessages);
}


void OrchestraProcessor::getStateInformation(juce::MemoryBlock &destData)
{
	juce::ValueTree state(PluginState::Tag);

	state.setProperty(PluginState::VersionAttr, PluginState::StateVersion, nullptr);
	state.setProperty(PluginState::InstrumentAttr, mCoreManager->getCurrentInstrument(), nullptr);
	state.setProperty(PluginState::ArticulationAttr, static_cast<int>(mCoreManager->getCurrentArticulation()), nullptr);

	if (auto xml = state.createXml())
		copyXmlToBinary(*xml, destData);
}


void OrchestraProcessor::setStateInformation(const void *data, int sizeInBytes)
{
	auto xml = getXmlFromBinary(data, sizeInBytes);

	if (xml == nullptr)
		return;

	const auto state = juce::ValueTree::fromXml(*xml);

	if (!state.isValid() || !state.hasType(PluginState::Tag))
	{
		LOG_WARNING("Ignoring plugin state: unexpected root tag");
		return;
	}

	const int version = state.getProperty(PluginState::VersionAttr, 0);

	if (version > PluginState::StateVersion)
	{
		LOG_WARNING("Ignoring plugin state written by a newer version ({} > {})", version, PluginState::StateVersion);
		return;
	}

	const InstrumentID instrument = state.getProperty(PluginState::InstrumentAttr, 0);

	if (instrument <= 0)
		return;

	const auto articulation = static_cast<Articulation>(static_cast<int>(state.getProperty(PluginState::ArticulationAttr, static_cast<int>(Articulation::sustain))));

	LOG_INFO("Restoring plugin state: instrument {}, articulation {}", instrument, static_cast<int>(articulation));

	mCoreManager->changeInstrument(instrument);
	mCoreManager->changeArticulation(instrument, articulation);
}
