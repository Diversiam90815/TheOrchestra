/*
  ==============================================================================
	Module			InstrumentDetailView
	Description		The view collection of the instruments information including the piano roll
  ==============================================================================
*/

#include "InstrumentDetailView.h"
#include "CustomLookAndFeel.h"
#include "TextMeasure.h"
#include "Helper.h"


namespace
{
const juce::String kBackLabel = juce::String::fromUTF8("\xE2\x80\xB9 Families"); // U+2039 chevron
}


//==============================================================================
// BreadcrumbBar
//==============================================================================

void BreadcrumbBar::setPath(const juce::String &family, const juce::String &instrument)
{
	mFamily		= family;
	mInstrument = instrument;
	layout();
	repaint();
}


void BreadcrumbBar::layout()
{
	auto	 *lf   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	auto	  font = lf ? lf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall);

	const int x	   = Space::xl;
	mBackBounds	   = juce::Rectangle<int>(x, 0, TextMeasure::lineWidth(font, kBackLabel) + Space::s, getHeight());
	mDividerX	   = mBackBounds.getRight() + Space::m;
	mPathX		   = mDividerX + Space::m;
}


void BreadcrumbBar::resized()
{
	layout();
}


void BreadcrumbBar::paint(juce::Graphics &g)
{
	auto	   *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t  = themeFor(*this);

	g.fillAll(t.toolbar);

	const auto font = lf ? lf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall);
	g.setFont(font);

	// Back link "< Families"
	g.setColour(t.accent);
	g.drawText(kBackLabel, mBackBounds, juce::Justification::centredLeft, false);

	// Vertical divider
	g.setColour(t.divider(0.2f));
	g.fillRect(mDividerX, getHeight() / 2 - 8, 1, 16);

	// Family / Instrument
	if (mFamily.isNotEmpty())
	{
		const juce::String famPart = mFamily + "  /  ";
		const int		   famW	   = TextMeasure::lineWidth(font, famPart);

		g.setColour(t.textTertiary);
		g.drawText(famPart, juce::Rectangle<int>(mPathX, 0, famW + Space::xs, getHeight()), juce::Justification::centredLeft, false);

		g.setColour(t.textPrimary);
		g.drawText(mInstrument, juce::Rectangle<int>(mPathX + famW, 0, getWidth() - mPathX - famW, getHeight()), juce::Justification::centredLeft, false);
	}

	// Bottom hairline
	g.setColour(t.divider(0.1f));
	g.fillRect(0, getHeight() - 1, getWidth(), 1);
}


void BreadcrumbBar::mouseUp(const juce::MouseEvent &e)
{
	if (mBackBounds.contains(e.getPosition()) && onBack)
		onBack();
}


//==============================================================================
// InstrumentDetailView
//==============================================================================

InstrumentDetailView::InstrumentDetailView()
{
	addAndMakeVisible(mBreadcrumb);
	addAndMakeVisible(mSidebar);
	addAndMakeVisible(mHeader);
	addAndMakeVisible(mSampler);
	addAndMakeVisible(mTabBar);

	// One scroller for every tab body.
	mBodyViewport.setViewedComponent(&mBodyHolder, false);
	mBodyViewport.setScrollBarsShown(true, false);
	mBodyViewport.setScrollBarThickness(Space::s);
	addAndMakeVisible(mBodyViewport);

	mBodyHolder.addChildComponent(mOverview);
	mBodyHolder.addChildComponent(mTechniques);
	mBodyHolder.addChildComponent(mRoles);
	mBodyHolder.addChildComponent(mFamousWorks);
	mOverview.setVisible(true);

	addAndMakeVisible(mPianoRoll);

	// Written/Sounding toggle from the header drives the overview (notation + qualities).
	mHeader.setPitchModeChangedCallback([this](PitchMode mode) { mOverview.setPitchMode(mode); });
	mHeader.setClefChangedCallback([this](Clef clef) { mOverview.setClef(clef); });

	// Tab switching (progressive disclosure - one body at a time).
	mTabBar.onTabChanged = [this](DetailTab tab) { showTab(tab); };
}


void InstrumentDetailView::setFamily(Family family, const std::vector<std::pair<InstrumentID, std::string>> &instruments)
{
	mCurrentFamily = family;
	mSidebar.setInstruments(instruments); // auto-selects first instrument (fires callback)
}


void InstrumentDetailView::setInstrument(const InstrumentProfile &instrument)
{
	mHeader.setInstrument(instrument);
	mOverview.setInstrument(instrument);
	mOverview.setClef(mHeader.getCurrentClef());
	mTechniques.setInstrument(instrument);
	mRoles.setInstrument(instrument);
	mFamousWorks.setInstrument(instrument);
	mPianoRoll.displayInstrument(instrument);

	mBreadcrumb.setPath(getFamilyNameFromKey(instrument.getInstrumentID()), instrument.getName());

	// Reset to the Overview tab for each new instrument.
	mTabBar.setActiveTab(DetailTab::Overview);
	showTab(DetailTab::Overview);
}


void InstrumentDetailView::setAvailableArticulations(std::set<Articulation> available)
{
	mSampler.setAvailableArticulations(std::move(available));

	resized();
}


void InstrumentDetailView::setInstrumentSelectedCallback(InstrumentSelectedCallback cb)
{
	mSidebar.setInstrumentSelectedCallback(std::move(cb));
}


void InstrumentDetailView::setBackToFamiliesCallback(std::function<void()> cb)
{
	mBreadcrumb.onBack = std::move(cb);
}


void InstrumentDetailView::setArticulationChangedCallback(ArticulationChangedCallback cb)
{
	mSampler.setArticulationChangedCallback(std::move(cb));
}


void InstrumentDetailView::initPianoRoll(juce::MidiKeyboardState &state)
{
	mPianoRoll.setKeyboardState(state);
	mPianoRoll.initPianoRoll();
}


void InstrumentDetailView::setPianoRollCcCallbacks(std::function<void(int, int)> onSend, std::function<int(int)> provider)
{
	mPianoRoll.setCcCallbacks(std::move(onSend), std::move(provider));
}


juce::Component &InstrumentDetailView::activeBodyComponent()
{
	switch (mCurrentTab)
	{
	case DetailTab::Techniques: return mTechniques;
	case DetailTab::Roles: return mRoles;
	case DetailTab::FamousWorks: return mFamousWorks;
	case DetailTab::Overview:
	default: return mOverview;
	}
}


const HasPreferredHeight &InstrumentDetailView::activeBody() const
{
	// Every tab body is both a Component and a HasPreferredHeight; resolve the
	// component once and cross-cast rather than repeating the switch.
	auto &body = const_cast<InstrumentDetailView *>(this)->activeBodyComponent();

	return dynamic_cast<const HasPreferredHeight &>(body);
}


void InstrumentDetailView::showTab(DetailTab tab)
{
	mCurrentTab = tab;

	mOverview.setVisible(tab == DetailTab::Overview);
	mTechniques.setVisible(tab == DetailTab::Techniques);
	mRoles.setVisible(tab == DetailTab::Roles);
	mFamousWorks.setVisible(tab == DetailTab::FamousWorks);

	mBodyViewport.setViewPosition(0, 0);
	resized();
}


void InstrumentDetailView::paint(juce::Graphics &g)
{
	g.fillAll(themeFor(*this).background);
}


void InstrumentDetailView::resized()
{
	auto area = getLocalBounds();

	mBreadcrumb.setBounds(area.removeFromTop(Chrome::breadcrumbH));
	mSidebar.setBounds(area.removeFromLeft(juce::jlimit(kMinSidebarW, kMaxSidebarW, juce::roundToInt(getWidth() * 0.16f))));

	// Detail column: each section takes the height it actually needs, and each
	// slot carries its own gap below so the panels never touch.
	auto	  detail	 = area;
	const int detailW	 = detail.getWidth();
	const int panelWidth = detailW - kPad * 2;

	auto	  slot		 = [&detail](int height, int gap) { return detail.removeFromTop(height + gap).withTrimmedBottom(gap); };

	mHeader.setBounds(slot(mHeader.getPreferredHeight(panelWidth), kPad).reduced(kPad, 0));
	mSampler.setBounds(slot(mSampler.getPreferredHeight(panelWidth), kPad).reduced(kPad, 0));
	mTabBar.setBounds(detail.removeFromTop(Chrome::tabBarH));

	// The piano roll is a constant height
	mPianoRoll.setBounds(detail.removeFromBottom(Chrome::pianoRollH + kPad).withTrimmedBottom(kPad).reduced(kPad + Space::s, 0));

	auto body = detail.reduced(kPad, 0);
	mBodyViewport.setBounds(body);

	// Holder is as tall as the content wants, so the viewport scrolls only when
	// the content genuinely does not fit
	const bool needsScroll	= activeBody().getPreferredHeight(body.getWidth()) > body.getHeight();
	const int  holderWidth	= body.getWidth() - (needsScroll ? Space::m : 0);
	const int  holderHeight = juce::jmax(body.getHeight(), activeBody().getPreferredHeight(holderWidth));

	mBodyHolder.setSize(holderWidth, holderHeight);
	activeBodyComponent().setBounds(mBodyHolder.getLocalBounds());
}
