#include "SinWaveAudio.h"

SinWaveAudio::SinWaveAudio()
{
}

void SinWaveAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    auto originalPhase = phase;
//std::cout<<"begin"<<std::endl;

  const auto startTargetSample=sampleBuffer.getNumSamples();
   sampleBuffer.setSize(bufferToFill.buffer->getNumChannels(),sampleBuffer.getNumSamples()+bufferToFill.numSamples,true,false,true);
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

        sampleBuffer.addFrom(chan, startTargetSample, channelData, bufferToFill.numSamples);
         // std::cout<<"here1"<<std::endl;
        if (sampleBuffer.getNumSamples() / 1024 > oldValue)
        {
            auto res=sampleBuffer.findMinMax(chan,0,sampleBuffer.getNumSamples());
            std::cout<<"here"<<res.getStart()<<"   "<<res.getEnd()<<std::endl;
            oldValue = sampleBuffer.getNumSamples() / 1024;
            sendChangeMessage();
        }
    }
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
