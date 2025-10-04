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
	~OrchestraProcessor() override;

	void			   init();

	MidiKeyboardState *getMidiKeyboardState() { return &mKeyboardState; }

private:
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;

	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

	void				  processBlock(AudioBuffer<float> &, MidiBuffer &) override;

	AudioProcessorEditor *createEditor() override;

	bool				  hasEditor() const override;

	const String		  getName() const override;

	bool				  acceptsMidi() const override;

	bool				  producesMidi() const override;

	bool				  isMidiEffect() const override;

	double				  getTailLengthSeconds() const override;

	int					  getNumPrograms() override;

	int					  getCurrentProgram() override;

	void				  setCurrentProgram(int index) override;

	const String		  getProgramName(int index) override;

	void				  changeProgramName(int index, const String &newName) override;

	void				  getStateInformation(MemoryBlock &destData) override;

	void				  setStateInformation(const void *data, int sizeInBytes) override;

	void				  setCurrentInstrument(int key, Articulation articulationUsed);


	InstrumentController  mInstrumentController;

	Sampler				  mOrchestraSampler;

	MidiKeyboardState	  mKeyboardState;


	friend class OrchestraEditor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OrchestraProcessor)
};
