#pragma once


#include <JuceHeader.h>
#include "audioprovider.h"
#include "gui.h"
 

class SampleModel;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    AudioProvider audioProvider;
    Gui mainGui;
    std::shared_ptr<SampleModel> sampleModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

 



