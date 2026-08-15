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
	mClefs			  = instrument.getClefs();
	auto range		  = instrument.getRange();
	mHasTransposition = (range.getWrittenLowNote() != range.getSoundingLowNote()) || (range.getWrittenHighNote() != range.getSoundingHighNote());
	mCurrentPitchMode = PitchMode::Written;

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
			img = img.rescaled(kImageWidth, kImageHeight, juce::Graphics::highResamplingQuality);
			mInstrumentImage.setImage(img);
		}
	}

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

	int		  tagX	  = rightSide.getX();
	const int tagY	  = rightSide.getY();
	const int clefW	  = 88;
	const int transW  = 116;
	const int toggleW = 104;

	for (auto &btn : mClefButtons)
	{
		btn->setBounds(tagX, tagY, clefW, kTagHeight);
		tagX += clefW + kTagGap;
	}

	if (mTranspositionInfoLabel)
	{
		mTranspositionInfoLabel->setBounds(tagX, tagY, transW, kTagHeight);
		tagX += transW + kTagGap;
	}

	if (mHasTransposition && mWrittenBtn && mSoundingBtn)
	{
		tagX += Space::s; // separator between info pills and the toggle pair

		mWrittenBtn->setBounds(tagX, tagY, toggleW, kTagHeight);
		tagX += toggleW + kTagGap;
		mSoundingBtn->setBounds(tagX, tagY, toggleW, kTagHeight);
	}
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
		const Clef clef	   = stringToClef(mClefs[i]);
		const bool isActive = clef == mCurrentClef;

		auto	   btn	   = std::make_unique<juce::TextButton>(mClefs[i]);
		btn->setName("MetaTag");
		btn->setClickingTogglesState(true);
		btn->setRadioGroupId(102);
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

	int				   interval	  = writtenMidi - soundingMidi;
	int				   normalised = ((interval % 12) + 12) % 12;

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
