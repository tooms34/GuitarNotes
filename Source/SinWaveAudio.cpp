#include "SinWaveAudio.h"

SinWaveAudio::SinWaveAudio()
{
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
    }
}

void SinWaveAudio::prepareToPlay(int samplesPerBlockExpected, double newSampleRate)
{
    std::cout << "sample" << newSampleRate << "samples:" << samplesPerBlockExpected << std::endl;
    phaseDelta = (float) (juce::MathConstants<double>::twoPi * frequency / newSampleRate);
}
