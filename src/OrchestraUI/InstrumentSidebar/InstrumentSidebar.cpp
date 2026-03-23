/*
  ==============================================================================
	Module			InstrumentSidebar
	Description		Visual instrument browser sidebar with selection highlighting
  ==============================================================================
*/

#include "InstrumentSidebar.h"
#include "CustomLookAndFeel.h"


InstrumentSidebar::InstrumentSidebar()
{
	mListBox.setModel(this);
	mListBox.setRowHeight(52);
	mListBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
	mListBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
	addAndMakeVisible(mListBox);
}


void InstrumentSidebar::paint(juce::Graphics &g)
{
	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (lnf)
		g.fillAll(lnf->getBackgroundColour());
	else
		g.fillAll(juce::Colour(18, 16, 26));

	// Right border
	g.setColour(juce::Colours::white.withAlpha(0.04f));
	g.fillRect(getWidth() - 1, 0, 1, getHeight());
}


void InstrumentSidebar::resized()
{
	mListBox.setBounds(getLocalBounds().withTrimmedTop(8).withTrimmedBottom(8));
}


void InstrumentSidebar::setFamily(Family family, const std::vector<std::pair<InstrumentID, std::string>> &instruments)
{
	mInstruments = instruments;
	mListBox.updateContent();

	// Auto-select first instrument
	if (!mInstruments.empty())
	{
		selectInstrument(mInstruments[0].first);
	}
}


void InstrumentSidebar::setInstrumentSelectedCallback(InstrumentSelectedCallback callback)
{
	mCallback = std::move(callback);
}


void InstrumentSidebar::selectInstrument(InstrumentID id)
{
	mSelectedID = id;

	for (int i = 0; i < static_cast<int>(mInstruments.size()); ++i)
	{
		if (mInstruments[i].first == id)
		{
			mListBox.selectRow(i);
			break;
		}
	}

	mListBox.repaint();

	if (mCallback)
		mCallback(id);
}


int InstrumentSidebar::getNumRows()
{
	return static_cast<int>(mInstruments.size());
}


void InstrumentSidebar::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
	if (rowNumber < 0 || rowNumber >= static_cast<int>(mInstruments.size()))
		return;

	auto *lnf	   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	bool isSelected = mInstruments[rowNumber].first == mSelectedID;

	// Background
	if (isSelected && lnf)
	{
		g.setColour(lnf->getSidebarSelectedColour());
		g.fillRect(0, 0, width, height);

		// Gold left accent bar
		g.setColour(lnf->getAccentColour());
		g.fillRect(0, 0, 3, height);
	}

	// Icon placeholder
	const int iconSize = 36;
	const int iconX	   = 16;
	const int iconY	   = (height - iconSize) / 2;

	if (lnf)
		g.setColour(isSelected ? lnf->getSurfaceElevatedColour() : lnf->getSurfaceColour());
	else
		g.setColour(juce::Colour(30, 27, 42));

	g.fillRoundedRectangle(static_cast<float>(iconX), static_cast<float>(iconY),
						   static_cast<float>(iconSize), static_cast<float>(iconSize), 6.0f);

	// Icon text (first 2 letters)
	auto name = mInstruments[rowNumber].second;
	if (lnf)
		g.setColour(isSelected ? lnf->getAccentColour() : lnf->getTextSecondaryColour());
	else
		g.setColour(juce::Colour(158, 154, 142));

	g.setFont(juce::Font(16.0f));
	g.drawText(juce::String(name.substr(0, 2)),
			   iconX, iconY, iconSize, iconSize,
			   juce::Justification::centred, false);

	// Instrument name
	const int textX = iconX + iconSize + 14;
	if (lnf)
	{
		g.setColour(isSelected ? lnf->getTextPrimaryColour() : lnf->getTextSecondaryColour());
		auto nameFont = juce::Font(lnf->getInstrumentTypeface()).withHeight(16.0f);
		nameFont.setExtraKerningFactor(0.003f);
		g.setFont(nameFont);
	}
	else
	{
		g.setColour(juce::Colour(238, 233, 218));
		g.setFont(juce::Font(16.0f));
	}

	g.drawText(name, textX, 0, width - textX - 8, height, juce::Justification::centredLeft, true);
}


void InstrumentSidebar::listBoxItemClicked(int row, const juce::MouseEvent &)
{
	if (row >= 0 && row < static_cast<int>(mInstruments.size()))
	{
		selectInstrument(mInstruments[row].first);
	}
}
