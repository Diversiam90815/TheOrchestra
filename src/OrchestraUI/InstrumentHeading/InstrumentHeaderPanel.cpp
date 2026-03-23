/*
  ==============================================================================
	Module			InstrumentHeaderPanel
	Description		Displays instrument name, image, family, clefs, and transposition
  ==============================================================================
*/

#include "InstrumentHeaderPanel.h"
#include "CustomLookAndFeel.h"
#include "Helper.h"


static Clef stringToClef(const std::string &str)
{
	if (str == "Treble")
		return Clef::Treble;
	if (str == "Bass")
		return Clef::Bass;
	if (str == "Alto")
		return Clef::Alto;
	if (str == "Tenor")
		return Clef::Tenor;
	return Clef::Treble;
}


InstrumentHeaderPanel::InstrumentHeaderPanel() : OrchestraPanel("")
{
	mNameLabel.setName("InstrumentName");
	addAndMakeVisible(mNameLabel);

	mFamilyLabel.setName("FamilySubtitle");
	addAndMakeVisible(mFamilyLabel);

	addAndMakeVisible(mInstrumentImage);
}


void InstrumentHeaderPanel::setInstrument(const InstrumentProfile &instrument)
{
	mNameLabel.setText(instrument.getName(), juce::dontSendNotification);

	// Get family name from ID
	auto familyName = getFamilyNameFromKey(instrument.getInstrumentID());
	mFamilyLabel.setText(familyName, juce::dontSendNotification);

	// Store clefs and transposition info
	mClefs			   = instrument.getClefs();
	mHasTransposition  = !instrument.getRange().getTransposition().empty();
	mCurrentPitchMode  = PitchMode::Written;

	if (!mClefs.empty())
		mCurrentClef = stringToClef(mClefs[0]);

	// Load instrument image
	juce::File imageFile = mFileManager.getInstrumentImage(TypeOfImage::InstrumentImage, instrument.getInstrumentID());
	if (imageFile.existsAsFile())
	{
		juce::Image img = juce::ImageFileFormat::loadFrom(imageFile);
		if (img.isValid())
		{
			img = img.rescaled(120, 84, juce::Graphics::highResamplingQuality);
			mInstrumentImage.setImage(img);
		}
	}

	rebuildMetaTags();
	resized();
	repaint();
}


void InstrumentHeaderPanel::resized()
{
	auto area = getLocalBounds().reduced(kPadding);

	// Image on left
	mInstrumentImage.setBounds(area.removeFromLeft(120).withHeight(84).withY(area.getY()));
	area.removeFromLeft(20); // gap

	// Name and family
	mNameLabel.setBounds(area.removeFromTop(36));
	mFamilyLabel.setBounds(area.removeFromTop(20));

	// Meta tags row
	area.removeFromTop(8);
	int tagX = area.getX();
	const int tagH = 24;
	const int tagGap = 6;

	for (auto &btn : mClefButtons)
	{
		int w = btn->getBestWidthForHeight(tagH) + 16;
		if (w < 70)
			w = 70;
		btn->setBounds(tagX, area.getY(), w, tagH);
		tagX += w + tagGap;
	}

	if (mHasTransposition && mWrittenBtn && mSoundingBtn)
	{
		tagX += 8; // extra separator gap

		int ww = 70;
		mWrittenBtn->setBounds(tagX, area.getY(), ww, tagH);
		tagX += ww + tagGap;
		mSoundingBtn->setBounds(tagX, area.getY(), ww, tagH);
	}
}


void InstrumentHeaderPanel::rebuildMetaTags()
{
	// Remove old buttons
	for (auto &btn : mClefButtons)
		removeChildComponent(btn.get());
	mClefButtons.clear();

	if (mWrittenBtn)
		removeChildComponent(mWrittenBtn.get());
	if (mSoundingBtn)
		removeChildComponent(mSoundingBtn.get());
	mWrittenBtn.reset();
	mSoundingBtn.reset();

	// Create clef buttons
	for (size_t i = 0; i < mClefs.size(); ++i)
	{
		auto btn = std::make_unique<juce::TextButton>(mClefs[i] + " Clef");
		btn->setName("MetaTag");
		btn->setClickingTogglesState(true);
		btn->setRadioGroupId(100);
		btn->setToggleState(i == 0, juce::dontSendNotification);

		auto clef = stringToClef(mClefs[i]);
		btn->onClick = [this, clef]()
		{
			mCurrentClef = clef;
			if (mClefChangedCallback)
				mClefChangedCallback(clef);
		};

		addAndMakeVisible(btn.get());
		mClefButtons.push_back(std::move(btn));
	}

	// Create Written/Sounding toggles for transposing instruments
	if (mHasTransposition)
	{
		mWrittenBtn = std::make_unique<juce::TextButton>("Written");
		mWrittenBtn->setName("MetaTag");
		mWrittenBtn->setClickingTogglesState(true);
		mWrittenBtn->setRadioGroupId(101);
		mWrittenBtn->setToggleState(true, juce::dontSendNotification);
		mWrittenBtn->onClick = [this]()
		{
			mCurrentPitchMode = PitchMode::Written;
			if (mPitchModeChangedCallback)
				mPitchModeChangedCallback(PitchMode::Written);
		};
		addAndMakeVisible(mWrittenBtn.get());

		mSoundingBtn = std::make_unique<juce::TextButton>("Sounding");
		mSoundingBtn->setName("MetaTag");
		mSoundingBtn->setClickingTogglesState(true);
		mSoundingBtn->setRadioGroupId(101);
		mSoundingBtn->setToggleState(false, juce::dontSendNotification);
		mSoundingBtn->onClick = [this]()
		{
			mCurrentPitchMode = PitchMode::Sounding;
			if (mPitchModeChangedCallback)
				mPitchModeChangedCallback(PitchMode::Sounding);
		};
		addAndMakeVisible(mSoundingBtn.get());
	}
}


void InstrumentHeaderPanel::setClefChangedCallback(ClefChangedCallback callback)
{
	mClefChangedCallback = std::move(callback);
}


void InstrumentHeaderPanel::setPitchModeChangedCallback(PitchModeChangedCallback callback)
{
	mPitchModeChangedCallback = std::move(callback);
}
