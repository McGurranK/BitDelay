#pragma once

#include "PluginProcessor.h"
#include "BitDelaySliderGroup.h"

class BitLookAndFeel final : public juce::LookAndFeel_V4 {
    public:
    void drawRotarySlider(juce::Graphics & GraphicsRef, int x, int y, int width, int height
                        , float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle
                        , juce::Slider &SliderRef) override
    {
        juce::LookAndFeel_V4::drawRotarySlider (GraphicsRef, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, SliderRef);
        GraphicsRef.setColour (juce::Colours::red);
        GraphicsRef.drawText (SliderRef.getTextFromValue(SliderRef.getValue()), x, y,width, height, juce::Justification::centredTop);
        GraphicsRef.drawText (SliderRef.getName(), x, y,width, height, juce::Justification::centred);
    }
};

class BitDelayEditor final : public juce::AudioProcessorEditor
{
public:
    explicit BitDelayEditor (BitDelayAudioProcessor&);
    ~BitDelayEditor() override = default;

private:
    void paint (juce::Graphics&) override;
    void resized() override;

    BitLookAndFeel bitLookAndFeel;

    BitDelayAudioProcessor& processorRef;
    BitDelaySlidersGroup bitDelaySlidersGroup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitDelayEditor)
};
