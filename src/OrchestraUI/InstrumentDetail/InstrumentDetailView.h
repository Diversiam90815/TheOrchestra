/*
  ==============================================================================
	Module			InstrumentDetailView
	Description		The view collection of the instruments information including the piano roll
  ==============================================================================
*/

#pragma once

#include <functional>

#include "JuceIncludes.h"
#include "InstrumentSidebar.h"
#include "InstrumentHeaderPanel.h"
#include "SamplerPanel.h"
#include "TabBar.h"
#include "OverviewPanel.h"
#include "TechniquesPanel.h"
#include "RolesPanel.h"
#include "FamousWorksPanel.h"
#include "PianoRollWithCc.h"


// Small breadcrumb toolbar: "< Families"  |  Family / Instrument
class BreadcrumbBar : public juce::Component
{
public:
	BreadcrumbBar() = default;

	std::function<void()> onBack;

	void setPath(const juce::String &family, const juce::String &instrument);

	void paint(juce::Graphics &g) override;
	void mouseUp(const juce::MouseEvent &e) override;

private:
	juce::String		 mFamily;
	juce::String		 mInstrument;
	juce::Rectangle<int> mBackBounds;
};


class InstrumentDetailView : public juce::Component
{
public:
	InstrumentDetailView();
	~InstrumentDetailView() override = default;

	// Population (driven by the editor / CoreManager)
	void setFamily(Family family, const std::vector<std::pair<InstrumentID, std::string>> &instruments);
	void setInstrument(const InstrumentProfile &instrument);
	void setAvailableArticulations(std::set<Articulation> available);

	// Navigation / action callbacks (wired by the editor)
	void setInstrumentSelectedCallback(InstrumentSelectedCallback cb);
	void setBackToFamiliesCallback(std::function<void()> cb);
	void setArticulationChangedCallback(ArticulationChangedCallback cb);

	// Piano roll wiring
	void	   initPianoRoll(juce::MidiKeyboardState &state);
	void	   setPianoRollCcCallbacks(std::function<void(int, int)> onSend, std::function<int(int)> provider);
	PianoRoll &getPianoRoll() { return mPianoRoll.getPianoRoll(); }

	void	   paint(juce::Graphics &g) override;
	void	   resized() override;

private:
	void showTab(DetailTab tab);

	BreadcrumbBar		  mBreadcrumb;
	InstrumentSidebar	  mSidebar;
	InstrumentHeaderPanel mHeader;
	SamplerPanel		  mSampler;
	TabBar				  mTabBar;

	// Tab bodies (only one visible at a time)
	OverviewPanel		  mOverview;
	TechniquesPanel		  mTechniques;
	RolesPanel			  mRoles;
	FamousWorksPanel	  mFamousWorks;

	PianoRollWithCc		  mPianoRoll;

	Family				  mCurrentFamily = Family::Strings;

	static constexpr int  kBreadcrumbH = 44;
	static constexpr int  kSidebarW	   = 200;
	static constexpr int  kHeaderH	   = 120;
	static constexpr int  kSamplerH	   = 96;
	static constexpr int  kTabBarH	   = 40;
	static constexpr int  kPianoH	   = 168;
	static constexpr int  kPad		   = 12;
};
