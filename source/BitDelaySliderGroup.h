#pragma once

#include "PluginProcessor.h"

class BitDelaySlidersGroup final : public juce::Component
{
public:
    explicit BitDelaySlidersGroup (const BitDelayAudioProcessor& ProcessorRef);

    ~BitDelaySlidersGroup() override = default;

private:
    void resized() override;

    juce::Slider delayTime { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider feedbackAmount { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider bitReduction { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider mixSlider { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };

    std::unique_ptr<juce::SliderParameterAttachment> delayTimeSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> bitReductionSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> mixSliderAttachment;
};
