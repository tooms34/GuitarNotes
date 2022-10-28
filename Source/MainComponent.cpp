#include "MainComponent.h"
#include "SinWaveAudio.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(600, 400);
    addAndMakeVisible(&mainGui);
    for(auto listener:mainGui.listeners()){
        audioProvider.addListener(listener);
    }    
}

MainComponent::~MainComponent()
{
     for(auto listener:mainGui.listeners()){
        audioProvider.removeListener(listener);
    }
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
    juce::Component::paint(g);
    /*
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);*/
}

void MainComponent::resized()
{
    mainGui.setBounds(getLocalBounds());
   juce::Component::resized();
}

 