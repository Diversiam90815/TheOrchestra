/*
  ==============================================================================
	Module			FamilySwitcherView
	Description		The entry screen
  ==============================================================================
*/

#include "FamilySwitcherView.h"
#include "CustomLookAndFeel.h"


FamilySwitcherView::FamilySwitcherView()
{
	struct Def
	{
		Family		family;
		const char *name;
		const char *letter;
	};

	// Badge and glyph colours come from the theme, keyed by family.
	const std::vector<Def> defs = {
		{Family::Woodwinds, "Woodwinds", "W"},
		{Family::Brass, "Brass", "B"},
		{Family::Strings, "Strings", "S"},
		{Family::Percussion, "Percussion", "P"},
	};

	for (const auto &d : defs)
	{
		auto card		= std::make_unique<FamilyCard>(d.family, d.name, d.letter);
		card->onClicked = [this](Family f)
		{
			if (onFamilySelected)
				onFamilySelected(f);
		};
		addAndMakeVisible(*card);
		mCards.push_back({d.family, std::move(card)});
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


void FamilySwitcherView::layout()
{
	const int contentW = juce::jmin(kMaxContentW, getWidth() - Space::huge * 2);
	const int cx	   = (getWidth() - contentW) / 2;

	mContentBounds	   = juce::Rectangle<int>(cx, 0, contentW, getHeight());

	// Toolbar icon, right-aligned.
	const int cyMid	   = Chrome::toolbarH / 2;
	const int cr	   = mContentBounds.getRight();
	mGearBounds		   = juce::Rectangle<int>(cr - Space::xl, cyMid - Space::m, Space::xl, Space::xl);

	// Title block, then the grid. One derivation, read by both layout and paint.
	// The block is centred in the space below the toolbar rather than pinned to
	// the top, which otherwise left the lower half of the screen empty.
	const int blockH   = kTitleH + Space::xs + kSubtitleH + Space::xl + kCardH * 2 + kGridGap;
	const int belowH   = getHeight() - Chrome::toolbarH;

	int		  y		   = Chrome::toolbarH + juce::jmax(Space::xxl, (belowH - blockH) / 2);

	mTitleBounds	   = juce::Rectangle<int>(cx, y, contentW, kTitleH);
	y += kTitleH + Space::xs;
	mSubtitleBounds = juce::Rectangle<int>(cx, y, contentW, kSubtitleH);
	y += kSubtitleH + Space::xl;

	const int cardW = (contentW - kGridGap) / 2;

	for (size_t i = 0; i < mCards.size(); ++i)
	{
		const int col = (int)i % 2;
		const int row = (int)i / 2;

		mCards[i].card->setBounds(cx + col * (cardW + kGridGap), y + row * (kCardH + kGridGap), cardW, kCardH);
	}
}


void FamilySwitcherView::paint(juce::Graphics &g)
{
	auto	   *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t  = themeFor(*this);

	g.fillAll(t.background);

	// Toolbar background (full width)
	g.setColour(t.toolbar);
	g.fillRect(0, 0, getWidth(), Chrome::toolbarH);
	g.setColour(t.divider());
	g.fillRect(0, Chrome::toolbarH - 1, getWidth(), 1);

	// Logo lockup (left): a small note glyph + wordmark
	{
		const int cx	= mContentBounds.getX();
		const int cyMid = Chrome::toolbarH / 2;
		auto	  note	= juce::Rectangle<float>((float)cx, (float)(cyMid - 9), 18.0f, 18.0f);

		g.setColour(t.accent);
		g.fillEllipse(note.getX(), note.getBottom() - 7.0f, 7.0f, 7.0f);
		g.drawLine(note.getX() + 7.0f, note.getBottom() - 3.5f, note.getX() + 7.0f, note.getY(), 1.8f);

		g.setColour(t.textPrimary);
		g.setFont(lf ? lf->getSerifFont(Type::bodySmall, true) : juce::Font(Type::bodySmall));
		g.drawText("THE ORCHESTRA", juce::Rectangle<int>(cx + Space::xxl, 0, 240, Chrome::toolbarH), juce::Justification::centredLeft, false);
	}

	// Settings gear (clickable)
	{
		auto		gb		  = mGearBounds.toFloat().reduced(4.0f);
		auto		c		  = gb.getCentre();
		const float rOut	  = gb.getWidth() * 0.5f * 0.78f;
		const float rIn		  = rOut * 0.5f;
		const float toothSize = rOut * 0.62f;
		const int	numTeeth  = 8;

		juce::Path	gear;
		gear.addEllipse(juce::Rectangle<float>(rOut * 2.0f, rOut * 2.0f).withCentre(c));

		for (int i = 0; i < numTeeth; ++i)
		{
			const float angle		= juce::MathConstants<float>::twoPi * (float)i / (float)numTeeth;
			const auto	toothCentre = c.getPointOnCircumference(rOut, angle);

			juce::Path	tooth;
			tooth.addRectangle(juce::Rectangle<float>(toothSize, toothSize).withCentre(toothCentre));
			tooth.applyTransform(juce::AffineTransform::rotation(angle, toothCentre.x, toothCentre.y));
			gear.addPath(tooth);
		}

		g.setColour(t.textTertiary);
		g.fillPath(gear);

		g.setColour(t.toolbar);
		g.fillEllipse(juce::Rectangle<float>(rIn * 2.0f, rIn * 2.0f).withCentre(c));
	}

	// Title block
	g.setColour(t.textPrimary);
	g.setFont(lf ? lf->getSerifFont(Type::title) : juce::Font(Type::title));
	g.drawText("Choose a family", mTitleBounds, juce::Justification::topLeft, false);

	g.setColour(t.textSecondary);
	g.setFont(lf ? lf->getSerifFont(Type::body) : juce::Font(Type::body));
	g.drawText("Four families, each with their own voice and range.", mSubtitleBounds, juce::Justification::topLeft, false);
}


void FamilySwitcherView::resized()
{
	layout();
}


void FamilySwitcherView::mouseUp(const juce::MouseEvent &e)
{
	if (mGearBounds.contains(e.getPosition()) && onSettings)
		onSettings();
}
