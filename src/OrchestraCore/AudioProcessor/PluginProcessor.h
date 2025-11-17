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


class OrchestraProcessor : public juce::AudioProcessor
{
public:
	OrchestraProcessor();
	~OrchestraProcessor() = default;

	CoreManager &getCoreManager();

private:
	void						 prepareToPlay(double sampleRate, int samplesPerBlock) override;

	bool						 isBusesLayoutSupported(const BusesLayout &layouts) const override;

	void						 processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

	void						 releaseResources() override {}
	juce::AudioProcessorEditor	*createEditor() override;
	bool						 hasEditor() const override { return true; }
	const juce::String			 getName() const override { return "The Orchestra"; }
	bool						 acceptsMidi() const override { return true; }
	bool						 producesMidi() const override { return false; }
	bool						 isMidiEffect() const override { return false; }
	double						 getTailLengthSeconds() const override { return 0.0; }
	int							 getNumPrograms() override { return 1; }
	int							 getCurrentProgram() override { return 0; }
	void						 setCurrentProgram(int index) override {}
	const juce::String			 getProgramName(int index) override { return {}; }
	void						 changeProgramName(int index, const juce::String &newName) override {}
	void						 getStateInformation(juce::MemoryBlock &destData) override {}
	void						 setStateInformation(const void *data, int sizeInBytes) override {}


	std::unique_ptr<CoreManager> mCoreManager;
};
