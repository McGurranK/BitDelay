#pragma once

#include "PluginProcessor.h"

class BitDelaySlidersGroup final : public juce::Component
{
public:
    explicit BitDelaySlidersGroup (const BitDelayAudioProcessor& ProcessorRef)
    {
        for (const auto& Sliders : { &delayTime, &feedbackAmount, &bitReduction, &mixSlider })
        {
            addAndMakeVisible (Sliders);
            Sliders->setWantsKeyboardFocus (true);
        }

        delayTimeSliderAttachment = std::make_unique<juce::SliderParameterAttachment>(dynamic_cast<juce::RangedAudioParameter&> (*ProcessorRef.delayTime), delayTime);
        feedbackSliderAttachment = std::make_unique<juce::SliderParameterAttachment>(dynamic_cast<juce::RangedAudioParameter&> (*ProcessorRef.feedbackAmount), bitReduction);
        bitReductionSliderAttachment = std::make_unique<juce::SliderParameterAttachment>(dynamic_cast<juce::RangedAudioParameter&> (*ProcessorRef.bitReduction), bitReduction);
        mixSliderAttachment = std::make_unique<juce::SliderParameterAttachment>(dynamic_cast<juce::RangedAudioParameter&> (*ProcessorRef.wetDryAmount), mixSlider);
    }

    ~BitDelaySlidersGroup() override = default;

private:
    void resized() override
    {
        auto bounds = getLocalBounds().toFloat();
        const auto sliderWidth = bounds.getWidth() * 0.25f;

        delayTime.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
        feedbackAmount.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
        bitReduction.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
        mixSlider.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
    }

    juce::Slider delayTime { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider feedbackAmount { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider bitReduction { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };
    juce::Slider mixSlider { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox };

    std::unique_ptr<juce::SliderParameterAttachment> delayTimeSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> bitReductionSliderAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> mixSliderAttachment;
};

class BitDelayEditor final : public juce::AudioProcessorEditor
{
public:
    explicit BitDelayEditor (BitDelayAudioProcessor&);
    ~BitDelayEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BitDelayAudioProcessor& processorRef;
    BitDelaySlidersGroup bitDelaySlidersGroup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitDelayEditor)
};
