/*
  ==============================================================================
	Module			SamplerPanel
	Description		Articulation toggle button grid for sampler control
  ==============================================================================
*/

#include "SamplerPanel.h"
#include "CustomLookAndFeel.h"
#include "Helper.h"


SamplerPanel::SamplerPanel() : OrchestraPanel("Sampler")
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


void SamplerPanel::resized()
{
	auto area = getContentArea();

	// Layout buttons in a wrapping flow
	const int btnW	 = 100;
	const int btnH	 = 32;
	const int gap	 = 8;

	int x = area.getX();
	int y = area.getY();

	for (auto &btn : mButtons)
	{
		if (x + btnW > area.getRight() && x != area.getX())
		{
			x = area.getX();
			y += btnH + gap;
		}
		btn->setBounds(x, y, btnW, btnH);
		x += btnW + gap;
	}

	// Status label at bottom
	mStatusLabel.setBounds(area.getX(), area.getBottom() - 18, area.getWidth(), 18);
}
