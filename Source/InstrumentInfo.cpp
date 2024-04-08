/*
  ==============================================================================

    InstrumentInfo.cpp
    Created: 1 Apr 2024 3:50:07pm
    Author:  jerry

  ==============================================================================
*/

#include "InstrumentInfo.h"

InstrumentInfo::InstrumentInfo(const juce::String& name, const juce::String& range, const juce::StringArray& qualities, const juce::StringArray& roles, const juce::StringArray& famousWorks, const juce::String& transposition)
    : name(name), range(range), qualities(qualities), roles(roles), famousWorks(famousWorks), transposition(transposition)
{
}

InstrumentInfo::InstrumentInfo()
{}

InstrumentInfo::~InstrumentInfo()
{

}

