#include "PluginProcessor.h"
#include "PluginEditor.h"


exodistAudioProcessor::exodistAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),params(apvts)
#endif
{
    auto& dryWetMixer = chain.template get<DryWetMixerIndex>();
    dryWetMixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    dryWetMixer.setWetLatency(0.0f);
}

exodistAudioProcessor::~exodistAudioProcessor()
{
}


const juce::String exodistAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool exodistAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool exodistAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool exodistAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double exodistAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int exodistAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int exodistAudioProcessor::getCurrentProgram()
{
    return 0;
}

void exodistAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String exodistAudioProcessor::getProgramName (int index)
{
    return {};
}

void exodistAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


void exodistAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;

    chain.prepare(spec);

    auto& dryWetMixer = chain.template get<DryWetMixerIndex>();
    dryWetMixer.prepare(spec);
}

void exodistAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool exodistAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void exodistAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    auto& gainProcessor = chain.template get<GainProcessorIndex>();
    auto& exoAlgoProcessor = chain.template get<ExoAlgoProcessorIndex>();
    auto& volumeProcessor = chain.template get<VolumeIndex>();
    auto& dryWetMixer = chain.template get<DryWetMixerIndex>();
    
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    dryWetMixer.pushDrySamples(block);
    
    float gain = params.gainParam->get();
    float softness = params.softnessParam->get();
    float treshold = params.thresholdParam->get();
    float volume = params.volumeParam->get();
    
    gainProcessor.setGainDecibels(gain);
    exoAlgoProcessor.setSoftness(softness);
    exoAlgoProcessor.setThreshold(treshold);
    volumeProcessor.setGainDecibels(volume);
    
    // chain.process(context);
    gainProcessor.process(context);
    exoAlgoProcessor.process(context);
    volumeProcessor.process(context);

    dryWetMixer.setWetMixProportion(params.mixParam->get());
    dryWetMixer.mixWetSamples(block);
}


bool exodistAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* exodistAudioProcessor::createEditor()
{
    return new exodistAudioProcessorEditor(*this);
    // return new juce::GenericAudioProcessorEditor(*this);
}


void exodistAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void exodistAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.replaceState(tree);
    }
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new exodistAudioProcessor();
}
