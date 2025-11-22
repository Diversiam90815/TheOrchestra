/*
  ==============================================================================
	Module			NotationComponent
	Description		JUCE Component wrapper for NotationRenderer
  ==============================================================================
*/

#include "NotationComponent.h"


NotationComponent::NotationComponent() {}


void NotationComponent::init() {}


void NotationComponent::displayInstrument(InstrumentProfile &instrument) {}


void NotationComponent::setNote(int midiNumber, Accidental accidental) {}


void NotationComponent::setNoteFromString(const std::string &noteName) {}


void NotationComponent::setClef(Clef clef) {}


void NotationComponent::autoSelectClef() {}
