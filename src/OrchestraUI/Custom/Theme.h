/*
  ==============================================================================
	Module			Theme
	Description		The single source of truth for every design token
  ==============================================================================
*/

#pragma once

#include <array>

#include "JuceIncludes.h"
#include "Parameters.h"


namespace Space
{
constexpr int xs   = 4;
constexpr int s	   = 8;
constexpr int m	   = 12;
constexpr int l	   = 16;
constexpr int xl   = 24;
constexpr int xxl  = 32;
constexpr int huge = 48;
} // namespace Space


namespace Radius
{
constexpr float sm = 4.0f;	// pills
constexpr float md = 6.0f;	// controls
constexpr float lg = 8.0f;	// inner cards
constexpr float xl = 10.0f; // panels
} // namespace Radius


namespace Type
{
constexpr float display	  = 38.0f; // instrument name
constexpr float title	  = 30.0f; // view titles ("Choose a family")
constexpr float heading	  = 22.0f; // card titles, note names
constexpr float body	  = 19.0f; // primary reading text
constexpr float bodySmall = 17.0f; // secondary reading text, breadcrumb, tabs
constexpr float label	  = 15.0f; // uppercase eyebrows, pills, composer line
constexpr float caption	  = 14.0f; // dense readouts
constexpr float micro	  = 13.0f; // absolute floor
} // namespace Type


namespace Chrome
{
constexpr int toolbarH	  = 68; // family switcher toolbar
constexpr int breadcrumbH = 56;
constexpr int tabBarH	  = 52;
constexpr int sidebarRowH = 56;
constexpr int pianoRollH  = 218;
} // namespace Chrome



struct Theme
{
	// Surfaces
	juce::Colour				background;		 // #12101A main / panel
	juce::Colour				surface;		 // #1B1726 card / tile
	juce::Colour				surfaceElevated; // #241F33 selected / hover
	juce::Colour				toolbar;		 // #181520 toolbar / tab bar
	juce::Colour				pianoWell;		 // #0A090E piano-roll well

	// Accent
	juce::Colour				accent;	   // #C4943A
	juce::Colour				accentDim; // #8A6828

	// Text
	juce::Colour				textPrimary;   // #EEE9DA
	juce::Colour				textSecondary; // #9E9A8E
	juce::Colour				textTertiary;  // #6B6760

	// Interactive
	juce::Colour				tabInactive;	 // #3A3650
	juce::Colour				sidebarHover;	 // #232040
	juce::Colour				sidebarSelected; // #2A2445

	std::array<juce::Colour, 4> registerBase;

	juce::Colour				divider(float alpha = 0.14f) const { return accent.withAlpha(alpha); }
	juce::Colour				outline(float alpha = 0.30f) const { return accent.withAlpha(alpha); }

	juce::Colour				registerSwatch(int index) const;
	juce::Colour				whiteKeyForRegister(int index) const;
	juce::Colour				blackKeyForRegister(int index) const;

	juce::Colour				familyBadgeBackground(Family family) const;
	juce::Colour				familyGlyph(Family family) const;

	juce::Colour				ccLaneFill(int laneIndex) const;
};


namespace Keys
{
inline const juce::Colour whiteInRange	  = juce::Colour::fromRGB(242, 237, 226); // warm ivory
inline const juce::Colour whiteOutOfRange = juce::Colour::fromRGB(110, 106, 98);  // firmly dimmed
inline const juce::Colour blackInRange	  = juce::Colour::fromRGB(20, 17, 24);
inline const juce::Colour blackOutOfRange = juce::Colour::fromRGB(42, 39, 48);	  // lighter, so contrast inverts

constexpr float			  whiteTint		  = 0.32f;								  // register blend into whiteInRange
constexpr float			  blackBrightness = 0.28f;								  // HSB brightness for a tinted black key
constexpr float			  blackSaturation = 0.85f;
} // namespace Keys


const Theme &defaultTheme();

const Theme &themeFor(const juce::Component &component);
