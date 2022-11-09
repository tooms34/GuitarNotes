#pragma once

#include <JuceHeader.h>

struct ControlsPanelModel
{
    double zoomHValue=1.0;
    double zoomVValue=1.0;
    bool pauseOn=false;
    double frequency=0;

};

class ControlsPanelListener : public juce::ActionListener
{
public:
    virtual void setControlsPanelModel(std::shared_ptr<ControlsPanelModel> model);
protected:
    std::shared_ptr<ControlsPanelModel> m_controlModel;
};