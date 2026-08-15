/*
  ==============================================================================
	Module			CcConfig
	Description		Assignable MIDI-CC lane configuration for the piano-roll gutter.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Theme.h"

#include <vector>


struct CcLane
{
	int			 ccNumber; // MIDI controller number (0..127)
	juce::String label;	   // short label shown under the slider (e.g. "MOD")
	juce::Colour fill;	   // slider fill colour
};

inline std::vector<CcLane> getDefaultCcLanes(const Theme &theme = defaultTheme())
{
	return {
		{11, "EXPR", theme.ccLaneFill(1)},
		{1, "MOD", theme.ccLaneFill(0)},
	};
}
