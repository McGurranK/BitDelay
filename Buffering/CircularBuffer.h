#pragma once

class CircularBuffer final
{
public:
    CircularBuffer () = default;

    void Prepare (const int TimeInSamples, const int NumberOfChannels);
    void processNewSamples (const juce::AudioBuffer<float>& BufferRef);

    void unwindCircularBuffer (const juce::AudioBuffer<float>& BufferRef)
    {
        const auto bufferSize = BufferRef.getNumSamples();



    }

private:
    CircularBufferPlayhead circularPlayHead;
    juce::AudioBuffer<float> circularSampleBuffer;
};
