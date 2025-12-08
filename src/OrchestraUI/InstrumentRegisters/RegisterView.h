/*
  ==============================================================================
	Module			RegisterView
	Description		View box containing the qualities of the different ranges of the instrument
  ==============================================================================
*/

#pragma once
#include "CustomComponent.h"


class RegisterView : public CustomComponent
{
public:
	RegisterView()	= default;
	~RegisterView() = default;

	void init() override;
	void displayInstrument(InstrumentProfile &instrument) override;

private:
	juce::Label		 mTitle;

	juce::TextButton mFirstLowerNote;
	juce::TextButton mFirstHigherNote;
	juce::TextEditor mFirstRegister;

	juce::TextButton mSecondLowerNote;
	juce::TextButton mSecondHigherNote;
	juce::TextEditor mSecondRegister;

	juce::TextButton mThirdLowerNote;
	juce::TextButton mThirdHigherNote;
	juce::TextEditor mThirdRegister;

	juce::TextButton mFourthLowerNote;
	juce::TextButton mFourthHigherNote;
	juce::TextEditor mFourthRegister;

	const int		 mRegisterTitleX		   = 79;
	const int		 mRegisterTitleY		   = 15;
	const int		 mRegisterTitleWidth	   = 110;
	const int		 mRegisterTitleHeight	   = 33;

	const int		 mNoteButtonWidth		   = 36;
	const int		 mNoteButtonHeight		   = 31;

	const int		 mRegisterWidth			   = 151;
	const int		 mRegisterHeight		   = 48;

	const int		 mFirstRowY				   = 67;
	const int		 mSecondRowY			   = 126;
	const int		 mThirdRowY				   = 185;
	const int		 mFourthRowY			   = 244;

	const int		 mRegisterX				   = 100;
	const int		 mLowerNoteX			   = 13;
	const int		 mHigherNoteX			   = 49;

	const int		 mNotesBackgroundBoxWidth  = 72;
	const int		 mNotesBackgroundBoxHeight = 31;

	const int		 mWidth					   = 269;
	const int		 mHeight				   = 305;
};
