/*
  ==============================================================================
	Module			PianoRollWithCc
	Description		Layout container that places the PianoRoll next to a MIDI-CC gutter
  ==============================================================================
*/

#include "PianoRollWithCc.h"
#include "CustomLookAndFeel.h"
#include "TextMeasure.h"


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
	mPianoRoll.displayInstrument(instrument);

	// Build the register legend (swatch colour + start-note name) from real data.
	mLegend.clear();

	const auto &t		  = themeFor(*this);
	const auto &registers = instrument.getRegisters();

	for (size_t i = 0; i < registers.size() && i < 4; ++i)
	{
		LegendEntry entry;
		entry.colour = t.registerSwatch((int)i);
		entry.note	 = juce::String(registers[i].getWrittenLowNote());
		mLegend.push_back(entry);
	}

	repaint();
}


void PianoRollWithCc::setCcCallbacks(std::function<void(int, int)> onSend, std::function<int(int)> provider)
{
	mCcGutter.onCcChanged	  = std::move(onSend);
	mCcGutter.ccValueProvider = std::move(provider);
}


void PianoRollWithCc::paint(juce::Graphics &g)
{
	auto	   *lf	   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t	   = themeFor(*this);

	auto		header = juce::Rectangle<int>(0, 0, getWidth(), kHeaderH);

	// "PIANO ROLL" section label (left)
	g.setColour(t.textTertiary);
	g.setFont(lf ? lf->getSerifFont(Type::label, true) : juce::Font(Type::label));
	g.drawText("PIANO ROLL", header, juce::Justification::centredLeft, false);

	// Register legend (right): swatch + start-note, right-aligned.
	if (!mLegend.empty())
	{
		const auto font = lf ? lf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall);
		g.setFont(font);

		const int swatch  = 10;
		const int gap	  = Space::s;
		const int itemGap = Space::l;
		const int textPad = Space::xs;

		// Measure total width, then lay out from the right edge.
		int		  totalW  = 0;
		for (const auto &e : mLegend)
			totalW += swatch + gap + TextMeasure::lineWidth(font, e.note) + itemGap;
		totalW -= itemGap;

		int x = getWidth() - totalW;
		int y = header.getCentreY();

		for (const auto &e : mLegend)
		{
			g.setColour(e.colour);
			g.fillRoundedRectangle((float)x, (float)(y - swatch / 2), (float)swatch, (float)swatch, 2.0f);
			x += swatch + gap;

			g.setColour(t.textTertiary);
			const int tw = TextMeasure::lineWidth(font, e.note);
			g.drawText(e.note, juce::Rectangle<int>(x, 0, tw + textPad, kHeaderH), juce::Justification::centredLeft, false);
			x += tw + itemGap;
		}
	}
}


void PianoRollWithCc::resized()
{
	auto	  body	  = getLocalBounds().withTrimmedTop(kHeaderH);

	const int gutterW = mCcGutter.getPreferredWidth();

	mCcGutter.setBounds(body.getX(), body.getY(), gutterW, body.getHeight());
	mPianoRoll.setBounds(body.getX() + gutterW + kGutterGap, body.getY(), body.getWidth() - gutterW - kGutterGap, body.getHeight());
}
