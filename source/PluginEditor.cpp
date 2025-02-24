#include "PluginProcessor.h"
#include "PluginEditor.h"


AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (BitDelayAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processorRef (p)
{
    addAndMakeVisible (&delayTime);
    addAndMakeVisible (&bitReduction);

    delayTimeSliderAttachment.reset
    (new juce::SliderParameterAttachment(dynamic_cast<juce::RangedAudioParameter&> (*p.delayTime), delayTime));
    bitReductionSliderAttachment.reset
    (new juce::SliderParameterAttachment(dynamic_cast<juce::RangedAudioParameter&> (*p.bitReduction), bitReduction));

    setSize (400, 300);
}

void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    delayTime.setBounds (bounds.removeFromLeft (static_cast<int>(bounds.getWidth() * 0.5)));
    bitReduction.setBounds (bounds);
}
