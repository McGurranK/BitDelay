#include "PluginProcessor.h"
#include "PluginEditor.h"


BitDelayEditor::BitDelayEditor (BitDelayAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , bitDelaySlidersGroup (p)
    , processorRef (p)
{
    addAndMakeVisible (&bitDelaySlidersGroup);

    setSize (400, 300);
    setResizable (false, true);
    setResizeLimits (400, 300, 1200, 900);
}

void BitDelayEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    const auto convertedBounds = getLocalBounds().toFloat();
    auto bounds = convertedBounds.withSizeKeepingCentre (convertedBounds.getWidth() * 0.9f, convertedBounds.getHeight() * 0.9f).toFloat();

    g.setColour (juce::Colours::white);
    g.fillRoundedRectangle (bounds.removeFromTop (bounds.getHeight() * 0.2f), 10.f);
    bounds.reduce (0, 5);
    g.fillRoundedRectangle (bounds, 10.f);
}

void BitDelayEditor::resized()
{
    const auto convertedBounds = getLocalBounds().toFloat();
    auto bounds = convertedBounds.withSizeKeepingCentre (convertedBounds.getWidth() * 0.9f, convertedBounds.getHeight() * 0.9f).toFloat();
    bounds.removeFromTop (bounds.getHeight() * 0.2f).reduce (0, 5);

    bitDelaySlidersGroup.setBounds (bounds.toNearestInt());
}