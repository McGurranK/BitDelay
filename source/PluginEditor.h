#pragma once

#include "PluginProcessor.h"
#include "BitDelaySliderGroup.h"

struct CircularBufferContext
{
    int PlayPositionOne { 0 };
    int PlayPositionOneSize { 0 };
    int PlayPositionTwo { 0 };
    int PlayPositionTwoSize { 0 };
};

class CircularBufferPlayhead final
{
public:
    void prepare (const int Size)
    {
        bufferSize = Size;
    }

    CircularBufferContext UpdateCircularBuffer (const int IncrementBy)
    {
        CircularBufferContext bufferContext{};

        bufferContext.PlayPositionOne = currentPlayPosition;
        currentPlayPosition += IncrementBy;

        const auto bufferSizeTwo = (currentPlayPosition > bufferSize) ? currentPlayPosition % bufferSize: 0;

        currentPlayPosition %= bufferSize;

        bufferContext.PlayPositionTwo = 0;
        bufferContext.PlayPositionTwo = bufferSizeTwo;

        return bufferContext;
    }

    int currentPlayPosition { 0 };
    int bufferSize { 0 };
};


class CircularBuffer final
{
public:
    CircularBuffer () = default;

    void Prepare (const int TimeInSamples, const int NumberOfChannels)
    {
        circularPlayHead.prepare (TimeInSamples);
        circularSampleBuffer.setSize (NumberOfChannels, TimeInSamples);
        circularSampleBuffer.clear();
    }

    void processNewSamples (const juce::AudioBuffer<float>& BufferRef)
    {
        const auto BufferSize = BufferRef.getNumSamples();
        const auto bufferContext = circularPlayHead.UpdateCircularBuffer (BufferSize);

        const auto bufferContextUpdate = [&](int PlayStart, int NumberOfSamples, int ReadOffset)
        {
            for (int ChannelIndex  = 0; ChannelIndex < BufferRef.getNumChannels(); ++ChannelIndex)
                circularSampleBuffer.copyFrom (ChannelIndex, PlayStart, BufferRef, ChannelIndex, ReadOffset, NumberOfSamples);
        };

        if (bufferContext.PlayPositionOne > 0)
            bufferContextUpdate (bufferContext.PlayPositionOne, bufferContext.PlayPositionOneSize, 0);

        if (bufferContext.PlayPositionTwo > 0)
            bufferContextUpdate (bufferContext.PlayPositionTwo, bufferContext.PlayPositionTwoSize, 0);
    }
    
    CircularBufferPlayhead circularPlayHead;
    juce::AudioBuffer<float> circularSampleBuffer;
};


class BitDelayVisualisation final : public juce::Component {
public:
    BitDelayVisualisation () = default;

private:
    void paint(juce::Graphics& GraphicsRef) override
    {

    }
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
