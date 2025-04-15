#include "Parameters.h"

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(gainParamID.getParamID()));
    softnessParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(softnessParamID.getParamID()));
    thresholdParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(thresholdParamID.getParamID()));
    volumeParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(volumeParamID.getParamID()));
    mixParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(mixParamID.getParamID()));
}


juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    auto gainParameter = std::make_unique<juce::AudioParameterFloat>(
        gainParamID,
        "gain",
        juce::NormalisableRange<float>
        (
            0.0f,
            24.0f,
            0.000001f,
            0.5f
        ),
        0.0f
    );
    auto softnessParameter = std::make_unique<juce::AudioParameterFloat>(
        softnessParamID,
        "softness",
        juce::NormalisableRange<float>
        (
            0.f,
            1.f,
            0.000001f,
            1.f
        ),
        0.5f
    );
    auto thresholdParameter = std::make_unique<juce::AudioParameterFloat>(
        thresholdParamID,
        "threshold",
        juce::NormalisableRange<float>
        (
            0.f,
            1.f,
            0.000001f,
            0.5f
        ),
        1.0f
    );
    auto volumeParameter = std::make_unique<juce::AudioParameterFloat>(
        volumeParamID,
        "volume",
        juce::NormalisableRange<float>
        (
            0.0f,
            12.0f,
            0.000001f,
            0.5f
        ),
        0.0f
    );
    auto mixParameter = std::make_unique<juce::AudioParameterFloat>(
        mixParamID,
        "mix",
        juce::NormalisableRange<float>
        (
            0.f,
            1.f,
            0.000001f,
            1.f
        ),
        1.0f
    );

    auto parameters = std::make_unique<
        juce::AudioProcessorParameterGroup>
    (
        "parameters",
        "PARAMETERS",
        "|",
        std::move(gainParameter),
        std::move(softnessParameter),
        std::move(thresholdParameter),
        std::move(volumeParameter),
        std::move(mixParameter)
     );

    layout.add
    (
        std::move(parameters)
    );

    return layout;
}
