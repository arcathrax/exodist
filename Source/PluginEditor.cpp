#include "PluginProcessor.h"
#include "PluginEditor.h"


exodistAudioProcessorEditor::exodistAudioProcessorEditor (exodistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

exodistAudioProcessorEditor::~exodistAudioProcessorEditor()
{
}


void exodistAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto image = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    juce::Rectangle<float> rectangle (0.f, 0.f, getWidth(), getHeight());
    g.setOpacity(1.0f);
    g.drawImage(image, rectangle, juce::RectanglePlacement::stretchToFit);
}

void exodistAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
