/*
  ==============================================================================
	Module			FamilySwitcherView
	Description		The entry screen. Toolbar (logo + search + settings),
					a "Choose a family" title, and a 2x2 grid of family cards.
  ==============================================================================
*/

#include "FamilySwitcherView.h"
#include "CustomLookAndFeel.h"


FamilySwitcherView::FamilySwitcherView()
{
	struct Def
	{
		Family		 family;
		const char	*name;
		const char	*letter;
		juce::Colour badgeBg;
		juce::Colour glyph;
	};

	const std::vector<Def> defs = {
		{ Family::Woodwinds,  "Woodwinds",	"W", juce::Colour::fromRGB(42, 75, 140).withAlpha(0.28f),  juce::Colour::fromRGB(124, 159, 224) },
		{ Family::Brass,	  "Brass",		"B", juce::Colour::fromRGB(176, 120, 24).withAlpha(0.30f), juce::Colour::fromRGB(227, 177, 92) },
		{ Family::Strings,	  "Strings",	"S", juce::Colour::fromRGB(196, 148, 58).withAlpha(0.24f), juce::Colour::fromRGB(196, 148, 58) },
		{ Family::Percussion, "Percussion", "P", juce::Colour::fromRGB(140, 42, 43).withAlpha(0.30f),  juce::Colour::fromRGB(217, 134, 135) },
	};

	for (const auto &d : defs)
	{
		auto card		 = std::make_unique<FamilyCard>(d.family, d.name, d.letter, d.badgeBg, d.glyph);
		card->onClicked = [this](Family f)
		{
			if (onFamilySelected)
				onFamilySelected(f);
		};
		addAndMakeVisible(*card);
		mCards.push_back({ d.family, std::move(card) });
	}
}


void FamilySwitcherView::setFamilyCount(Family family, int count)
{
	for (auto &entry : mCards)
		if (entry.family == family)
			entry.card->setCount(count);
}


void FamilySwitcherView::setSelectedFamily(Family family)
{
	for (auto &entry : mCards)
		entry.card->setSelected(entry.family == family);
}


void FamilySwitcherView::paint(juce::Graphics &g)
{
	auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const juce::Colour bg		 = lf ? lf->getBackgroundColour() : juce::Colour::fromRGB(18, 16, 26);
	const juce::Colour toolbar	 = lf ? lf->getToolbarColour() : juce::Colour::fromRGB(24, 21, 32);
	const juce::Colour gold		 = lf ? lf->getAccentColour() : juce::Colour::fromRGB(196, 148, 58);
	const juce::Colour primary	 = lf ? lf->getTextPrimaryColour() : juce::Colour::fromRGB(238, 233, 218);
	const juce::Colour secondary = lf ? lf->getTextSecondaryColour() : juce::Colour::fromRGB(158, 154, 142);
	const juce::Colour muted	 = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);
	const juce::Colour divider	 = lf ? lf->getDividerColour(0.14f) : gold.withAlpha(0.14f);

	g.fillAll(bg);

	// Toolbar background (full width)
	auto toolbarArea = juce::Rectangle<int>(0, 0, getWidth(), kToolbarH);
	g.setColour(toolbar);
	g.fillRect(toolbarArea);
	g.setColour(divider);
	g.fillRect(0, kToolbarH - 1, getWidth(), 1);

	const int cx = mContentBounds.getX();
	const int cr = mContentBounds.getRight();

	// Logo lockup (left): a small note glyph + wordmark
	{
		const int   cyMid = kToolbarH / 2;
		auto		note  = juce::Rectangle<float>((float)cx, (float)(cyMid - 8), 16.0f, 16.0f);
		g.setColour(gold);

		// note head
		g.fillEllipse(note.getX(), note.getBottom() - 6.0f, 6.0f, 6.0f);

		// stem
		g.drawLine(note.getX() + 6.0f, note.getBottom() - 3.0f, note.getX() + 6.0f, note.getY(), 1.6f);

		g.setColour(primary);
		auto font = lf ? lf->getSerifFont(12.0f, true) : juce::Font(12.0f);
		g.setFont(font);
		g.drawText("THE ORCHESTRA", juce::Rectangle<int>(cx + 24, 0, 200, kToolbarH), juce::Justification::centredLeft, false);
	}

	// Right icons: search (magnifier) + settings (gear)
	{
		const int cyMid = kToolbarH / 2;

		// Settings gear (rightmost, clickable)
		mGearBounds = juce::Rectangle<int>(cr - 20, cyMid - 10, 20, 20);
		g.setColour(muted);
		auto gc = mGearBounds.toFloat().reduced(2.0f);
		g.drawEllipse(gc.reduced(3.0f), 1.4f);
		g.drawEllipse(gc.reduced(7.0f), 1.4f);

		// Search magnifier (left of gear)
		auto search = juce::Rectangle<float>((float)(cr - 52), (float)(cyMid - 8), 16.0f, 16.0f);
		g.drawEllipse(search.getX(), search.getY(), 11.0f, 11.0f, 1.6f);
		g.drawLine(search.getX() + 10.0f, search.getY() + 10.0f, search.getX() + 15.0f, search.getY() + 15.0f, 1.6f);
	}

	// Title block
	{
		auto titleY = kToolbarH + 26;
		g.setColour(primary);
		g.setFont(lf ? lf->getSerifFont(22.0f) : juce::Font(22.0f));
		g.drawText("Choose a family", juce::Rectangle<int>(cx, titleY, mContentBounds.getWidth(), 30), juce::Justification::topLeft, false);

		g.setColour(secondary);
		g.setFont(lf ? lf->getSerifFont(12.0f) : juce::Font(12.0f));
		g.drawText("Four families, each with their own voice and range.", juce::Rectangle<int>(cx, titleY + 32, mContentBounds.getWidth(), 20),
				   juce::Justification::topLeft, false);
	}
}


void FamilySwitcherView::resized()
{
	const int contentW = juce::jmin(kMaxContentW, getWidth() - 80);
	const int cx	   = (getWidth() - contentW) / 2;

	mContentBounds = juce::Rectangle<int>(cx, 0, contentW, getHeight());

	// Grid begins below the toolbar + title block.
	const int gridTop = kToolbarH + 26 + 32 + 20 + 24;

	const int cardW	  = (contentW - kGridGap) / 2;

	for (size_t i = 0; i < mCards.size(); ++i)
	{
		const int col = (int)i % 2;
		const int row = (int)i / 2;

		const int x = cx + col * (cardW + kGridGap);
		const int y = gridTop + row * (kCardH + kGridGap);

		mCards[i].card->setBounds(x, y, cardW, kCardH);
	}
}


void FamilySwitcherView::mouseUp(const juce::MouseEvent &e)
{
	if (mGearBounds.contains(e.getPosition()) && onSettings)
		onSettings();
}
