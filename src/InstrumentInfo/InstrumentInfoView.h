/*
  ==============================================================================

	Module			InstrumentInfoModel
	Description		Displaying the instrument's information

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "InstrumentInfoModel.h"
#include "CustomPianoRoll.h"
#include "CustomLookAndFeel.h"
#include "Sampler.h"


class InstrumentInfoView : public Component, public MenuBarModel
{
public:
	//==============================================================================
	//                          CONSTRUCTOR - DESTRUCTOR
	//==============================================================================

	InstrumentInfoView(CustomPianoRoll &piano, Sampler &sampler);

	~InstrumentInfoView();


private:
	//==============================================================================
	//                          PRIVATE METHODS
	//==============================================================================

	void								displayLabels();

	void								resized() override;

	void								showInstrumentInfo(int key);

	void								displayText(Label &label, String text);

	void								setupHeading(Label &labelToSetup, const String &title);

	StringArray							getMenuBarNames() override;

	PopupMenu							getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;

	void								menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	void								clearLabels(std::vector<std::unique_ptr<Label>> &labels);

	void								displayLabelsForCategory(const StringArray &texts, std::vector<std::unique_ptr<Label>> &labelsContainer, const int category);


	//==============================================================================
	//                          PRIVATE OBJECTS
	//==============================================================================

	int									mCurrentSelectedInstrument = defaultInstrument; // Default value out of reach of different enums

	int									mCurrentFamily;									// integer describing the current selected instrument family from the Family enum

	MenuBarComponent					menuBar;										// Menubar instance

	InstrumentInfoModel					mInstrumentModel;								// Model for our view

	Sampler							   &mOrchestraSampler;

	Label								mInstrument;			  // Label for the Instrument's name
	Label								mRangeTitle;			  // Title for the ranges
	Label								mUsefulInformationTitle;  // Title for the Useful information
	Label								mQualitiesTitle;		  // Title for the Qualities
	Label								mTranspositionTitle;	  // Title for the Transposition
	Label								mPlayingTechniquesTitle;  // Title for the Playing Techniques
	Label								mFamousWorksTitle;		  // Title for the Famous Works

	Label								mRange;					  // Label used to display the selected instrument's ranges
	Label								mTransposition;			  // Label used to display the selected instrument's transposition

	std::vector<std::unique_ptr<Label>> mQualityLabels;			  // Vector of labels displaying the qualities
	std::vector<std::unique_ptr<Label>> mPlayingTechniqueLabels;  // Vector of labels displaying the playing techniques
	std::vector<std::unique_ptr<Label>> mFamousWorksLabels;		  // Vector of labels displaying famous works
	std::vector<std::unique_ptr<Label>> mUsefulInformationLabels; // Vector of labels displaying useful information


	CustomPianoRoll					   &mCustomPianoRoll;		  // Our customized Piano Roll

	CustomLookAndFeel					mCustomLookAndFeel;		  // Customized Look&Feel
};
