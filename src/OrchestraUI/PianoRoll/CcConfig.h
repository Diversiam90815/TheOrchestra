/*
  ==============================================================================
	Module			CcConfig
	Description		Assignable MIDI-CC lane configuration for the piano-roll gutter.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include <vector>


struct CcLane
{
	int			 ccNumber;	// MIDI controller number (0..127)
	juce::String label;		// short label shown under the slider (e.g. "MOD")
	juce::Colour fill;		// slider fill colour
};


// Default lanes: CC1 (mod wheel / dynamics) and CC11 (expression).
// Colours follow the design: MOD = register-1 blue (#3D5EA5), EXPR = gold (#C4943A).
inline std::vector<CcLane> getDefaultCcLanes()
{
	return {
		{ 1,  "MOD",  juce::Colour::fromRGB(61, 94, 165) },
		{ 11, "EXPR", juce::Colour::fromRGB(196, 148, 58) },
	};
}
