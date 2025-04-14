#include "Parameters.h"

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(gainParamID.getParamID()));
    softnessParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(softnessParamID.getParamID()));
    thresholdParam = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter(thresholdParamID.getParamID()));
}


juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    auto gainParameter = std::make_unique<juce::AudioParameterFloat>(
        gainParamID,
        "gain",
        juce::NormalisableRange<float>
        (
            0.75f,
            12.0f,
            0.000001f,
            0.5f
        ),
        1.0f
    );
    auto softnessParameter = std::make_unique<juce::AudioParameterFloat>(
        softnessParamID,
        "softness",
        juce::NormalisableRange<float>
        (
            0.f,
            1.f,
            0.000001f,
            0.5f
        ),
        0.f
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

    auto parameters = std::make_unique<
        juce::AudioProcessorParameterGroup>
    (
        "parameters",
        "PARAMETERS",
        "|",
        std::move(gainParameter),
        std::move(softnessParameter),
        std::move(thresholdParameter)
     );

    layout.add
    (
        std::move(parameters)
    );

    return layout;
}
