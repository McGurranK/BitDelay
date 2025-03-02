// Basic state loading code to reuse in JUCE projects (TODO: Add Unit tests)
class BasicStateLoading
{
public:
  BasicStateLoading (juce::AudioProcessor& ProcessorRef);

  void getStateInformation (juce::MemoryBlock& destData);
  void setParameterInformation (const void* data, int sizeInBytes);

private:
  const juce::String xmlStringName {"Parameters"};
  const juce::String xmlValueAttribruteString {"Value"};

  juce::AudioProcessor& processorRef;
};
