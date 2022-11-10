#pragma once

#include <JuceHeader.h>


class Spectrogram;
class SpatialSoundViewer;
class ControlsPanel;
class ControlsPanelListener;
class SampleListener;
class SampleModelHandler;

 
class Gui : public juce::Component
{
public:
    Gui();
    ~Gui()override;
    void resized()override;
    std::vector<SampleListener*> listeners()const;

    const ControlsPanel& controlsPanel()const;

    void addListener(ControlsPanelListener* listener);

private:
    juce::FlexBox box;
    std::unique_ptr<Spectrogram> ampSpectrogram;
    std::unique_ptr<Spectrogram> phaseSpectrogram;
    std::unique_ptr<SpatialSoundViewer> spatialSoundViewer;
    std::unique_ptr<ControlsPanel> m_controlsPanel;
    std::unique_ptr<SampleModelHandler> m_sampleModelHandler;
};


