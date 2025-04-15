#include "PluginProcessor.h"
#include "PluginEditor.h"


exodistAudioProcessorEditor::exodistAudioProcessorEditor (exodistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    softnessSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    thresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    volumeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    
    gainSlider.setLookAndFeel(&customLookAndFeel);
    softnessSlider.setLookAndFeel(&customLookAndFeel);
    thresholdSlider.setLookAndFeel(&customLookAndFeel);
    mixSlider.setLookAndFeel(&customLookAndFeel);
    volumeSlider.setLookAndFeel(&customLookAndFeel);
    
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(softnessSlider);
    addAndMakeVisible(thresholdSlider);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(volumeSlider);
    
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
    const int mediumSize = 75;
    const int smallSize = 35;

    gainSlider.setBounds(
        getWidth() / 2 - gainSize / 2,
        getHeight() / 2 - gainSize / 2,
        gainSize,
        gainSize
    );

    softnessSlider.setBounds(
        70,
        getHeight() - mediumSize - 60,
        mediumSize,
        mediumSize
    );

    thresholdSlider.setBounds(
        getWidth() - mediumSize - 70,
        getHeight() - mediumSize - 60,
        mediumSize,
        mediumSize
    );

    mixSlider.setBounds(
        90,
        80,
        smallSize,
        smallSize
    );

    volumeSlider.setBounds(
        getWidth() - smallSize - 90,
        80,
        smallSize,
        smallSize
    );
}


