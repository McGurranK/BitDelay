#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitDelayAudioProcessor::BitDelayAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
    delayTime = new juce::AudioParameterFloat ("DLTM", "Delay Time", juce::NormalisableRange<float> (1.0f, 48000.0f), 24000.f);
    bitReduction = new juce::AudioParameterFloat ("BTRD", "Bit Rate", juce::NormalisableRange<float> (1.0f, 16.0f), 4.f);

    addParameter(delayTime);
    addParameter(bitReduction);
}

BitDelayAudioProcessor::~BitDelayAudioProcessor()
{
}

//==============================================================================
const juce::String BitDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BitDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BitDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BitDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BitDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BitDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BitDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BitDelayAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String BitDelayAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void BitDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void BitDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.numChannels = static_cast<uint32_t>(getTotalNumInputChannels());
    spec.maximumBlockSize = static_cast<uint32_t>(samplesPerBlock);
    spec.sampleRate = sampleRate;

    delayLine.prepare (spec);
    delayLine.setMaximumDelayInSamples (48000);
    delayLine.setDelay (24000);

    delayTimeSmoothing.reset (sampleRate,0.01);
    bitRateSmoothing.reset (sampleRate,0.01);

    delayTimeSmoothing.setCurrentAndTargetValue (delayTime->get());
    bitRateSmoothing.setCurrentAndTargetValue (delayTime->get());
}

void BitDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool BitDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void BitDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    const auto numberOfChannels = buffer.getNumChannels();
    const auto numberOfSamples = buffer.getNumSamples();

    delayTimeSmoothing.setTargetValue (delayTime->get());
    bitRateSmoothing.setTargetValue ( bitReduction->get());

    for (int channelIndex =0; channelIndex < numberOfChannels; channelIndex++)
    {
        auto* channelPointer = buffer.getWritePointer (channelIndex);

        for (int sampleIndex = 0; sampleIndex < numberOfSamples; sampleIndex++)
        {
            const auto bitReductionMultiplier = std::pow (2.f, bitRateSmoothing.getNextValue());

            auto delayedSample = delayLine.popSample (channelIndex, delayTimeSmoothing.getNextValue()) * 0.9f;

            // Reduction of bit rate after popping sample
            delayedSample *= bitReductionMultiplier;
            delayedSample = std::round (delayedSample);
            delayedSample /= bitReductionMultiplier;

            channelPointer[sampleIndex] += delayedSample;

            delayLine.pushSample (channelIndex, channelPointer[sampleIndex]);
        }
    }
}

//==============================================================================
bool BitDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BitDelayAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void BitDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void BitDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BitDelayAudioProcessor();
}
