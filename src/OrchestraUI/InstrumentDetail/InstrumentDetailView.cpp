/*
  ==============================================================================
	Module			InstrumentDetailView
	Description		The view collection of the instruments information including the piano roll
  ==============================================================================
*/

#include "InstrumentDetailView.h"
#include "CustomLookAndFeel.h"
#include "Helper.h"


//==============================================================================
// BreadcrumbBar
//==============================================================================

void BreadcrumbBar::setPath(const juce::String &family, const juce::String &instrument)
{
	mFamily		= family;
	mInstrument = instrument;
	repaint();
}


void BreadcrumbBar::paint(juce::Graphics &g)
{
	auto			  *lf	   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const juce::Colour barBg   = lf ? lf->getToolbarColour() : juce::Colour::fromRGB(24, 21, 32);
	const juce::Colour gold	   = lf ? lf->getAccentColour() : juce::Colour::fromRGB(196, 148, 58);
	const juce::Colour primary = lf ? lf->getTextPrimaryColour() : juce::Colour::fromRGB(238, 233, 218);
	const juce::Colour muted   = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);
	const juce::Colour divider = lf ? lf->getDividerColour(0.1f) : juce::Colour::fromRGB(196, 148, 58).withAlpha(0.1f);

	g.fillAll(barBg);

	auto	   area = getLocalBounds().reduced(22, 0);
	const auto font = lf ? lf->getSerifFont(12.5f) : juce::Font(12.5f);
	g.setFont(font);

	// Back link "< Families"
	const juce::String back	 = juce::String::fromUTF8("\xE2\x80\xB9 Families"); // U+2039 chevron
	const int		   backW = font.getStringWidth(back);
	mBackBounds				 = juce::Rectangle<int>(area.getX(), 0, backW + 6, getHeight());

	g.setColour(gold);
	g.drawText(back, mBackBounds, juce::Justification::centredLeft, false);

	int x = mBackBounds.getRight() + 12;

	// vertical divider
	g.setColour(lf ? lf->getDividerColour(0.2f) : juce::Colour::fromRGB(196, 148, 58).withAlpha(0.2f));
	g.fillRect(x, getHeight() / 2 - 7, 1, 14);
	x += 12;

	// Family / Instrument
	if (mFamily.isNotEmpty())
	{
		const juce::String famPart = mFamily + "  /  ";
		g.setColour(muted);
		g.drawText(famPart, juce::Rectangle<int>(x, 0, font.getStringWidth(famPart) + 4, getHeight()), juce::Justification::centredLeft, false);
		x += font.getStringWidth(famPart);

		g.setColour(primary);
		g.drawText(mInstrument, juce::Rectangle<int>(x, 0, getWidth() - x, getHeight()), juce::Justification::centredLeft, false);
	}

	// bottom hairline
	g.setColour(divider);
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

	addChildComponent(mOverview);
	addChildComponent(mTechniques);
	addChildComponent(mRoles);
	addChildComponent(mFamousWorks);
	mOverview.setVisible(true);

	addAndMakeVisible(mPianoRoll);

	// Written/Sounding toggle from the header drives the overview (notation + qualities).
	mHeader.setPitchModeChangedCallback([this](PitchMode mode) { mOverview.setPitchMode(mode); });

	// Tab switching (progressive disclosure - one body at a time).
	mTabBar.onTabChanged = [this](DetailTab tab) { showTab(tab); };
}


void InstrumentDetailView::setFamily(Family family, const std::vector<std::pair<InstrumentID, std::string>> &instruments)
{
	mCurrentFamily = family;
	mSidebar.setFamily(family, instruments); // auto-selects first instrument (fires callback)
}


void InstrumentDetailView::setInstrument(const InstrumentProfile &instrument)
{
	mHeader.setInstrument(instrument);
	mOverview.setInstrument(instrument);
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


void InstrumentDetailView::showTab(DetailTab tab)
{
	mOverview.setVisible(tab == DetailTab::Overview);
	mTechniques.setVisible(tab == DetailTab::Techniques);
	mRoles.setVisible(tab == DetailTab::Roles);
	mFamousWorks.setVisible(tab == DetailTab::FamousWorks);
	resized();
}


void InstrumentDetailView::paint(juce::Graphics &g)
{
	auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	g.fillAll(lf ? lf->getBackgroundColour() : juce::Colour::fromRGB(18, 16, 26));
}


void InstrumentDetailView::resized()
{
	auto area = getLocalBounds();

	mBreadcrumb.setBounds(area.removeFromTop(kBreadcrumbH));

	mSidebar.setBounds(area.removeFromLeft(kSidebarW));

	// Detail column
	auto detail = area;

	mHeader.setBounds(detail.removeFromTop(kHeaderH).reduced(kPad, kPad));
	mSampler.setBounds(detail.removeFromTop(kSamplerH).reduced(kPad, 0));
	mTabBar.setBounds(detail.removeFromTop(kTabBarH));

	auto piano = detail.removeFromBottom(kPianoH).reduced(kPad + 12, kPad);

	// Remaining space = the active tab body.
	auto body  = detail;
	mOverview.setBounds(body);
	mTechniques.setBounds(body.reduced(kPad, kPad));
	mRoles.setBounds(body.reduced(kPad, kPad));
	mFamousWorks.setBounds(body.reduced(kPad, kPad));

	mPianoRoll.setBounds(piano);
}
