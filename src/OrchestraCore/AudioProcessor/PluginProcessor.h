/*
  ==============================================================================
	Module			PluginProcessor
	Description		Audio Plugin Processor
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Sampler.h"
#include "InstrumentController.h"

class OrchestraEditor;


class OrchestraProcessor : public AudioProcessor
{
public:
	OrchestraProcessor();
	~OrchestraProcessor() = default;

	void			   init();

	MidiKeyboardState *getMidiKeyboardState() { return &mKeyboardState; }

private:
	void				  prepareToPlay(double sampleRate, int samplesPerBlock) override;

	bool				  isBusesLayoutSupported(const BusesLayout &layouts) const override;

	void				  processBlock(AudioBuffer<float> &, MidiBuffer &) override;

	void				  releaseResources() override {}
	AudioProcessorEditor *createEditor() override;
	bool				  hasEditor() const override { return true; }
	const String		  getName() const override { return BuildInfo::Name; }
	bool				  acceptsMidi() const override { return true; }
	bool				  producesMidi() const override { return false; }
	bool				  isMidiEffect() const override { return false; }
	double				  getTailLengthSeconds() const override { return 0.0; }
	int					  getNumPrograms() override { return 1; }
	int					  getCurrentProgram() override { return 0; }
	void				  setCurrentProgram(int index) override {}
	const String		  getProgramName(int index) override { return {}; }
	void				  changeProgramName(int index, const String &newName) override {}
	void				  getStateInformation(MemoryBlock &destData) override {}
	void				  setStateInformation(const void *data, int sizeInBytes) override {}
	void				  setCurrentInstrument(int key, Articulation articulationUsed) {}


	InstrumentController  mInstrumentController;

	Sampler				  mOrchestraSampler;

	MidiKeyboardState	  mKeyboardState;


	friend class OrchestraEditor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OrchestraProcessor)
};
