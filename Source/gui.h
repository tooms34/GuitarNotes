#pragma once

#include <JuceHeader.h>

class Spectrogram;

class Gui : public juce::Component
{
public:
    Gui();
    ~Gui()override;
    void resized()override;

private:
    juce::FlexBox box;
    std::unique_ptr<Spectrogram> ampSpectrogram;
    std::unique_ptr<Spectrogram> phaseSpectrogram;
};
