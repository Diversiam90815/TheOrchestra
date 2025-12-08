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
	addAndConfigureLabel(mTitle, "QualitiesTitle", "Registers", mQualitiesTitleX, mQualitiesTitleY, mQualitiesTitleWidth, mQualitiesTitleHeight);

	// Note buttons
	addAndConfigureButton(mFirstLowerNote, "FirstQualityLower", mLowerNoteX, mFirstRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mFirstHigherNote, "FirstQualityHigher", mHigherNoteX, mFirstRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	addAndConfigureButton(mSecondLowerNote, "SecondQualityLower", mLowerNoteX, mSecondRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mSecondHigherNote, "SecondQualityHigher", mHigherNoteX, mSecondRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	addAndConfigureButton(mThirdLowerNote, "ThirdQualityLower", mLowerNoteX, mThirdRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mThirdHigherNote, "ThirdQualityHigher", mHigherNoteX, mThirdRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	addAndConfigureButton(mFourthLowerNote, "FourthQualityLower", mLowerNoteX, mFourthRowY, mNoteButtonWidth, mNoteButtonHeight, false);
	addAndConfigureButton(mFourthHigherNote, "FourthQualityHigher", mHigherNoteX, mFourthRowY, mNoteButtonWidth, mNoteButtonHeight, false);

	// InstrumentRegisters TextEditors
	addAndConfigureTextEditor(mFirstQuality, mQualityX, mFirstRowY, mQualityWidth, mQualityHeight);
	addAndConfigureTextEditor(mSecondQuality, mQualityX, mSecondRowY, mQualityWidth, mQualityHeight);
	addAndConfigureTextEditor(mThirdQuality, mQualityX, mThirdRowY, mQualityWidth, mQualityHeight);
	addAndConfigureTextEditor(mFourthQuality, mQualityX, mFourthRowY, mQualityWidth, mQualityHeight);
}


void QualitiesView::displayInstrument(InstrumentProfile &instrument)
{
	const auto														  registers = instrument.getRegisters();

	std::vector<std::tuple<juce::String, juce::String, juce::String>> parsedRegisters;

	// Dividing the qualities and the ranges into separate parts
	for (auto &quality : registers)
	{
		std::string lowerNote	= quality.getLowerRange();
		std::string higherNote	= quality.getHigherRange();
		std::string description = quality.getDescription();

		parsedRegisters.emplace_back(lowerNote, higherNote, description);
	}

	juce::TextButton *lowerNotes[]	   = {&mFirstLowerNote, &mSecondLowerNote, &mThirdLowerNote, &mFourthLowerNote};
	juce::TextButton *higherNotes[]	   = {&mFirstHigherNote, &mSecondHigherNote, &mThirdHigherNote, &mFourthHigherNote};
	juce::TextEditor *qualitiesTexts[] = {&mFirstQuality, &mSecondQuality, &mThirdQuality, &mFourthQuality};

	auto			  configureEditor  = [](juce::TextEditor &editor, const juce::String &text)
	{
		editor.setReadOnly(false);
		editor.setVisible(!text.isEmpty());
		editor.setText(text, juce::dontSendNotification);
		editor.setMultiLine(true);
		editor.setReadOnly(true);
	};

	auto configureButton = [](juce::TextButton &button, const juce::String &text)
	{
		button.setVisible(!text.isEmpty());
		button.setButtonText(text);
	};

	for (size_t i = 0; i < std::size(lowerNotes); ++i)
	{
		if (i < parsedRegisters.size())
		{
			const auto &[lowerNote, higherNote, description] = parsedRegisters[i];

			configureButton(*lowerNotes[i], lowerNote);
			configureButton(*higherNotes[i], higherNote);
			configureEditor(*qualitiesTexts[i], description);
		}
		else
		{
			lowerNotes[i]->setVisible(false);
			higherNotes[i]->setVisible(false);
			qualitiesTexts[i]->setVisible(false);
		}
	}
}
