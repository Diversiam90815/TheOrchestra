/*
  ==============================================================================
	Module			InstrumentSidebar
	Description		Visual instrument browser sidebar with selection highlighting
  ==============================================================================
*/

#include "InstrumentSidebar.h"
#include "CustomLookAndFeel.h"
#include "Theme.h"


InstrumentSidebar::InstrumentSidebar()
{
	mListBox.setModel(this);
	mListBox.setRowHeight(Chrome::sidebarRowH);
	mListBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
	mListBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
	addAndMakeVisible(mListBox);
}


void InstrumentSidebar::paint(juce::Graphics &g)
{
	const auto &t = themeFor(*this);

	g.fillAll(t.background);

	// Right border
	g.setColour(juce::Colours::white.withAlpha(0.04f));
	g.fillRect(getWidth() - 1, 0, 1, getHeight());
}


void InstrumentSidebar::resized()
{
	mListBox.setBounds(getLocalBounds().withTrimmedTop(Space::m).withTrimmedBottom(Space::m));
}


void InstrumentSidebar::setInstruments(const std::vector<std::pair<InstrumentID, std::string>> &instruments)
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

	auto	   *lnf		   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t		   = themeFor(*this);

	const bool	isSelected = mInstruments[rowNumber].first == mSelectedID;

	// Background
	if (isSelected)
	{
		g.setColour(t.sidebarSelected);
		g.fillRect(0, 0, width, height);

		// Gold left accent bar
		g.setColour(t.accent);
		g.fillRect(0, 0, 3, height);
	}

	// Icon placeholder
	const int iconSize = 34;
	const int iconX	   = Space::m;
	const int iconY	   = (height - iconSize) / 2;

	g.setColour(isSelected ? t.surfaceElevated : t.surface);
	g.fillRoundedRectangle((float)iconX, (float)iconY, (float)iconSize, (float)iconSize, Radius::md);

	// Icon text (first 2 letters)
	auto name = mInstruments[rowNumber].second;
	g.setColour(isSelected ? t.accent : t.textSecondary);
	g.setFont(lnf ? lnf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall));
	g.drawText(juce::String(name.substr(0, 2)), iconX, iconY, iconSize, iconSize, juce::Justification::centred, false);

	// Instrument name
	const int textX = iconX + iconSize + Space::m;
	g.setColour(isSelected ? t.textPrimary : t.textSecondary);
	g.setFont(lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body));
	g.drawText(name, textX, 0, width - textX - Space::s, height, juce::Justification::centredLeft, true);
}


void InstrumentSidebar::listBoxItemClicked(int row, const juce::MouseEvent &)
{
	if (row >= 0 && row < static_cast<int>(mInstruments.size()))
	{
		selectInstrument(mInstruments[row].first);
	}
}
