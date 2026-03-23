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

	mTranspositionLabel.setName("SectionTitle");
	addAndMakeVisible(mTranspositionLabel);

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
	mHasTransposition  = (range.getLowerRange() != range.getDisplayedLowerRange())
					  || (range.getHigherRange() != range.getDisplayedHigherRange());
	mCurrentPitchMode  = PitchMode::Written;

	// Derive transposition label (e.g., "in Bb", "in F")
	if (mHasTransposition)
	{
		auto transLabel = deriveTranspositionLabel(range.getLowerRange(), range.getDisplayedLowerRange());
		mTranspositionLabel.setText(transLabel, juce::dontSendNotification);
	}
	else
	{
		mTranspositionLabel.setText("", juce::dontSendNotification);
	}

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

	// Right side: name, family + transposition, meta tags stacked
	auto rightSide = area;

	// Name at top
	mNameLabel.setBounds(rightSide.removeFromTop(36));

	// Family subtitle + transposition label on same row
	auto familyRow = rightSide.removeFromTop(20);
	if (mHasTransposition)
	{
		mFamilyLabel.setBounds(familyRow.removeFromLeft(familyRow.getWidth() / 2));
		mTranspositionLabel.setBounds(familyRow);
	}
	else
	{
		mFamilyLabel.setBounds(familyRow);
		mTranspositionLabel.setBounds(0, 0, 0, 0);
	}

	// Meta tags row
	rightSide.removeFromTop(8);
	int tagX = rightSide.getX();
	const int tagH = 24;
	const int tagGap = 6;

	for (auto &btn : mClefButtons)
	{
		int w = btn->getBestWidthForHeight(tagH) + 16;
		if (w < 70)
			w = 70;
		btn->setBounds(tagX, rightSide.getY(), w, tagH);
		tagX += w + tagGap;
	}

	if (mHasTransposition && mWrittenBtn && mSoundingBtn)
	{
		tagX += 8; // extra separator gap

		int ww = 70;
		mWrittenBtn->setBounds(tagX, rightSide.getY(), ww, tagH);
		tagX += ww + tagGap;
		mSoundingBtn->setBounds(tagX, rightSide.getY(), ww, tagH);
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


juce::String InstrumentHeaderPanel::deriveTranspositionLabel(const std::string &writtenLow, const std::string &soundingLow) const
{
	// Derive the transposition interval by comparing written vs sounding pitch
	// e.g., Clarinet: written E3, sounding D3 → transposition is down a major 2nd → "in Bb"
	// French Horn: written F2, sounding Bb1 → transposition is down a 5th → "in F"

	int writtenMidi	 = turnNotenameIntoMidinumber(writtenLow);
	int soundingMidi = turnNotenameIntoMidinumber(soundingLow);

	if (writtenMidi <= 0 || soundingMidi <= 0)
		return "Transposing";

	// The interval in semitones (positive = sounds lower than written)
	int interval = writtenMidi - soundingMidi;

	// Normalize to 0-11 range (mod 12) to find the transposition key
	int normalised = ((interval % 12) + 12) % 12;

	// Map interval to key name
	// 0 semitones = C (concert pitch, but might be octave transposition)
	// 1 = Db/C#, 2 = Bb (down major 2nd), 3 = A, etc.
	// Note: The convention for transposing instruments:
	// When the instrument plays C, it sounds the transposition note
	// So if written C sounds as Bb, it's "in Bb" (interval = +2 semitones written above sounding)

	static const char *keyNames[] = {
		"in C",	 // 0
		"in B",	 // 1  (sounds a semitone lower)
		"in Bb", // 2  (Clarinet, Trumpet)
		"in A",	 // 3  (Clarinet in A)
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

	// Check for octave transposition (e.g., Double Bass sounds octave lower, Piccolo sounds octave higher)
	if (normalised == 0 && interval != 0)
	{
		if (interval > 0)
			label = "8vb (octave lower)";
		else
			label = "8va (octave higher)";
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
