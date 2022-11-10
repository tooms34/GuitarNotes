#include "samplemodel.h"
#include "SinWaveAudio.h"

SampleModel::SampleModel() 
{
    startTimerHz(60);
}

void SampleModel::changeListenerCallback(juce::ChangeBroadcaster *source)
{  
     std::cout<<"get"<<std::endl;
    auto sourceAudio = static_cast<SinWaveAudio *>(source);
     if(double(m_sampleBuffer.getNumSamples())/sourceAudio->sampleRate()>0.1){
            return;
     }
     std::cout<<"get after"<<std::endl;
     const auto& sourceBuffer=sourceAudio->buffer();
    const auto startTargetSample = m_sampleBuffer.getNumSamples();
    m_sampleBuffer.setSize(sourceBuffer.getNumChannels(), m_sampleBuffer.getNumSamples() + sourceBuffer.getNumSamples(), true, false, true);
     std::unique_lock lock(mutex);
     {
    for (auto chan = 0; chan < m_sampleBuffer.getNumChannels(); ++chan)
    {
        m_sampleBuffer.copyFrom(chan, startTargetSample, sourceBuffer, chan, 0, sourceBuffer.getNumSamples());
    }
     
    m_dataChanged = true;
     }
}


juce::AudioBuffer<float> SampleModel::sampleBuffer() const
    {
        std::shared_lock lock(mutex);
        return m_sampleBuffer;
    }

void SampleModel::timerCallback() 
{    
    std::shared_lock lock(mutex);
    if (m_dataChanged)
    {
        sendChangeMessage();        
        m_dataChanged = false;
    }
}

void SampleModel::clear(){
    std::unique_lock lock(mutex);
    m_sampleBuffer.clear();
    m_sampleBuffer.setSize(0,0,false,true,false);
    std::cout<<"CLEAR"<<std::endl;
     m_dataChanged = true;

}



void SampleModelHandler::actionListenerCallback(const juce::String &message)
{
std::cout<<"action"<<message<<std::endl;
m_model->clear();

}