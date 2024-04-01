/*
  ==============================================================================

    InstrumentInfo.cpp
    Created: 1 Apr 2024 3:50:07pm
    Author:  jerry

  ==============================================================================
*/

#include "InstrumentInfo.h"


InstrumentInfoView::InstrumentInfoView()
{

}


InstrumentInfoView::~InstrumentInfoView()
{

}


void InstrumentInfoView::displayTextBoxes()
{

}


void InstrumentInfoView::displayInstrument(int family, int instrument)
{
    switch (family)
    {
    case (Family::Default):
    {
        mCurrentFamily = Family::Default;
        mCurrentSelectedInstrument = defaultInstrument;
        break;
    }

    case (Family::Strings):
    {
        mCurrentFamily = Family::Strings;
        
        break;
    }

    case (Family::Brass):
    {
        mCurrentFamily = Family::Brass;
        break;
    }

    case (Family::Woodwinds):
    {
        mCurrentFamily = Family::Woodwinds;
        break;
    }

    case (Family::Percussion):
    {
        mCurrentFamily = Family::Percussion;
        break;
    }

    default: break;
    }
}


void InstrumentInfoView::showStringsInstrument(int instrument)
{
    switch (instrument)
    {
    
    case (Strings::Violin):
    {
        break;
    }

    case (Strings::Viola):
    {
        break;
    }

    case (Strings::Violoncello):
    {
        break;
    }

    case (Strings::Contrabass):
    {
        break;
    }

    default: break;

    }
}


void InstrumentInfoView::showBrassInstrument(int instrument)
{
    switch (instrument)
    {

    case (Brass::FrenchHorn):
    {
        break;
    }

    case (Brass::Trumpet):
    {
        break;
    }

    case (Brass::TenorTrombone):
    {
        break;
    }

    case (Brass::BassTrombone):
    {
        break;
    }

    case (Brass::Cimbasso):
    {
        break;
    }

    case (Brass::Tuba):
    {
        break;
    }

    default: break;

    }
}


void InstrumentInfoView::showPercussionInstrument(int instrument)
{
    switch (instrument)
    {

    case (Percussion::Harp):
    {
        break;
    }

    case (Percussion::Celeste):
    {
        break;
    }

    case (Percussion::Timpani):
    {
        break;
    }

    case (Percussion::Marimba):
    {
        break;
    }

    default: break;

    }
}


void InstrumentInfoView::showWoodwindInstrument(int instrument)
{
    switch (instrument)
    {

    case (Woodwinds::Piccolo):
    {
        break;
    }

    case (Woodwinds::Flute):
    {
        break;
    }

    case (Woodwinds::Oboe):
    {
        break;
    }

    case (Woodwinds::CorAnglais):
    {
        break;
    }   
    
    case (Woodwinds::Clarinet):
    {
        break;
    }    
    
    case (Woodwinds::BassClarinet):
    {
        break;
    }

    case (Woodwinds::Basson):
    {
        break;
    }

    case (Woodwinds::Contrabassoon):
    {
        break;
    }

    default: break;

    }
}
