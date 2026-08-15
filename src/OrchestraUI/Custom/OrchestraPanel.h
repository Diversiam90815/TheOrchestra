/*
  ==============================================================================
	Module			OrchestraPanel
	Description		Base class for all UI panels.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "InstrumentInfo.h"
#include "Theme.h"


enum class PitchMode
{
	Written,
	Sounding
};


/*
 @brief					Implemented by anything the detail view stacks vertically.
						The view allocates height from these rather than from
						hardcoded per-section pixel constants.
*/
struct HasPreferredHeight
{
	virtual ~HasPreferredHeight() = default;

	/*
	 @brief					Height this component wants at the given width.
	 @param					[IN] width it will be laid out at - matters because
							several panels wrap their content.
	*/
	virtual int getPreferredHeight(int width) const = 0;
};


class OrchestraPanel : public juce::Component
{
public:
	explicit OrchestraPanel(const juce::String &title = "");
	~OrchestraPanel() override = default;

	void				 paint(juce::Graphics &g) override;

	virtual void		 setInstrument(const InstrumentProfile &instrument) = 0;

protected:
	juce::Rectangle<int> getContentArea() const;
	void				 setTitle(const juce::String &newTitle) { mTitle = newTitle; }

	/*
	 @brief					Vertical space this panel spends on padding and title,
							i.e. everything getPreferredHeight must add to its
							content height.
	*/
	int					 getChromeHeight() const;

	static constexpr int kPadding	  = Space::xl;
	static constexpr int kTitleHeight = 24;
	static constexpr int kTitleGap	  = Space::m;

private:
	juce::String mTitle;
};
