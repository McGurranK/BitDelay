#include "BitDelaySliderGroup.h"

BitDelaySlidersGroup::BitDelaySlidersGroup (const BitDelayAudioProcessor& ProcessorRef)
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

void BitDelaySlidersGroup::resized() override
{
    auto bounds = getLocalBounds().toFloat();
    const auto sliderWidth = bounds.getWidth() * 0.25f;

    delayTime.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
    feedbackAmount.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
    bitReduction.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
    mixSlider.setBounds (bounds.removeFromLeft (sliderWidth).toNearestInt());
}