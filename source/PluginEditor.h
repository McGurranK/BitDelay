#pragma once

#include "PluginProcessor.h"

class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (BitDelayAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider delayTime { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider bitReduction { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };

    std::unique_ptr<juce::SliderParameterAttachment> delayTimeSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> bitReductionSliderAttachment;

    BitDelayAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
