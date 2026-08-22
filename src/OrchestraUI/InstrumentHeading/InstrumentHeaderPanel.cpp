/*
  ==============================================================================
	Module			InstrumentHeaderPanel
	Description		Displays instrument name, image, family, clefs (info), transposition
  ==============================================================================
*/

#include "InstrumentHeaderPanel.h"
#include "CustomLookAndFeel.h"
#include "TextMeasure.h"
#include "Helper.h"


InstrumentHeaderPanel::InstrumentHeaderPanel() : OrchestraPanel("")
{
	setLabelStyle(mNameLabel, LabelStyle::InstrumentName);
	addAndMakeVisible(mNameLabel);

	setLabelStyle(mFamilyLabel, LabelStyle::FamilySubtitle);
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
	mClefs			  = instrument.getClefs();
	auto range		  = instrument.getRange();
	mHasTransposition = (range.getWrittenLowNote() != range.getSoundingLowNote()) || (range.getWrittenHighNote() != range.getSoundingHighNote());
	mCurrentPitchMode = PitchMode::Written;

	// Derive transposition label
	if (mHasTransposition)
		mTranspositionText = juce::String(deriveTranspositionLabel(range.getWrittenLowNote(), range.getSoundingLowNote()));
	else
		mTranspositionText = "";

	if (!mClefs.empty())
		mCurrentClef = clefFromString(mClefs[0]);

	juce::File imageFile = mFileManager.getInstrumentImage(TypeOfImage::InstrumentImage, instrument.getInstrumentID());
	mInstrumentImage.setImageFile(imageFile);

	if (imageFile.existsAsFile() && !mInstrumentImage.hasImage())
		LOG_WARNING("Could not decode instrument image: {}", imageFile.getFullPathName().toStdString());

	rebuildMetaTags();
	resized();
	repaint();
}


int InstrumentHeaderPanel::getPreferredHeight(int /*width*/) const
{
	const int textStack = kNameHeight + kFamilyHeight + Space::s + kTagHeight;

	return getChromeHeight() + juce::jmax(kImageHeight, textStack);
}


void InstrumentHeaderPanel::resized()
{
	auto area	   = getLocalBounds().reduced(kPadding);

	// Image on the left, vertically centered
	auto imageArea = area.removeFromLeft(kImageWidth);
	mInstrumentImage.setBounds(imageArea.withSizeKeepingCentre(kImageWidth, kImageHeight));
	area.removeFromLeft(Space::xl);

	// Right side: name, family, meta tags stacked
	auto rightSide = area;

	mNameLabel.setBounds(rightSide.removeFromTop(kNameHeight));
	mFamilyLabel.setBounds(rightSide.removeFromTop(kFamilyHeight));

	// Meta tags row: [clef info labels] [transposition info] [Written | Sounding toggles]
	rightSide.removeFromTop(Space::s);

	int		  tagX = rightSide.getX();
	const int tagY = rightSide.getY();

	for (auto &btn : mClefButtons)
	{
		const int w = pillWidth(btn->getButtonText());
		btn->setBounds(tagX, tagY, w, kTagHeight);
		tagX += w + kTagGap;
	}

	if (mTranspositionInfoLabel)
	{
		const int w = pillWidth(mTranspositionInfoLabel->getText());
		mTranspositionInfoLabel->setBounds(tagX, tagY, w, kTagHeight);
		tagX += w + kTagGap;
	}

	if (mHasTransposition && mWrittenBtn && mSoundingBtn)
	{
		tagX += Space::s; // separator between info pills and the toggle pair

		const int writtenW = pillWidth(mWrittenBtn->getButtonText());
		mWrittenBtn->setBounds(tagX, tagY, writtenW, kTagHeight);
		tagX += writtenW + kTagGap;

		mSoundingBtn->setBounds(tagX, tagY, pillWidth(mSoundingBtn->getButtonText()), kTagHeight);
	}
}


int InstrumentHeaderPanel::pillWidth(const juce::String &text) const
{
	auto	  *lnf	= dynamic_cast<CustomLookAndFeel *>(&const_cast<InstrumentHeaderPanel *>(this)->getLookAndFeel());
	const auto font = lnf ? lnf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall);

	// Measured rather than fixed, so longer labels ("Sounding", "in Bb") cannot clip.
	return juce::jmax(kMinTagWidth, TextMeasure::lineWidth(font, text) + kTagPadX * 2);
}


void InstrumentHeaderPanel::rebuildMetaTags()
{
	// Remove old components
	for (auto &btn : mClefButtons)
		removeChildComponent(btn.get());
	mClefButtons.clear();

	if (mTranspositionInfoLabel)
		removeChildComponent(mTranspositionInfoLabel.get());
	mTranspositionInfoLabel.reset();

	if (mWrittenBtn)
		removeChildComponent(mWrittenBtn.get());
	if (mSoundingBtn)
		removeChildComponent(mSoundingBtn.get());
	mWrittenBtn.reset();
	mSoundingBtn.reset();

	for (size_t i = 0; i < mClefs.size(); ++i)
	{
		const Clef clef		= clefFromString(mClefs[i]);
		const bool isActive = clef == mCurrentClef;

		auto	   btn		= std::make_unique<juce::TextButton>(mClefs[i]);
		setButtonStyle(*btn, ButtonStyle::MetaTag);
		btn->setClickingTogglesState(true);
		btn->setRadioGroupId(RadioGroup::clef);
		btn->setToggleState(isActive, juce::dontSendNotification);
		btn->onClick = [this, clef]()
		{
			mCurrentClef = clef;
			if (mClefChangedCallback)
				mClefChangedCallback(clef);
		};
		addAndMakeVisible(btn.get());
		mClefButtons.push_back(std::move(btn));
	}

	// Create transposition info label if applicable
	if (mHasTransposition && mTranspositionText.isNotEmpty())
	{
		mTranspositionInfoLabel = std::make_unique<juce::Label>("transposition", mTranspositionText);
		setLabelStyle(*mTranspositionInfoLabel, LabelStyle::MetaInfo);
		mTranspositionInfoLabel->setJustificationType(juce::Justification::centred);
		addAndMakeVisible(mTranspositionInfoLabel.get());
	}

	// Create Written/Sounding toggles for transposing instruments
	if (mHasTransposition)
	{
		mWrittenBtn = std::make_unique<juce::TextButton>("Written");
		setButtonStyle(*mWrittenBtn, ButtonStyle::MetaTag);
		mWrittenBtn->setClickingTogglesState(true);
		mWrittenBtn->setRadioGroupId(RadioGroup::pitchMode);
		mWrittenBtn->setToggleState(true, juce::dontSendNotification);
		mWrittenBtn->onClick = [this]()
		{
			mCurrentPitchMode = PitchMode::Written;
			if (mPitchModeChangedCallback)
				mPitchModeChangedCallback(PitchMode::Written);
		};
		addAndMakeVisible(mWrittenBtn.get());

		mSoundingBtn = std::make_unique<juce::TextButton>("Sounding");
		setButtonStyle(*mSoundingBtn, ButtonStyle::MetaTag);
		mSoundingBtn->setClickingTogglesState(true);
		mSoundingBtn->setRadioGroupId(RadioGroup::pitchMode);
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
