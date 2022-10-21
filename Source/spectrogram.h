#pragma once

#include <JuceHeader.h>

class Spectrogram : public juce::Component
{
public:
    Spectrogram() = default;
    void paint(juce::Graphics &g) override;
};
