#pragma once

#include <JuceHeader.h>

class SinWaveAudio : public juce::AudioSource
{
public:
    SinWaveAudio();
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override { ; }

private:
    float phase = 0.0f;
    float phaseDelta = 0.0f;
    float frequency = 5000.0f;
    float amplitude = 0.05f;
};
 