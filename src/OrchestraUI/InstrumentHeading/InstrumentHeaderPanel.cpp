/*
  ==============================================================================
	Module			InstrumentHeaderPanel
	Description		Displays instrument name, image, family, clefs (info), transposition
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
	auto range		   = instrument.getRange();
	mHasTransposition  = (range.getWrittenLowNote() != range.getSoundingLowNote())
					  || (range.getWrittenHighNote() != range.getSoundingHighNote());
	mCurrentPitchMode  = PitchMode::Written;

	// Derive transposition label
	if (mHasTransposition)
		mTranspositionText = deriveTranspositionLabel(range.getWrittenLowNote(), range.getSoundingLowNote());
	else
		mTranspositionText = "";

	if (!mClefs.empty())
		mCurrentClef = stringToClef(mClefs[0]);

	// Load instrument image
	juce::File imageFile = mFileManager.getInstrumentImage(TypeOfImage::InstrumentImage, instrument.getInstrumentID());
	if (imageFile.existsAsFile())
	{
		juce::Image img = juce::ImageFileFormat::loadFrom(imageFile);
		if (img.isValid())
		{
			img = img.rescaled(90, 84, juce::Graphics::highResamplingQuality);
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

	// Image on the left, vertically centered
	auto imageArea = area.removeFromLeft(90);
	mInstrumentImage.setBounds(imageArea.withHeight(84).withY(imageArea.getY() + (imageArea.getHeight() - 84) / 2));
	area.removeFromLeft(16); // gap

	// Right side: name, family, meta tags stacked
	auto rightSide = area;

	// Name at top
	mNameLabel.setBounds(rightSide.removeFromTop(36));

	// Family subtitle
	mFamilyLabel.setBounds(rightSide.removeFromTop(20));

	// Meta tags row: [clef info labels] [transposition info] [Written | Sounding toggles]
	rightSide.removeFromTop(8);
	int tagX = rightSide.getX();
	const int tagH = 24;
	const int tagGap = 6;

	// Clef info labels (non-interactive)
	for (auto &label : mClefLabels)
	{
		int w = 80;
		label->setBounds(tagX, rightSide.getY(), w, tagH);
		tagX += w + tagGap;
	}

	// Transposition info label
	if (mTranspositionInfoLabel)
	{
		int w = 90;
		mTranspositionInfoLabel->setBounds(tagX, rightSide.getY(), w, tagH);
		tagX += w + tagGap;
	}

	// Written/Sounding toggle buttons
	if (mHasTransposition && mWrittenBtn && mSoundingBtn)
	{
		tagX += 4; // small separator

		int ww = 80;
		mWrittenBtn->setBounds(tagX, rightSide.getY(), ww, tagH);
		tagX += ww + tagGap;
		mSoundingBtn->setBounds(tagX, rightSide.getY(), ww, tagH);
	}
}


void InstrumentHeaderPanel::rebuildMetaTags()
{
	// Remove old components
	for (auto &label : mClefLabels)
		removeChildComponent(label.get());
	mClefLabels.clear();

	if (mTranspositionInfoLabel)
		removeChildComponent(mTranspositionInfoLabel.get());
	mTranspositionInfoLabel.reset();

	if (mWrittenBtn)
		removeChildComponent(mWrittenBtn.get());
	if (mSoundingBtn)
		removeChildComponent(mSoundingBtn.get());
	mWrittenBtn.reset();
	mSoundingBtn.reset();

	// Create clef info labels (non-interactive pills)
	for (size_t i = 0; i < mClefs.size(); ++i)
	{
		auto label = std::make_unique<juce::Label>("MetaInfo", mClefs[i] + " Clef");
		label->setJustificationType(juce::Justification::centred);
		addAndMakeVisible(label.get());
		mClefLabels.push_back(std::move(label));
	}

	// Create transposition info label if applicable
	if (mHasTransposition && mTranspositionText.isNotEmpty())
	{
		mTranspositionInfoLabel = std::make_unique<juce::Label>("MetaInfo", mTranspositionText);
		mTranspositionInfoLabel->setJustificationType(juce::Justification::centred);
		addAndMakeVisible(mTranspositionInfoLabel.get());
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


juce::String InstrumentHeaderPanel::deriveTranspositionLabel(const std::string &writtenLow, const std::string &soundingLow) const
{
	int writtenMidi	 = turnNotenameIntoMidinumber(writtenLow);
	int soundingMidi = turnNotenameIntoMidinumber(soundingLow);

	if (writtenMidi <= 0 || soundingMidi <= 0)
		return "Transposing";

	int interval   = writtenMidi - soundingMidi;
	int normalised = ((interval % 12) + 12) % 12;

	static const char *keyNames[] = {
		"in C",	 // 0
		"in B",	 // 1
		"in Bb", // 2  (Clarinet, Trumpet)
		"in A",	 // 3
		"in Ab", // 4
		"in G",	 // 5  (Alto Flute)
		"in Gb", // 6
		"in F",	 // 7  (French Horn, Cor Anglais)
		"in E",	 // 8
		"in Eb", // 9  (Alto Sax, Eb Clarinet)
		"in D",	 // 10
		"in Db", // 11
	};

	juce::String label = keyNames[normalised];

	// Check for octave transposition
	if (normalised == 0 && interval != 0)
	{
		if (interval > 0)
			label = "8vb";
		else
			label = "8va";
	}

	return label;
}


void InstrumentHeaderPanel::setClefChangedCallback(ClefChangedCallback callback)
{
	mClefChangedCallback = std::move(callback);
}


void InstrumentHeaderPanel::setPitchModeChangedCallback(PitchModeChangedCallback callback)
{
	mPitchModeChangedCallback = std::move(callback);
}
