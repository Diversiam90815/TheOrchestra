/*
  ==============================================================================
	Module			Theme
	Description		The single source of truth for every design token: spacing,
					radii, type sizes and colours.

					Components reach the palette through themeFor(*this) rather
					than dynamic_cast-ing the LookAndFeel and carrying their own
					hardcoded fallback hex, so the palette exists exactly once.
  ==============================================================================
*/

#pragma once

#include <array>

#include "JuceIncludes.h"
#include "Parameters.h"


// 4px base spacing scale. Every gap, pad and inset comes from here.
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


// Type scale. Nothing in the UI may use a size outside this list, and nothing
// may go below Type::micro - the previous design drifted down to 8.5px.
namespace Type
{
constexpr float display	  = 34.0f; // instrument name
constexpr float title	  = 24.0f; // view titles ("Choose a family")
constexpr float heading	  = 19.0f; // card titles, note names
constexpr float body	  = 16.0f; // primary reading text
constexpr float bodySmall = 14.0f; // secondary reading text, breadcrumb, tabs
constexpr float label	  = 13.0f; // uppercase eyebrows, pills, composer line
constexpr float caption	  = 12.0f; // dense readouts
constexpr float micro	  = 11.0f; // absolute floor
} // namespace Type


// Fixed chrome heights. Bars stay fixed; everything between them is intrinsic.
namespace Chrome
{
constexpr int toolbarH	  = 64; // family switcher toolbar
constexpr int breadcrumbH = 52;
constexpr int tabBarH	  = 48;
constexpr int sidebarRowH = 52;
} // namespace Chrome


/*
 @brief					Resolved design tokens. Held by CustomLookAndFeel and
						reached via themeFor(); never constructed per-component.
*/
struct Theme
{
	// Surfaces
	juce::Colour				background;		 // #12101A main / panel
	juce::Colour				surface;		 // #1B1726 card / tile
	juce::Colour				surfaceElevated; // #241F33 selected / hover
	juce::Colour				toolbar;		 // #181520 toolbar / tab bar
	juce::Colour				pianoWell;		 // #0A090E piano-roll well

	// Accent
	juce::Colour				accent;			 // #C4943A
	juce::Colour				accentDim;		 // #8A6828

	// Text
	juce::Colour				textPrimary;	 // #EEE9DA
	juce::Colour				textSecondary;	 // #9E9A8E
	juce::Colour				textTertiary;	 // #6B6760

	// Interactive
	juce::Colour				tabInactive;	 // #3A3650
	juce::Colour				sidebarHover;	 // #232040
	juce::Colour				sidebarSelected; // #2A2445

	// Register / quality bands, at full saturation. All register-derived
	// colours come from here so the legend, the swatches and the piano roll
	// finally agree.
	std::array<juce::Colour, 4> registerBase;

	juce::Colour				divider(float alpha = 0.14f) const { return accent.withAlpha(alpha); }
	juce::Colour				outline(float alpha = 0.30f) const { return accent.withAlpha(alpha); }

	/*
	 @brief					Swatch / legend colour for a register index. Sits on
							a dark surface, so it is lifted for contrast.
	*/
	juce::Colour				registerSwatch(int index) const;

	/*
	 @brief					Tint applied to an in-range white key for a register.
	*/
	juce::Colour				whiteKeyForRegister(int index) const;

	/*
	 @brief					Fill for an in-range black key for a register. Drawn
							opaquely - never alpha-blended onto black.
	*/
	juce::Colour				blackKeyForRegister(int index) const;

	juce::Colour				familyBadgeBackground(Family family) const;
	juce::Colour				familyGlyph(Family family) const;

	/*
	 @brief					Fill colour for a MIDI-CC lane, by lane index.
	*/
	juce::Colour				ccLaneFill(int laneIndex) const;
};


// Piano-key base colours. In-range keys keep their natural colour and pick up a
// register tint; out-of-range keys are pushed hard away from them so the
// playable span reads as one solid block.
namespace Keys
{
inline const juce::Colour whiteInRange	  = juce::Colour::fromRGB(242, 237, 226); // warm ivory
inline const juce::Colour whiteOutOfRange = juce::Colour::fromRGB(110, 106, 98);	 // firmly dimmed
inline const juce::Colour blackInRange	  = juce::Colour::fromRGB(20, 17, 24);
inline const juce::Colour blackOutOfRange = juce::Colour::fromRGB(42, 39, 48);	 // lighter, so contrast inverts

constexpr float			  whiteTint		  = 0.32f; // register blend into whiteInRange
constexpr float			  blackBrightness = 0.28f; // HSB brightness for a tinted black key
constexpr float			  blackSaturation = 0.85f;
} // namespace Keys


/*
 @brief					The process-wide token set. Used directly when a
						component is not (yet) parented under a CustomLookAndFeel.
*/
const Theme &defaultTheme();

/*
 @brief					Tokens for a component, resolved through its LookAndFeel.
 @param					[IN] component asking for the tokens.
 @return				The owning CustomLookAndFeel's theme, or defaultTheme().
*/
const Theme &themeFor(const juce::Component &component);
