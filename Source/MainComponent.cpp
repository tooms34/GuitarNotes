#include "MainComponent.h"
#include "SinWaveAudio.h"
#include "samplemodel.h"

//==============================================================================
MainComponent::MainComponent(): sampleModel(std::make_shared<SampleModel>())
{
    setSize(600, 400);
    addAndMakeVisible(&mainGui);

     
    mainGui.addListener(audioProvider.sourceAudio());

    audioProvider.addListener(sampleModel.get());
    
     for(const auto item:mainGui.listeners()){
        item->setModel(sampleModel);
        sampleModel->addChangeListener(item);
    }
}

MainComponent::~MainComponent()
{
      
        audioProvider.removeListener(sampleModel.get());
    
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

 