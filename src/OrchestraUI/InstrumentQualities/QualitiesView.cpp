/*
  ==============================================================================
	Module			QualitiesView
	Description		View box containing the qualities of the differnt ranges of the instrument
  ==============================================================================
*/

#include "QualitiesView.h"


void QualitiesView::init()
{
	setSize(mWidth, mHeight);

	// Title
	addAndConfigureLabel(mTitle, "QualitiesTitle", "Qualities", mQualitiesTitleX, mQualitiesTitleY, mQualitiesTitleWidth, mQualitiesTitleHeight);

	// Note buttons
	addAndConfigureButton(mFirstLowerNote, "FirstQualityLower", mLowerNoteX, mFirstRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mFirstHigherNote, "FirstQualityHigher", mHigherNoteX, mFirstRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	addAndConfigureButton(mSecondLowerNote, "SecondQualityLower", mLowerNoteX, mSecondRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mSecondHigherNote, "SecondQualityHigher", mHigherNoteX, mSecondRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	addAndConfigureButton(mThirdLowerNote, "ThirdQualityLower", mLowerNoteX, mThirdRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mThirdHigherNote, "ThirdQualityHigher", mHigherNoteX, mThirdRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	addAndConfigureButton(mFourthLowerNote, "FourthQualityLower", mLowerNoteX, mFourthRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mFourthHigherNote, "FourthQualityHigher", mHigherNoteX, mFourthRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	// Qualities TextEditors
	addAndConfigureTextEditor(mFirstQuality, mQualityX, mFirstRowY, mQualityWidth, mQualityHeight);
	addAndConfigureTextEditor(mSecondQuality, mQualityX, mSecondRowY, mQualityWidth, mQualityHeight);
	addAndConfigureTextEditor(mThirdQuality, mQualityX, mThirdRowY, mQualityWidth, mQualityHeight);
	addAndConfigureTextEditor(mFourthQuality, mQualityX, mFourthRowY, mQualityWidth, mQualityHeight);
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

		if (range.contains("-")) // Ranges are divided with a '-'
		{
			lowerNote  = getLowerOrHigherNote(range, true);
			higherNote = getLowerOrHigherNote(range, false);
		}
		else
		{
			// Single note case: Use the single note as both lower and higher note
			lowerNote  = range.trim();
			higherNote = range.trim();
		}

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
