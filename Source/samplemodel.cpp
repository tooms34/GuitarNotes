#include "samplemodel.h"
#include "SinWaveAudio.h"

SampleModel::SampleModel() 
{
    startTimerHz(60);
}

void SampleModel::changeListenerCallback(juce::ChangeBroadcaster *source)
{  
    auto sourceAudio = static_cast<SinWaveAudio *>(source);
     if(double(m_sampleBuffer.getNumSamples())/sourceAudio->sampleRate()>0.1){
            return;
     }
     const auto& sourceBuffer=sourceAudio->buffer();
    const auto startTargetSample = m_sampleBuffer.getNumSamples();
    m_sampleBuffer.setSize(sourceBuffer.getNumChannels(), m_sampleBuffer.getNumSamples() + sourceBuffer.getNumSamples(), true, false, true);
    for (auto chan = 0; chan < m_sampleBuffer.getNumChannels(); ++chan)
    {
        m_sampleBuffer.copyFrom(chan, startTargetSample, sourceBuffer, chan, 0, sourceBuffer.getNumSamples());
    }
    m_dataChanged = true;
}

void SampleModel::timerCallback() 
{    
    if (m_dataChanged)
    {
        sendChangeMessage();
        m_dataChanged = false;
    }
}

void SampleModel::clear(){
    m_sampleBuffer.clear();
     m_dataChanged = true;

}