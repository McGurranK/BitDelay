#pragma once

#include "PluginProcessor.h"
#include "BitDelaySliderGroup.h"

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
