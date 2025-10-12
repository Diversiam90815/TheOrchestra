/*
  ==============================================================================
	Module			PluginProcessor
	Description		Audio Plugin Processor
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "CoreManager.h"

class OrchestraEditor;


class OrchestraProcessor : public AudioProcessor
{
public:
	OrchestraProcessor();
	~OrchestraProcessor() = default;

	std::shared_ptr<CoreManager> getCoreManager();

private:
	void						 prepareToPlay(double sampleRate, int samplesPerBlock) override;

	bool						 isBusesLayoutSupported(const BusesLayout &layouts) const override;

	void						 processBlock(AudioBuffer<float> &, MidiBuffer &) override;

	void						 releaseResources() override {}
	AudioProcessorEditor		*createEditor() override;
	bool						 hasEditor() const override { return true; }
	const String				 getName() const override { return "The Orchestra"; }
	bool						 acceptsMidi() const override { return true; }
	bool						 producesMidi() const override { return false; }
	bool						 isMidiEffect() const override { return false; }
	double						 getTailLengthSeconds() const override { return 0.0; }
	int							 getNumPrograms() override { return 1; }
	int							 getCurrentProgram() override { return 0; }
	void						 setCurrentProgram(int index) override {}
	const String				 getProgramName(int index) override { return {}; }
	void						 changeProgramName(int index, const String &newName) override {}
	void						 getStateInformation(MemoryBlock &destData) override {}
	void						 setStateInformation(const void *data, int sizeInBytes) override {}


	std::shared_ptr<CoreManager> mCoreManager;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OrchestraProcessor)
};
