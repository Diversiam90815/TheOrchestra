/*
  ==============================================================================
	Module			InstrumentDetailView
	Description		The view collection of the instruments information including the piano roll
  ==============================================================================
*/

#pragma once

#include <functional>

#include "JuceIncludes.h"
#include "Theme.h"
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

	void				  setPath(const juce::String &family, const juce::String &instrument);

	void				  paint(juce::Graphics &g) override;
	void				  resized() override;
	void				  mouseUp(const juce::MouseEvent &e) override;

private:
	// Computed in resized()/setPath(), not paint() - mouseUp() reads mBackBounds
	// and would otherwise hit-test a rect that only existed after a repaint.
	void				 layout();

	juce::String		 mFamily;
	juce::String		 mInstrument;
	juce::Rectangle<int> mBackBounds;
	int					 mDividerX = 0;
	int					 mPathX	   = 0;
};


class InstrumentDetailView : public juce::Component
{
public:
	InstrumentDetailView();
	~InstrumentDetailView() override = default;

	// Population (driven by the editor / CoreManager)
	void	   setFamily(Family family, const std::vector<std::pair<InstrumentID, std::string>> &instruments);
	void	   setInstrument(const InstrumentProfile &instrument);
	void	   setAvailableArticulations(std::set<Articulation> available);

	// Navigation / action callbacks (wired by the editor)
	void	   setInstrumentSelectedCallback(InstrumentSelectedCallback cb);
	void	   setBackToFamiliesCallback(std::function<void()> cb);
	void	   setArticulationChangedCallback(ArticulationChangedCallback cb);

	// Piano roll wiring
	void	   initPianoRoll(juce::MidiKeyboardState &state);
	void	   setPianoRollCcCallbacks(std::function<void(int, int)> onSend, std::function<int(int)> provider);
	PianoRoll &getPianoRoll() { return mPianoRoll.getPianoRoll(); }

	void	   paint(juce::Graphics &g) override;
	void	   resized() override;

private:
	void					   showTab(DetailTab tab);

	/*
	 @brief					The currently visible tab body, as its intrinsic-height
							interface. Never null.
	*/
	const HasPreferredHeight  &activeBody() const;
	juce::Component			  &activeBodyComponent();

	BreadcrumbBar			   mBreadcrumb;
	InstrumentSidebar		   mSidebar;
	InstrumentHeaderPanel	   mHeader;
	SamplerPanel			   mSampler;
	TabBar					   mTabBar;

	// The single scroller for tab bodies. Panels report their natural height and
	// flow into mBodyHolder; nothing below owns a Viewport of its own.
	juce::Viewport			   mBodyViewport;
	juce::Component			   mBodyHolder;

	// Tab bodies (only one visible at a time), parented to mBodyHolder
	OverviewPanel			   mOverview;
	TechniquesPanel			   mTechniques;
	RolesPanel				   mRoles;
	FamousWorksPanel		   mFamousWorks;

	PianoRollWithCc			   mPianoRoll;

	Family					   mCurrentFamily = Family::Strings;
	DetailTab				   mCurrentTab	  = DetailTab::Overview;

	static constexpr int	   kMinSidebarW = 216;
	static constexpr int	   kMaxSidebarW = 280;
	static constexpr int	   kPad			= Space::l;
};
