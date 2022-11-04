#pragma once

#include <JuceHeader.h>

 
class Spectrogram : public juce::Component
{
public:
    Spectrogram() = default;
    void setData(std::vector<float> &&data);
    void paint(juce::Graphics &g) override;

    juce::Colour color;

private:
    std::vector<float> m_data;
}; 