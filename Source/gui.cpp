#include "gui.h"
#include "spectrogram.h"

Gui::Gui() : ampSpectrogram(std::make_unique<Spectrogram>()),
             phaseSpectrogram(std::make_unique<Spectrogram>())
{
    addAndMakeVisible(ampSpectrogram.get());
    addAndMakeVisible(phaseSpectrogram.get());
    
}

Gui::~Gui()
{
    ;
}

void Gui::resized()
{
    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.items.add(juce::FlexItem(*ampSpectrogram).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(*phaseSpectrogram).withMinWidth(50.0f).withMinHeight(50.0f));

    fb.performLayout(getLocalBounds().toFloat());
}