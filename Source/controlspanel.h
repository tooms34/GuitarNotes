#pragma once

#include <JuceHeader.h>

 


class ControlsPanel : public juce::Component,
                      public juce::ChangeBroadcaster
{
public:
ControlsPanel();
void resized();
private:
    std::unique_ptr<TextButton> pauseButton;
};
  


