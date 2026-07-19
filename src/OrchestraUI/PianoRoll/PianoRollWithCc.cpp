/*
  ==============================================================================
	Module			PianoRollWithCc
	Description		Layout container that places the PianoRoll next to a MIDI-CC gutter
  ==============================================================================
*/

#include "PianoRollWithCc.h"
#include "CustomLookAndFeel.h"


PianoRollWithCc::PianoRollWithCc()
{
	addAndMakeVisible(mCcGutter);
	addAndMakeVisible(mPianoRoll);
}


void PianoRollWithCc::setKeyboardState(juce::MidiKeyboardState &state)
{
	mPianoRoll.setKeyboardState(state);
}


void PianoRollWithCc::initPianoRoll()
{
	mPianoRoll.init();
}


void PianoRollWithCc::displayInstrument(const InstrumentProfile &instrument)
{
	// PianoRoll::displayInstrument takes a non-const ref; work on a copy.
	InstrumentProfile copy = instrument;
	mPianoRoll.displayInstrument(copy);

	// Build the register legend (swatch colour + start-note name) from real data.
	mLegend.clear();

	auto *lf	 = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	auto  colours = lf ? lf->getQualityColours() : std::vector<juce::Colour>{};

	const auto &registers = instrument.getRegisters();
	for (size_t i = 0; i < registers.size() && i < 4; ++i)
	{
		LegendEntry entry;
		entry.colour = (i < colours.size()) ? colours[i] : juce::Colours::grey;
		entry.note	 = juce::String(registers[i].getWrittenLowNote());
		mLegend.push_back(entry);
	}

	repaint();
}


void PianoRollWithCc::setCcCallbacks(std::function<void(int, int)> onSend, std::function<int(int)> provider)
{
	mCcGutter.onCcChanged	 = std::move(onSend);
	mCcGutter.ccValueProvider = std::move(provider);
}


void PianoRollWithCc::paint(juce::Graphics &g)
{
	auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const juce::Colour textMuted = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);

	auto header = juce::Rectangle<int>(0, 0, getWidth(), kHeaderH);

	// "PIANO ROLL" section label (left)
	g.setColour(textMuted);
	g.setFont(lf ? lf->getSerifFont(11.0f, true) : juce::Font(11.0f));
	g.drawText("PIANO ROLL", header, juce::Justification::centredLeft, false);

	// Register legend (right): swatch + start-note, right-aligned.
	if (!mLegend.empty())
	{
		g.setFont(lf ? lf->getSerifFont(11.0f) : juce::Font(11.0f));

		const int   swatch	= 8;
		const int   gap		= 5;
		const int   itemGap	= 12;
		const int   textPad	= 4;

		// Measure total width, then lay out from the right edge.
		int totalW = 0;
		for (const auto &e : mLegend)
			totalW += swatch + gap + g.getCurrentFont().getStringWidth(e.note) + itemGap;
		totalW -= itemGap;

		int x = getWidth() - totalW;
		int y = header.getCentreY();

		for (const auto &e : mLegend)
		{
			g.setColour(e.colour);
			g.fillRoundedRectangle((float)x, (float)(y - swatch / 2), (float)swatch, (float)swatch, 2.0f);
			x += swatch + gap;

			g.setColour(textMuted);
			const int tw = g.getCurrentFont().getStringWidth(e.note);
			g.drawText(e.note, juce::Rectangle<int>(x, 0, tw + textPad, kHeaderH), juce::Justification::centredLeft, false);
			x += tw + itemGap;
		}
	}
}


void PianoRollWithCc::resized()
{
	auto body = getLocalBounds().withTrimmedTop(kHeaderH);

	const int gutterW = mCcGutter.getPreferredWidth();

	mCcGutter.setBounds(body.getX(), body.getY(), gutterW, body.getHeight());
	mPianoRoll.setBounds(body.getX() + gutterW + kGutterGap, body.getY(), body.getWidth() - gutterW - kGutterGap, body.getHeight());
}
