#pragma once

#include <JuceHeader.h>

struct ControlsPanelModel
{
    double zoomHValue=1.0;
    double zoomVValue=1.0;
    bool pauseOn=false;

};

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
    juce::Slider zoomHorizontal;
    juce::Slider zoomVertical;

    std::shared_ptr<ControlsPanelModel> m_model;
};