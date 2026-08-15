/*
  ==============================================================================
	Module			MidiCcGutter
	Description		Vertical MIDI-CC sliders shown beside the piano roll.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "CcConfig.h"

#include <functional>
#include <memory>
#include <vector>


class MidiCcGutter : public juce::Component, private juce::Timer
{
public:
	explicit MidiCcGutter(std::vector<CcLane> lanes = getDefaultCcLanes());
	~MidiCcGutter() override;

	// Gutter -> engine: a lane's value changed (user dragged the slider).
	std::function<void(int ccNumber, int value)> onCcChanged;

	// Engine -> gutter: return the latest value for a CC (0..127), or -1 if unknown.
	std::function<int(int ccNumber)>			 ccValueProvider;

	int	 getPreferredWidth() const;

	void resized() override;

private:
	void timerCallback() override;

	class CcSlider;

	std::vector<CcLane>						mLanes;
	std::vector<std::unique_ptr<CcSlider>>	mSliders;

	static constexpr int kColumnWidth = 42;
	static constexpr int kColumnGap	  = Space::m;
};
