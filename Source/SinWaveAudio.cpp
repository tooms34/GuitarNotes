#include "SinWaveAudio.h"

SinWaveAudio::SinWaveAudio()
{
   //Timer::callAfterDelay(3000,[this](){std::cout<<"event"<<std::endl;amplitude=(amplitude==0.05)?0.2:0.05;});
   
}

void SinWaveAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    auto originalPhase = phase;

    for (auto chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan)
    {
        phase = originalPhase;

        auto *channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);
        for (auto i = 0; i < bufferToFill.numSamples; ++i)
        {
            channelData[i] = amplitude * std::sin(phase);

            // increment the phase step for the next sample
            phase = std::fmod(phase + phaseDelta, juce::MathConstants<float>::twoPi);
        }
        // std::cout<<"here0"<<std::endl;
    }
    sampleBuffer.makeCopyOf(*bufferToFill.buffer);
    sendChangeMessage();
}

void SinWaveAudio::prepareToPlay(int samplesPerBlockExpected, double newSampleRate)
{
    m_sampleRate=newSampleRate;   
    std::cout << "sample" << newSampleRate << "samples:" << samplesPerBlockExpected << std::endl;
    phaseDelta = (float)(juce::MathConstants<double>::twoPi * frequency / m_sampleRate);
}




 const juce::AudioBuffer<float> & SinWaveAudio::buffer() const
    {
        
        return sampleBuffer;
    }

double SinWaveAudio::sampleRate()const{

    return m_sampleRate;
}


void SinWaveAudio::actionListenerCallback(const juce::String &message)
{
    if (message == "Frequency")
    {      
        frequency=float(m_controlModel->frequency);    
        phaseDelta = (float)(juce::MathConstants<double>::twoPi * frequency / m_sampleRate);
    }
}