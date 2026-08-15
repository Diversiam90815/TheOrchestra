/*
  ==============================================================================
	Module			SamplerPanel
	Description		Articulation toggle button grid for sampler control
  ==============================================================================
*/

#include "SamplerPanel.h"
#include "CustomLookAndFeel.h"
#include "TextMeasure.h"
#include "Helper.h"


SamplerPanel::SamplerPanel() : OrchestraPanel("SAMPLER")
{
	mStatusLabel.setName("StatusLabel");
	addAndMakeVisible(mStatusLabel);
}


void SamplerPanel::setAvailableArticulations(std::set<Articulation> available)
{
	mAvailable = std::move(available);

	// Remove old buttons
	for (auto &btn : mButtons)
		removeChildComponent(btn.get());
	mButtons.clear();

	// A new instrument means nothing is loaded yet
	mLoadedArticulation.reset();
	mSamplesReady = false;

	for (auto artic : mAvailable)
	{
		auto btn = std::make_unique<juce::TextButton>();
		btn->setName("Articulation");

		// Get display name
		auto it = articulationReverseMap.find(artic);
		if (it != articulationReverseMap.end())
			btn->setButtonText(it->second);
		else
			btn->setButtonText("Unknown");

		btn->setClickingTogglesState(true);
		btn->setRadioGroupId(200);

		auto articulationCopy = artic;
		btn->onClick		  = [this, articulationCopy]() { onArticulationClicked(articulationCopy); };

		addAndMakeVisible(btn.get());
		mButtons.push_back(std::move(btn));
	}

	updateStatus();
	resized();
	repaint();
}


void SamplerPanel::setArticulationChangedCallback(ArticulationChangedCallback callback)
{
	mCallback = std::move(callback);
}


void SamplerPanel::onArticulationClicked(Articulation articulation)
{
	// Re-clicking the articulation that is already loaded used to re-trigger a
	// full sample reload for no reason.
	if (mLoadedArticulation.has_value() && *mLoadedArticulation == articulation)
		return;

	mSelected			= articulation;
	mLoadedArticulation = articulation;
	mSamplesReady		= mCallback ? mCallback(articulation) : false;

	updateStatus();
	repaint();
}


void SamplerPanel::updateStatus()
{
	juce::String text;

	if (mAvailable.empty())
	{
		text = "No articulations available";
	}
	else if (!mLoadedArticulation.has_value())
	{
		text = "Not loaded";
	}
	else
	{
		auto selectedName = articulationReverseMap.count(mSelected) ? articulationReverseMap.at(mSelected) : "Unknown";

		text = juce::String(selectedName) + (mSamplesReady ? " loaded" : " failed to load") + " - " + juce::String((int)mAvailable.size()) + " articulations available";
	}

	mStatusLabel.setText(text, juce::dontSendNotification);
}


void SamplerPanel::paint(juce::Graphics &g)
{
	OrchestraPanel::paint(g);

	auto					 *lnf		= dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const auto				  titleFont = lnf ? lnf->getSectionTitleFont() : juce::Font(Type::label);
	const int				  titleW	= TextMeasure::lineWidth(titleFont, "SAMPLER");
	const auto				  titleArea = getLocalBounds().reduced(kPadding, 0).withY(kPadding).withHeight(kTitleHeight);

	static const juce::Colour kReady	= juce::Colour::fromRGB(88, 178, 96);
	static const juce::Colour kNotReady = juce::Colour::fromRGB(196, 74, 66);

	const float				  dotY		= (float)titleArea.getCentreY() - kDotSize * 0.5f;
	const float				  dotX		= (float)titleArea.getX() + (float)titleW + Space::s;

	g.setColour((mLoadedArticulation.has_value() && mSamplesReady) ? kReady : kNotReady);
	g.fillEllipse(dotX, dotY, kDotSize, kDotSize);
}


int SamplerPanel::wrappedRowCount(int width) const
{
	if (mButtons.empty())
		return 0;

	const int contentWidth = width - kPadding * 2;
	const int perRow	   = juce::jmax(1, (contentWidth + kGap) / (kButtonWidth + kGap));

	return ((int)mButtons.size() + perRow - 1) / perRow;
}


int SamplerPanel::getPreferredHeight(int width) const
{
	const int rows = wrappedRowCount(width);

	if (rows == 0)
		return getChromeHeight() + kStatusHeight;

	const int buttonBlock = rows * kButtonHeight + (rows - 1) * kGap;

	return getChromeHeight() + buttonBlock + Space::m + kStatusHeight;
}


void SamplerPanel::resized()
{
	auto area	= getContentArea();

	auto status = area.removeFromBottom(kStatusHeight);
	mStatusLabel.setBounds(status);

	area.removeFromBottom(Space::m);

	int x = area.getX();
	int y = area.getY();

	for (auto &btn : mButtons)
	{
		if (x + kButtonWidth > area.getRight() && x != area.getX())
		{
			x = area.getX();
			y += kButtonHeight + kGap;
		}
		btn->setBounds(x, y, kButtonWidth, kButtonHeight);
		x += kButtonWidth + kGap;
	}
}
