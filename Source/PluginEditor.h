#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class exodistAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    exodistAudioProcessorEditor (exodistAudioProcessor&);
    ~exodistAudioProcessorEditor() override;


    void paint (juce::Graphics&) override;
    void resized() override;

private:
    exodistAudioProcessor& audioProcessor;
    
    juce::Slider gainSlider;
    juce::Slider softnessSlider;
    juce::Slider thresholdSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (exodistAudioProcessorEditor)
};
