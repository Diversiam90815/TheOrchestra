/*
  ==============================================================================
	Module			Theme
	Description		The single source of truth for every design token.
  ==============================================================================
*/

#include "Theme.h"
#include "CustomLookAndFeel.h"


juce::Colour Theme::registerSwatch(int index) const
{
	if (index < 0 || index >= (int)registerBase.size())
		return textTertiary;

	// Lifted off the base so the dot reads against the dark surface it sits on.
	return registerBase[(size_t)index].brighter(0.25f);
}


juce::Colour Theme::whiteKeyForRegister(int index) const
{
	if (index < 0 || index >= (int)registerBase.size())
		return Keys::whiteInRange;

	return Keys::whiteInRange.interpolatedWith(registerBase[(size_t)index], Keys::whiteTint);
}


juce::Colour Theme::blackKeyForRegister(int index) const
{
	if (index < 0 || index >= (int)registerBase.size())
		return Keys::blackInRange;

	// A dark, saturated version of the register colour. Drawn opaquely - the
	// previous design alpha-blended this onto black, which erased it entirely.
	return registerBase[(size_t)index].withBrightness(Keys::blackBrightness).withSaturation(Keys::blackSaturation);
}


juce::Colour Theme::familyBadgeBackground(Family family) const
{
	switch (family)
	{
	case Family::Woodwinds:	 return registerBase[0].withAlpha(0.28f);
	case Family::Brass:		 return registerBase[1].withAlpha(0.30f);
	case Family::Strings:	 return accent.withAlpha(0.24f);
	case Family::Percussion: return registerBase[3].withAlpha(0.30f);
	default:				 return surfaceElevated;
	}
}


juce::Colour Theme::familyGlyph(Family family) const
{
	switch (family)
	{
	case Family::Woodwinds:	 return registerBase[0].brighter(0.85f);
	case Family::Brass:		 return registerBase[1].brighter(0.55f);
	case Family::Strings:	 return accent;
	case Family::Percussion: return registerBase[3].brighter(0.75f);
	default:				 return textSecondary;
	}
}


juce::Colour Theme::ccLaneFill(int laneIndex) const
{
	// Lane 0 (MOD) borrows the first register blue, lane 1 (EXPR) the accent.
	return (laneIndex % 2 == 0) ? registerBase[0].brighter(0.35f) : accent;
}


const Theme &defaultTheme()
{
	static const Theme theme = []
	{
		Theme t;

		t.background	  = juce::Colour::fromRGB(18, 16, 26);	 // #12101A
		t.surface		  = juce::Colour::fromRGB(27, 23, 38);	 // #1B1726
		t.surfaceElevated = juce::Colour::fromRGB(36, 31, 51);	 // #241F33
		t.toolbar		  = juce::Colour::fromRGB(24, 21, 32);	 // #181520
		t.pianoWell		  = juce::Colour::fromRGB(10, 9, 14);	 // #0A090E

		// Brightened from the original design pass - the muted text read as too
		// low-contrast against the near-black background, especially textTertiary.
		t.accent		  = juce::Colour::fromRGB(214, 164, 68);	// #D6A444, was #C4943A
		t.accentDim		  = juce::Colour::fromRGB(138, 104, 40); // #8A6828

		t.textPrimary	  = juce::Colour::fromRGB(245, 242, 233); // #F5F2E9, was #EEE9DA
		t.textSecondary	  = juce::Colour::fromRGB(184, 180, 168); // #B8B4A8, was #9E9A8E
		t.textTertiary	  = juce::Colour::fromRGB(140, 135, 125);	 // #8C877D, was #6B6760

		t.tabInactive	  = juce::Colour::fromRGB(58, 54, 80);	// #3A3650
		t.sidebarHover	  = juce::Colour::fromRGB(35, 32, 64);	// #232040
		t.sidebarSelected = juce::Colour::fromRGB(42, 36, 69);	// #2A2445

		t.registerBase	  = { juce::Colour::fromRGB(42, 75, 140),  // #2A4B8C blue
							  juce::Colour::fromRGB(176, 120, 24), // #B07818 gold
							  juce::Colour::fromRGB(42, 107, 30),  // #2A6B1E green
							  juce::Colour::fromRGB(140, 42, 43) };// #8C2A2B red

		return t;
	}();

	return theme;
}


const Theme &themeFor(const juce::Component &component)
{
	if (auto *lf = dynamic_cast<CustomLookAndFeel *>(&component.getLookAndFeel()))
		return lf->getTheme();

	return defaultTheme();
}
