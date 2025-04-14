#include "PluginProcessor.h"
#include "PluginEditor.h"


exodistAudioProcessorEditor::exodistAudioProcessorEditor (exodistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    softnessSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    thresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    
    gainSlider.setLookAndFeel(&customLookAndFeel);
    softnessSlider.setLookAndFeel(&customLookAndFeel);
    thresholdSlider.setLookAndFeel(&customLookAndFeel);
    
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(softnessSlider);
    addAndMakeVisible(thresholdSlider);
    
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
    const int gainSize = 200;
    const int otherSize = 75;

    // Mitte – gainSlider
    gainSlider.setBounds(
        getWidth() / 2 - gainSize / 2,
        getHeight() / 2 - gainSize / 2,
        gainSize,
        gainSize
    );

    // Unten links – softnessSlider (80 px von links, 50 px vom Boden)
    softnessSlider.setBounds(
        70,
        getHeight() - otherSize - 60,
        otherSize,
        otherSize
    );

    // Unten rechts – thresholdSlider (80 px von rechts, 50 px vom Boden)
    thresholdSlider.setBounds(
        getWidth() - otherSize - 70,
        getHeight() - otherSize - 60,
        otherSize,
        otherSize
    );
}

