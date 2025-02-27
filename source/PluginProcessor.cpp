#include "PluginProcessor.h"
#include "PluginEditor.h"

BitDelayAudioProcessor::BitDelayAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
{
    delayTime = new juce::AudioParameterFloat ("DLTM", "Delay Time", juce::NormalisableRange<float> (2.0f, 48000.0f), 24000.f);
    bitReduction = new juce::AudioParameterFloat ("BTRD", "Bit Rate", juce::NormalisableRange<float> (2.0f, 16.0f), 4.f);
    feedbackAmount  = new juce::AudioParameterFloat ("FBAM", "Delay Feedback", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5);
    wetDryAmount  = new juce::AudioParameterFloat ("MIX", "Mix Amount", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5);

    addParameter(delayTime);
    addParameter(bitReduction);
    addParameter(feedbackAmount);
    addParameter(wetDryAmount);
}

const juce::String BitDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BitDelayAudioProcessor::acceptsMidi() const
{
    return false;
}

bool BitDelayAudioProcessor::producesMidi() const
{
    return false;
}

bool BitDelayAudioProcessor::isMidiEffect() const
{
    return false;
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

    mixerProcessor.prepare (spec);
    mixerProcessor.setWetMixProportion (wetDryAmount->get());

    delayTimeSmoothing.reset (sampleRate,0.01);
    bitRateSmoothing.reset (sampleRate,0.01);
    feedbackSmoothing.reset (sampleRate,0.01);

    delayTimeSmoothing.setCurrentAndTargetValue (delayTime->get());
    bitRateSmoothing.setCurrentAndTargetValue (16.f);
    feedbackSmoothing.setCurrentAndTargetValue (0.5f);
}

void BitDelayAudioProcessor::releaseResources()
{
}

bool BitDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void BitDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    const auto numberOfChannels = buffer.getNumChannels();
    const auto numberOfSamples = buffer.getNumSamples();

    delayTimeSmoothing.setTargetValue (delayTime->get());
    bitRateSmoothing.setTargetValue ( bitReduction->get());
    feedbackSmoothing.setTargetValue ( feedbackAmount->get());

    mixerProcessor.setWetMixProportion (wetDryAmount->get());
    mixerProcessor.pushDrySamples (buffer);

    for (int channelIndex =0; channelIndex < numberOfChannels; channelIndex++)
    {
        auto* channelPointer = buffer.getWritePointer (channelIndex);

        for (int sampleIndex = 0; sampleIndex < numberOfSamples; sampleIndex++)
        {
            const auto bitReductionMultiplier = std::pow (2.f, bitRateSmoothing.getNextValue());

            auto delayedSample = delayLine.popSample (channelIndex, delayTimeSmoothing.getNextValue());

            // Reduction of bit rate after popping sample
            delayedSample *= bitReductionMultiplier;
            delayedSample = std::round (delayedSample);
            delayedSample /= bitReductionMultiplier;

            channelPointer[sampleIndex] += delayedSample;

            delayLine.pushSample (channelIndex, channelPointer[sampleIndex] * feedbackSmoothing.getNextValue());
        }
    }

    mixerProcessor.mixWetSamples (buffer);
}

//==============================================================================
bool BitDelayAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* BitDelayAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
    //return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void BitDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void BitDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BitDelayAudioProcessor();
}