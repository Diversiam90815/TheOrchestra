
#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor(OrchestraProcessor &proc)
	: AudioProcessorEditor(&proc), audioProcessor(proc), mPianoRollView(), mInstrumentInfoView(*mPianoRollView.mPianoRoll.get(), audioProcessor.mOrchestraSampler)
{
	showUI();
	setLookAndFeel(&mCustomLookAndFeel);
}


OrchestraEditor::~OrchestraEditor()
{
	setLookAndFeel(nullptr);
}


void OrchestraEditor::showUI()
{
	addAndMakeVisible(mInstrumentInfoView);
	addAndMakeVisible(mPianoRollView);

	mMenuBar.setModel(&mInstrumentInfoView);
	addAndMakeVisible(mMenuBar);

	setSize(1200, 1000);
	//setSize(500,400);
}


void OrchestraEditor::paint(Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}


void OrchestraEditor::resized()
{
	mPianoRollView.setBoundsRelative(0.0f, 0.9f, 1.0f, 0.1f);
	mInstrumentInfoView.setBoundsRelative(0.01f, 0.05f, 0.98f, 0.8f);
	mMenuBar.setBounds(getLocalBounds().removeFromTop(mCustomLookAndFeel.getDefaultMenuBarHeight()));
}
