/*
  ==============================================================================

    InstrumentInfoModel.h
    Created: 8 Apr 2024 6:23:51pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <map>
#include "InstrumentInfo.h"


class InstrumentInfoModel
{
public:
    InstrumentInfoModel();
    ~InstrumentInfoModel();

    void addStringInstruments();
    void addWoodwindInstruments();
    void addBrassInstruments();
    void addPercussionInstruments();

    void addInstrument(Family family, int instrumentId, const InstrumentInfo& info);

    InstrumentInfo getInstrument(Family family, int instrumentId);

private:
    std::map<int, InstrumentInfo> instruments;

};