/*
  ==============================================================================
	Module			MidiCcGutter
	Description		Vertical MIDI-CC sliders shown beside the piano roll.
  ==============================================================================
*/

#include "MidiCcGutter.h"
#include "CustomLookAndFeel.h"


// A single vertical CC slider
class MidiCcGutter::CcSlider : public juce::Component
{
public:
	explicit CcSlider(const CcLane &lane) : mLane(lane) {}

	std::function<void(int ccNumber, int value)> onChanged;

	int	 getValue() const { return mValue; }

	void setValueExternally(int newValue)
	{
		newValue = juce::jlimit(0, 127, newValue);
		if (newValue != mValue)
		{
			mValue = newValue;
			repaint();
		}
	}

	bool isDragging() const { return mDragging; }

	void mouseDown(const juce::MouseEvent &e) override
	{
		mDragging = true;
		updateFromMouse(e);
	}

	void mouseDrag(const juce::MouseEvent &e) override { updateFromMouse(e); }

	void mouseUp(const juce::MouseEvent &) override { mDragging = false; }

	void paint(juce::Graphics &g) override
	{
		auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

		const juce::Colour trackBg	= lf ? lf->getCardColour() : juce::Colour::fromRGB(27, 23, 38);
		const juce::Colour border	= lf ? lf->getDividerColour(0.14f) : juce::Colour::fromRGB(196, 148, 58).withAlpha(0.14f);
		const juce::Colour textMuted = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);

		auto track = getTrackBounds();

		// Value readout
		g.setColour(textMuted);
		g.setFont(lf ? lf->getSerifFont(9.5f) : juce::Font(9.5f));
		g.drawText(juce::String(mValue), juce::Rectangle<int>(0, 0, getWidth(), kReadoutH), juce::Justification::centred, false);

		// Track
		g.setColour(trackBg);
		g.fillRoundedRectangle(track, 8.0f);

		// Fill (anchored to bottom)
		const float fillFraction = (float)mValue / 127.0f;
		const float fillH		 = track.getHeight() * fillFraction;
		if (fillH > 0.0f)
		{
			juce::Rectangle<float> fill(track.getX(), track.getBottom() - fillH, track.getWidth(), fillH);
			g.setColour(mLane.fill);
			g.fillRoundedRectangle(fill, 8.0f);
		}

		// Border
		g.setColour(border);
		g.drawRoundedRectangle(track, 8.0f, 1.0f);

		// Label
		g.setColour(textMuted);
		g.setFont(lf ? lf->getSerifFont(8.5f, true) : juce::Font(8.5f));
		g.drawText(mLane.label, juce::Rectangle<int>(0, getHeight() - kLabelH, getWidth(), kLabelH), juce::Justification::centred, false);
	}

private:
	juce::Rectangle<float> getTrackBounds() const
	{
		const float trackW = 16.0f;
		const float x	   = (getWidth() - trackW) * 0.5f;
		const float top	   = (float)kReadoutH + 2.0f;
		const float bottom = (float)(getHeight() - kLabelH) - 2.0f;
		return juce::Rectangle<float>(x, top, trackW, juce::jmax(1.0f, bottom - top));
	}

	void updateFromMouse(const juce::MouseEvent &e)
	{
		auto		track	 = getTrackBounds();
		const float y		 = juce::jlimit(track.getY(), track.getBottom(), (float)e.position.y);
		const float fraction = 1.0f - (y - track.getY()) / track.getHeight();
		const int	newValue = juce::jlimit(0, 127, juce::roundToInt(fraction * 127.0f));

		if (newValue != mValue)
		{
			mValue = newValue;
			repaint();
			if (onChanged)
				onChanged(mLane.ccNumber, mValue);
		}
	}

	CcLane mLane;
	int	   mValue	 = 0;
	bool   mDragging = false;

	static constexpr int kReadoutH = 14;
	static constexpr int kLabelH   = 12;
};



MidiCcGutter::MidiCcGutter(std::vector<CcLane> lanes) : mLanes(std::move(lanes))
{
	for (const auto &lane : mLanes)
	{
		auto slider		  = std::make_unique<CcSlider>(lane);
		slider->onChanged = [this](int cc, int value)
		{
			if (onCcChanged)
				onCcChanged(cc, value);
		};
		addAndMakeVisible(*slider);
		mSliders.push_back(std::move(slider));
	}

	startTimerHz(30);
}


MidiCcGutter::~MidiCcGutter()
{
	stopTimer();
}


int MidiCcGutter::getPreferredWidth() const
{
	const int count = (int)mSliders.size();
	if (count <= 0)
		return 0;
	return count * kColumnWidth + (count - 1) * kColumnGap;
}


void MidiCcGutter::resized()
{
	int x = 0;
	for (auto &slider : mSliders)
	{
		slider->setBounds(x, 0, kColumnWidth, getHeight());
		x += kColumnWidth + kColumnGap;
	}
}


void MidiCcGutter::timerCallback()
{
	if (!ccValueProvider)
		return;

	for (size_t i = 0; i < mSliders.size(); ++i)
	{
		if (mSliders[i]->isDragging())
			continue;

		const int latest = ccValueProvider(mLanes[i].ccNumber);
		if (latest >= 0)
			mSliders[i]->setValueExternally(latest);
	}
}
