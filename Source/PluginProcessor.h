#pragma once

#include <JuceHeader.h>
#include "Parameters.h"
#include "DSP/ExoAlgoProcessor.h"

class exodistAudioProcessor  : public juce::AudioProcessor
{
public:
    exodistAudioProcessor();
    ~exodistAudioProcessor() override;


    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;


    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;


    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;


    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;


    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts {
        *this, nullptr, "Parameters", Parameters::createParameterLayout()
    };
    Parameters params;
    
private:
    // ProcessorChain setup
    using ProcessorChain = juce::dsp::ProcessorChain<
        juce::dsp::DryWetMixer<float>,
        juce::dsp::Gain<float>,
        ExoAlgoProcessor<float>,
        juce::dsp::Gain<float>
    >;
    ProcessorChain chain;
    
    enum
    {
        DryWetMixerIndex,
        GainProcessorIndex,
        ExoAlgoProcessorIndex,
        VolumeIndex
    };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (exodistAudioProcessor)
};
