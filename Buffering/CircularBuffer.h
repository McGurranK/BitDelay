#pragma once

class CircularBuffer final
{
public:
    CircularBuffer () = default;

    void Prepare (const int TimeInSamples, const int NumberOfChannels);
    void processNewSamples (const juce::AudioBuffer<float>& BufferRef);

    void unwindCircularBuffer (const juce::AudioBuffer<float>& BufferRef)
    {
        juce::ignoreUnused (BufferRef);
        // Todo : Add unwinding
    }

private:
    CircularBufferPlayhead circularPlayHead;
    juce::AudioBuffer<float> circularSampleBuffer;
};
