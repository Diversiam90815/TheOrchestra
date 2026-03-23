/*
  ==============================================================================
	Module			InstrumentSidebar
	Description		Visual instrument browser sidebar with selection highlighting
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"

#include <functional>


using InstrumentSelectedCallback = std::function<void(InstrumentID)>;


class InstrumentSidebar : public juce::Component, public juce::ListBoxModel
{
public:
	InstrumentSidebar();
	~InstrumentSidebar() override = default;

	void paint(juce::Graphics &g) override;
	void resized() override;

	void setFamily(Family family, const std::vector<std::pair<InstrumentID, std::string>> &instruments);
	void setInstrumentSelectedCallback(InstrumentSelectedCallback callback);
	void selectInstrument(InstrumentID id);

	// ListBoxModel
	int	 getNumRows() override;
	void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;
	void listBoxItemClicked(int row, const juce::MouseEvent &) override;

private:
	juce::ListBox									  mListBox;
	std::vector<std::pair<InstrumentID, std::string>> mInstruments;
	InstrumentID									  mSelectedID = 0;
	InstrumentSelectedCallback						  mCallback;
};
