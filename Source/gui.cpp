#include "gui.h"
#include "spectrogram.h"

Gui::Gui() : ampSpectrogram(std::make_unique<Spectrogram>()),
             phaseSpectrogram(std::make_unique<Spectrogram>()),
             spatialSoundViewer(std::make_unique<SpatialSoundViewer>())
{
     setSize(600, 400);
     addAndMakeVisible(spatialSoundViewer.get());
     ampSpectrogram->color=juce::Colours::red;
    addAndMakeVisible(ampSpectrogram.get());
    phaseSpectrogram->color=juce::Colours::blue;
    addAndMakeVisible(phaseSpectrogram.get());
  //  std::cout<<getLocalBounds().getHeight()<<getLocalBounds().getWidth()<<std::endl;

}

Gui::~Gui()
{
    ;
}

void Gui::resized()
{
    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    fb.alignContent = juce::FlexBox::AlignContent::stretch;
    fb.items.add(juce::FlexItem(*spatialSoundViewer).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(*ampSpectrogram).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(*phaseSpectrogram).withMinWidth(50.0f).withMinHeight(50.0f));
    std::cout<<"--->"<<ampSpectrogram->getWidth();
    fb.performLayout(getLocalBounds().toFloat());
}


std::vector<juce::ChangeListener*> Gui::listeners()const{
 return {static_cast<juce::ChangeListener*>(spatialSoundViewer.get())};
}