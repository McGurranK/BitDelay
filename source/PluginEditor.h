#pragma once

#include "PluginProcessor.h"

class BitDelayEditor final : public juce::AudioProcessorEditor
{
public:
    explicit BitDelayEditor (BitDelayAudioProcessor&);
    ~BitDelayEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider delayTime { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider feedbackAmount { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider bitReduction { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider mixSlider { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };

    std::unique_ptr<juce::SliderParameterAttachment> delayTimeSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> bitReductionSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> mixSliderAttachment;

    BitDelayAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitDelayEditor)
};
