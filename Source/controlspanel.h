#pragma once

#include <JuceHeader.h>
#include "controlspanellistener.h"

class ControlsPanel : public juce::Component,
                      public juce::ActionBroadcaster
{
public:
    ControlsPanel();
    void resized();
    std::shared_ptr<ControlsPanelModel> model()const{
        return m_model;
    }

private:
void updateModel();

private:
    std::unique_ptr<TextButton> pauseButton;
     std::unique_ptr<TextButton> fftButton;
    juce::Slider zoomHorizontal;
    juce::Slider zoomVertical;
    std::unique_ptr<juce::Slider> frequencySlider;

    std::shared_ptr<ControlsPanelModel> m_model;
};

 