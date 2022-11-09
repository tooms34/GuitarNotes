#pragma once

#include <JuceHeader.h>
#include "samplemodel.h"

 
class Spectrogram : public juce::Component,public SampleListener
{
public:
    Spectrogram();
    ~Spectrogram()override;
   
    void paint(juce::Graphics &g) override;

    juce::Colour color;

    void changeListenerCallback(juce::ChangeBroadcaster *)override;

private:    
    static constexpr size_t fftSize=1<<10;
    std::vector<float> m_fftData;
    dsp::FFT forwardFFT;
    juce::Image spectrogramImage;
}; 