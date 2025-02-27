#include "PluginProcessor.h"
#include "PluginEditor.h"


BitDelayEditor::BitDelayEditor (BitDelayAudioProcessor& p)
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

void BitDelayEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void BitDelayEditor::resized()
{
    auto bounds = getLocalBounds();
    delayTime.setBounds (bounds.removeFromLeft (static_cast<int>(bounds.getWidth() * 0.5)));
    bitReduction.setBounds (bounds);
}
