#pragma once

#include "PluginProcessor.h"

class BitDelayVisualisation final : public juce::Component
{
public:
    explicit BitDelayVisualisation (const juce::AudioProcessor& ProcessorRef, LockFreeFifo& FifoRef)
    : localProcessorRef (ProcessorRef)
    , fifoRef (FifoRef)
    {
        vBlankAttachmentPtr = std::make_unique<juce::VBlankAttachment> (this, []{});
    }

private:
    void checkConfiguration ()
    {
        const auto sampleRate = localProcessorRef.getSampleRate();
        const int numberOfChannels = localProcessorRef.getTotalNumInputChannels();

        if ( ! juce::approximatelyEqual (sampleRate, currentSampleRate) || juce::approximatelyEqual(numberOfChannels, currentNumberOfChannels))
        {
            currentSampleRate = sampleRate;
            currentNumberOfChannels = numberOfChannels;
            // Reallocate resources

            pollingBuffer.setSize (numberOfChannels, 1024, false, false, false);
        }
    }

    void updatePath()
    {
        checkConfiguration();
        pollingBuffer.setSize (pollingBuffer.getNumChannels(), 1024, true, false, true);
        const auto samplesRead = fifoRef.WriteSamples (pollingBuffer);
        pollingBuffer.setSize (pollingBuffer.getNumChannels(), samplesRead, true, false, true);

        delayBuffer.writeSamples (pollingBuffer);

        repaint();
    }

    void paint (juce::Graphics& GraphicsRef) override
    {}

    double currentSampleRate { 0.0 };
    int currentNumberOfChannels { 0};

    const juce::AudioProcessor& localProcessorRef;

    juce::AudioBuffer<float> pollingBuffer;

    LockFreeFifo& fifoRef;
    CircularBuffer<float> delayBuffer;

    std::unique_ptr<juce::VBlankAttachment> vBlankAttachmentPtr;
};


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
