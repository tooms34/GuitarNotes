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
    auto res=sampleBuffer.findMinMax (0, 0,sampleBuffer.getNumSamples());
     //std::cout<<"minmax Sinwave"<<res.getStart()<<"   "<<res.getEnd()<<std::endl;
    sendChangeMessage();
}

void SinWaveAudio::prepareToPlay(int samplesPerBlockExpected, double newSampleRate)
{
    std::cout << "sample" << newSampleRate << "samples:" << samplesPerBlockExpected << std::endl;
    phaseDelta = (float)(juce::MathConstants<double>::twoPi * frequency / newSampleRate);
}

/*
   void SinWaveAudio::paint (juce::Graphics& g)
    {
        juce::Rectangle<int> thumbnailBounds (10, 100, getWidth() - 20, getHeight() - 120);

        if (thumbnail.getNumChannels() == 0)
            paintIfNoFileLoaded (g, thumbnailBounds);
        else
            paintIfFileLoaded (g, thumbnailBounds);
    }*/



 const juce::AudioBuffer<float> & SinWaveAudio::buffer() const
    {
        
        return sampleBuffer;
    }