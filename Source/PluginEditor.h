#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/CustomLookAndFeel.h"


class exodistAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    exodistAudioProcessorEditor (exodistAudioProcessor&);
    ~exodistAudioProcessorEditor() override;


    void paint (juce::Graphics&) override;
    void resized() override;

private:
    exodistAudioProcessor& audioProcessor;
    
    CustomLookAndFeel customLookAndFeel;
    
    juce::Slider gainSlider;
    juce::Slider softnessSlider;
    juce::Slider thresholdSlider;
    
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment{audioProcessor.apvts, gainParamID.getParamID(), gainSlider};
    juce::AudioProcessorValueTreeState::SliderAttachment softnessSliderAttachment{audioProcessor.apvts, softnessParamID.getParamID(), softnessSlider};
    juce::AudioProcessorValueTreeState::SliderAttachment thresholdSliderAttachment{audioProcessor.apvts, thresholdParamID.getParamID(), thresholdSlider};
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (exodistAudioProcessorEditor)
};
