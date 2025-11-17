/*
  ==============================================================================
	Module			CoreManager
	Description		Manager of the Core Project
  ==============================================================================
*/

#include "CoreManager.h"


CoreManager::CoreManager()
	: mInstrumentController(std::make_unique<InstrumentController>()), mSampler(std::make_unique<OrchestraSampler>()), mMidiKeyboardState(std::make_unique<juce::MidiKeyboardState>())
{
}


void CoreManager::init()
{
	// Use call_once to ensure logging is only initialized once globally
	static std::once_flag loggingInitFlag;
	std::call_once(loggingInitFlag,
				   [this]()
				   {
					   mLogger.initLogging();
					   logProjectInfo();
				   });

	mInstrumentController->init();
	mSampler->init(*mInstrumentController.get());

	LOG_INFO("Core Manager initialized!");
}


void CoreManager::prepareAudio(double sampleRate, int samplesPerblock)
{
	LOG_INFO("Preparing audio with Samplerate={}, samplesPerBlock={}", sampleRate, samplesPerblock);
	mSampler->prepare(sampleRate, samplesPerblock);
}


juce::MidiKeyboardState &CoreManager::getMidiKeyboardState()
{
	return *mMidiKeyboardState;
}


void CoreManager::changeInstrument(InstrumentID key)
{
	LOG_INFO("Changing instrument to {}", key);

	// Check if it is valid
	if (!mInstrumentController->getInstrument(key).isValid())
	{
		LOG_ERROR("Instrument with key {} not found!", key);
		return;
	}

	mSampler->reset();

	mCurrentInstrumentKey = key;

	// TODO: maybe preload default articulation

	LOG_INFO("Instrument changed successfully to key {}", key);
}


void CoreManager::changeArticulation(InstrumentID key, Articulation articulation)
{
	mSampler->addSoundsFromInstrumentToSampler(key, articulation);
	LOG_INFO("Instrument key {} changed to articulation {}", key, static_cast<int>(articulation));
}


void			  CoreManager::changeSamplesFolder(std::string &samplesFolder) {}


InstrumentProfile CoreManager::getInstrument(InstrumentID key)
{
	return mInstrumentController->getInstrument(key);
}


std::set<Articulation> CoreManager::getAvailableArticulations(InstrumentID instrumentKey)
{
	return mSampler->getAvailableArticulationsForInstrument(instrumentKey);
}


void CoreManager::processAudioBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	mMidiKeyboardState->processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

	mSampler->process(buffer, midiMessages);
}


void CoreManager::setSamplesFolder(std::string &directory)
{
	if (mSampler)
		mSampler->reloadSamples(directory);
}


void CoreManager::logProjectInfo()
{
	LOG_INFO("=======================================");
	LOG_INFO("============ SYSTEM INFO ==============");

	LOG_INFO("Project Name:\t\t {}", BuildInfo::Name);
	LOG_INFO("Project Version:\t\t {}", BuildInfo::Version);

	LOG_INFO("Build Time:\t\t {}", BuildInfo::Timestamp);
	LOG_INFO("Branch:\t\t\t {}", BuildInfo::Branch);
	LOG_INFO("Commit SHA:\t\t {}", BuildInfo::CommitSHA);
	LOG_INFO("Commit SHA Short:\t {}", BuildInfo::CommitSHAShort);

	LOG_INFO("Generator:\t\t {}", BuildInfo::Generator);
	LOG_INFO("CPP Version:\t\t {}", BuildInfo::CxxStandard);

	LOG_INFO("System Name:\t\t {}", BuildInfo::SystemName);
	LOG_INFO("System Version:\t\t {}", BuildInfo::SystemVersion);
	LOG_INFO("System CPU:\t\t {}", BuildInfo::SystemCPU);

	LOG_INFO("Compiler:\t\t {}", BuildInfo::CompilerID);
	LOG_INFO("Compiler Version:\t {}", BuildInfo::CompilerVersion);

	LOG_INFO("================= END =================");
	LOG_INFO("=======================================");
}
