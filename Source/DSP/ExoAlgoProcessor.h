#pragma once
template <typename Type>
class ExoAlgoProcessor : public juce::dsp::ProcessorBase
{
public:
    ExoAlgoProcessor()
    {
        
    }

    void prepare (const juce::dsp::ProcessSpec& spec) override
    {
        
    }
    
    void process (const juce::dsp::ProcessContextReplacing<Type>& context) override
    {
        // auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();

        auto numChannels = outputBlock.getNumChannels();
        auto numSamples = outputBlock.getNumSamples();

        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* channelData = outputBlock.getChannelPointer(ch);

            for (size_t i = 0; i < numSamples; ++i)
            {
                channelData[i] = processSample(channelData[i]);
            }
        }
    }
    
    void reset() override
    {
        
    }

    void setSoftness(float newSoftness)
    {
        this->softness = newSoftness;
    }
    void setThreshold(float newThreshold)
    {
        this->threshold = newThreshold;
    }
private:
    float softness;
    float threshold;
    
    float processSample(float input)
    {
        float output = softness*(std::tanh(input*1)*threshold)+(1-softness)*std::max(std::min(input, threshold), -threshold);
        return output;
    }
};
