/*
  ==============================================================================
	Module			SamplerPanel
	Description		Articulation toggle button grid for sampler control
  ==============================================================================
*/

#include "SamplerPanel.h"
#include "CustomLookAndFeel.h"
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

	// Create new buttons
	bool first = true;
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

		if (first)
		{
			btn->setToggleState(true, juce::dontSendNotification);
			mSelected = artic;
			first = false;
		}

		auto articulationCopy = artic;
		btn->onClick = [this, articulationCopy]() { onArticulationClicked(articulationCopy); };

		addAndMakeVisible(btn.get());
		mButtons.push_back(std::move(btn));
	}

	// Update status
	auto selectedName = articulationReverseMap.count(mSelected) ? articulationReverseMap.at(mSelected) : "None";
	mStatusLabel.setText(juce::String(selectedName) + " loaded - " + juce::String(static_cast<int>(mAvailable.size())) + " articulations available",
						 juce::dontSendNotification);

	resized();
	repaint();
}


void SamplerPanel::setArticulationChangedCallback(ArticulationChangedCallback callback)
{
	mCallback = std::move(callback);
}


void SamplerPanel::onArticulationClicked(Articulation articulation)
{
	mSelected = articulation;

	auto selectedName = articulationReverseMap.count(mSelected) ? articulationReverseMap.at(mSelected) : "None";
	mStatusLabel.setText(juce::String(selectedName) + " loaded - " + juce::String(static_cast<int>(mAvailable.size())) + " articulations available",
						 juce::dontSendNotification);

	if (mCallback)
		mCallback(articulation);
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

	// Status label claims the bottom first, so a wrapped second button row can
	// never collide with it.
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
