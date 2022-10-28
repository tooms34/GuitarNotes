#pragma once

#include <JuceHeader.h>


class Spectrogram;
class SpatialSoundViewer;
class ControlsPanel;

 
class Gui : public juce::Component
{
public:
    Gui();
    ~Gui()override;
    void resized()override;
    std::vector<juce::ChangeListener*> listeners()const;

private:
    juce::FlexBox box;
    std::unique_ptr<Spectrogram> ampSpectrogram;
    std::unique_ptr<Spectrogram> phaseSpectrogram;
    std::unique_ptr<SpatialSoundViewer> spatialSoundViewer;
    std::unique_ptr<ControlsPanel> controlsPanel;
};


