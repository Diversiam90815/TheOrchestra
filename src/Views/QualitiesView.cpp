/*
  ==============================================================================

	Module			QualitiesView
	Description		View box containing the qualities of the differnt ranges of the instrument

  ==============================================================================
*/

#include "QualitiesView.h"


QualitiesView::QualitiesView()
{
}


QualitiesView::~QualitiesView()
{
}


void QualitiesView::init()
{
	setSize(mWidth, mHeight);

	// Set the title
	addAndMakeVisible(&mTitle);
	mTitle.setName("QualitiesTitle");
	mTitle.setText("Qualities", dontSendNotification);
	mTitle.setBounds(mQualitiesTitleX, mQualitiesTitleY, mQualitiesTitleWidth, mQualitiesTitleHeight);

	// Settings the note names positions
	addAndMakeVisible(&mFirstLowerNote);
	mFirstLowerNote.setName("FirstQualityLower");
	mFirstLowerNote.setBounds(mLowerNoteX, mFirstRowY, mNoteButtonWidth, mNoteButtonHeight);
	mFirstLowerNote.setConnectedEdges(Button::ConnectedOnRight);
	mFirstLowerNote.setVisible(false);

	addAndMakeVisible(&mFirstHigherNote);
	mFirstHigherNote.setName("FirstQualityHigher");
	mFirstHigherNote.setBounds(mHigherNoteX, mFirstRowY, mNoteButtonWidth, mNoteButtonHeight);
	mFirstHigherNote.setConnectedEdges(Button::ConnectedOnLeft);
	mFirstHigherNote.setVisible(false);

	addAndMakeVisible(&mSecondLowerNote);
	mSecondLowerNote.setName("SecondQualityLower");
	mSecondLowerNote.setBounds(mLowerNoteX, mSecondRowY, mNoteButtonWidth, mNoteButtonHeight);
	mSecondLowerNote.setConnectedEdges(Button::ConnectedOnRight);
	mSecondLowerNote.setVisible(false);

	addAndMakeVisible(&mSecondHigherNote);
	mSecondHigherNote.setName("SecondQualityHigher");
	mSecondHigherNote.setBounds(mHigherNoteX, mSecondRowY, mNoteButtonWidth, mNoteButtonHeight);
	mSecondHigherNote.setConnectedEdges(Button::ConnectedOnLeft);
	mSecondHigherNote.setVisible(false);

	addAndMakeVisible(&mThirdLowerNote);
	mThirdLowerNote.setName("ThirdQualityLower");
	mThirdLowerNote.setBounds(mLowerNoteX, mThirdRowY, mNoteButtonWidth, mNoteButtonHeight);
	mThirdLowerNote.setConnectedEdges(Button::ConnectedOnRight);
	mThirdLowerNote.setVisible(false);

	addAndMakeVisible(&mThirdHigherNote);
	mThirdHigherNote.setName("ThirdQualityHigher");
	mThirdHigherNote.setBounds(mHigherNoteX, mThirdRowY, mNoteButtonWidth, mNoteButtonHeight);
	mThirdHigherNote.setConnectedEdges(Button::ConnectedOnLeft);
	mThirdHigherNote.setVisible(false);

	addAndMakeVisible(&mFourthLowerNote);
	mFourthLowerNote.setName("FourthQualityLower");
	mFourthLowerNote.setBounds(mLowerNoteX, mFourthRowY, mNoteButtonWidth, mNoteButtonHeight);
	mFourthLowerNote.setConnectedEdges(Button::ConnectedOnRight);
	mFourthLowerNote.setVisible(false);

	addAndMakeVisible(&mFourthHigherNote);
	mFourthHigherNote.setName("FourthQualityHigher");
	mFourthHigherNote.setBounds(mHigherNoteX, mFourthRowY, mNoteButtonWidth, mNoteButtonHeight);
	mFourthHigherNote.setConnectedEdges(Button::ConnectedOnLeft);
	mFourthHigherNote.setVisible(false);

	// Setting the qualities positions
	addAndMakeVisible(&mFirstQuality);
	mFirstQuality.setBounds(mQualityX, mFirstRowY, mQualityWidth, mQualityHeight);
	mFirstQuality.setJustification(Justification::centredTop);
	mFirstQuality.setFont(mCustomLookNFeel.getTextEditorFont());

	addAndMakeVisible(&mSecondQuality);
	mSecondQuality.setBounds(mQualityX, mSecondRowY, mQualityWidth, mQualityHeight);
	mSecondQuality.setJustification(Justification::centredTop);
	mSecondQuality.setFont(mCustomLookNFeel.getTextEditorFont());

	addAndMakeVisible(&mThirdQuality);
	mThirdQuality.setBounds(mQualityX, mThirdRowY, mQualityWidth, mQualityHeight);
	mThirdQuality.setJustification(Justification::centredTop);
	mThirdQuality.setFont(mCustomLookNFeel.getTextEditorFont());

	addAndMakeVisible(&mFourthQuality);
	mFourthQuality.setBounds(mQualityX, mFourthRowY, mQualityWidth, mQualityHeight);
	mFourthQuality.setJustification(Justification::centredTop);
	mFourthQuality.setFont(mCustomLookNFeel.getTextEditorFont());
}


void QualitiesView::displayInstrument(InstrumentInfo &instrument)
{
	StringArray										qualities = instrument.getQualities();

	std::vector<std::tuple<String, String, String>> parsedQualities;

	// Dividing the qualities and the ranges into separate parts
	for (auto &quality : qualities)
	{
		String lowerNote, higherNote, qualityText, range;

		range		= splitColonizedStrings(quality, true);
		qualityText = splitColonizedStrings(quality, false);
		lowerNote	= getLowerOrHigherNote(range, true);
		higherNote	= getLowerOrHigherNote(range, false);

		parsedQualities.emplace_back(lowerNote, higherNote, qualityText);
	}

	TextButton *lowerNotes[]	 = {&mFirstLowerNote, &mSecondLowerNote, &mThirdLowerNote, &mFourthLowerNote};
	TextButton *higherNotes[]	 = {&mFirstHigherNote, &mSecondHigherNote, &mThirdHigherNote, &mFourthHigherNote};
	TextEditor *qualitiesTexts[] = {&mFirstQuality, &mSecondQuality, &mThirdQuality, &mFourthQuality};

	auto		configureEditor	 = [](TextEditor &editor, const String &text)
	{
		editor.setReadOnly(false);
		editor.setVisible(!text.isEmpty());
		editor.setText(text, dontSendNotification);
		editor.setMultiLine(true);
		editor.setReadOnly(true);
	};

	auto configureButton = [](TextButton &button, const String &text)
	{
		button.setVisible(!text.isEmpty());
		button.setButtonText(text);
	};

	for (size_t i = 0; i < std::size(lowerNotes); ++i)
	{
		if (i < parsedQualities.size())
		{
			const auto &[lowerNote, higherNote, qualityText] = parsedQualities[i];

			configureButton(*lowerNotes[i], lowerNote);
			configureButton(*higherNotes[i], higherNote);
			configureEditor(*qualitiesTexts[i], qualityText);
		}
		else
		{
			lowerNotes[i]->setVisible(false);
			higherNotes[i]->setVisible(false);
			qualitiesTexts[i]->setVisible(false);
		}
	}
}
