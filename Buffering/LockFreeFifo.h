#pragma once

class LockFreeFifo
{
public:
  void prepare (const int NumberOfChannels, const int NumberOfSamples);
  void readSamples (const juce::AudioBuffer<float>& BufferRef);
  int WriteSamples (juce::AudioBuffer<float>& BufferRef);

private:
  juce::AudioBuffer<float> buffer;
  juce::AbstractFifo bufferFifo { 1 };
};
