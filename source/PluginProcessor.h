#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

class BitDelayAudioProcessor final : public juce::AudioProcessor
{
public:

    BitDelayAudioProcessor();
    ~BitDelayAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioParameterFloat* delayTime;
    juce::AudioParameterFloat* bitReduction;
    juce::AudioParameterFloat* feedbackAmount;
    juce::AudioParameterFloat* wetDryAmount;

private:
    juce::SmoothedValue<float> delayTimeSmoothing;
    juce::SmoothedValue<float> bitRateSmoothing;
    juce::SmoothedValue<float> feedbackSmoothing;

    juce::dsp::DelayLine<float> delayLine;
    juce::dsp::DryWetMixer<float> mixerProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitDelayAudioProcessor)
};
