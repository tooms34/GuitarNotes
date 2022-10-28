#pragma once

#include <JuceHeader.h>

class SinWaveAudio : public juce::AudioSource, public juce::ChangeBroadcaster
{
public:
    SinWaveAudio();
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override { ; }
    //  void paint (juce::Graphics& g) override;

    const juce::AudioBuffer<float> &buffer() const;
     

private:
    float phase = 0.0f;
    float phaseDelta = 0.0f;
    float frequency = 500.0f;
    float amplitude = 0.05f;

    juce::AudioBuffer<float> sampleBuffer;   
   
};
