
//==============================================================================
//				INCLUDES
//==============================================================================

#pragma once

#include <JuceHeader.h>


/*
Free Orchestra samples:
https://www.delamar.de/loops-samples/free-orchestra-samples-kostenlos-download-orchester-9341/

*/


//==============================================================================
//				AUDIO PROCESSOR
//==============================================================================

class OrchestraProcessor : public AudioProcessor
{
public:
	//==============================================================================
	//				CONSTRUCTOR DESTRUCTOR
	//==============================================================================
	OrchestraProcessor();

	~OrchestraProcessor() override;


	//==============================================================================
	//				PUBLIC METHODS
	//==============================================================================

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


private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OrchestraProcessor)
};
