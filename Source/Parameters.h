#pragma once
#include <JuceHeader.h>

const juce::ParameterID gainParamID { "gain", 1 };
const juce::ParameterID softnessParamID { "softness", 1 };
const juce::ParameterID thresholdParamID { "threshold", 1 };
const juce::ParameterID volumeParamID{ "volume", 1 };
const juce::ParameterID mixParamID{ "mix", 1 };

class Parameters
{
public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    juce::AudioParameterFloat* gainParam;
    juce::AudioParameterFloat* softnessParam;
    juce::AudioParameterFloat* thresholdParam;
    juce::AudioParameterFloat* volumeParam;
    juce::AudioParameterFloat* mixParam;
};
