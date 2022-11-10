#include "gui.h"
#include "spectrogram.h"
#include "spatialsoundviewer.h"
#include "controlspanel.h"
#include "samplemodel.h"

Gui::Gui() : ampSpectrogram(std::make_unique<Spectrogram>()),
             phaseSpectrogram(std::make_unique<Spectrogram>()),
             spatialSoundViewer(std::make_unique<SpatialSoundViewer>()),
             m_controlsPanel(std::make_unique<ControlsPanel>()),
             m_sampleModelHandler(std::make_unique<SampleModelHandler>())
{
    setSize(600, 400);
    addAndMakeVisible(spatialSoundViewer.get());
    ampSpectrogram->color = juce::Colours::red;
    addAndMakeVisible(ampSpectrogram.get());
    phaseSpectrogram->color = juce::Colours::blue;
    addAndMakeVisible(phaseSpectrogram.get());
    addAndMakeVisible(m_controlsPanel.get());
    addListener(spatialSoundViewer.get());
    addListener(m_sampleModelHandler.get());
 
}

Gui::~Gui()
{
    m_controlsPanel->removeActionListener(spatialSoundViewer.get());
   
}

const ControlsPanel &Gui::controlsPanel() const
{
    return *m_controlsPanel;
}

void Gui::resized()
{
    juce::Grid grid;

    grid.rowGap = 10_px;
    grid.columnGap = 10_px;
    grid.templateRows = {juce::Grid::TrackInfo(juce::Grid::Fr(30)),
                         juce::Grid::TrackInfo(juce::Grid::Fr(30)),
                         juce::Grid::TrackInfo(juce::Grid::Fr(30)),
                         juce::Grid::TrackInfo(juce::Grid::Fr(10))};
    grid.templateColumns = {juce::Grid::TrackInfo(juce::Grid::Fr(100))};

    grid.autoFlow = juce::Grid::AutoFlow::column;
    /*juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    fb.alignContent = juce::FlexBox::AlignContent::stretch;
    fb.items.add(juce::FlexItem(.withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(*ampSpectrogram).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(*phaseSpectrogram).withMinWidth(50.0f).withMinHeight(50.0f));
    std::cout<<"--->"<<ampSpectrogram->getWidth();
    fb.performLayout(getLocalBounds().toFloat());*/
    grid.items.addArray({GridItem(*spatialSoundViewer),
                         GridItem(*ampSpectrogram),
                         GridItem(*phaseSpectrogram),
                         GridItem(*m_controlsPanel)});
    grid.performLayout(getLocalBounds());
}

std::vector<SampleListener *> Gui::listeners() const
{
    return {static_cast<SampleListener *>(spatialSoundViewer.get()), static_cast<SampleListener *>(ampSpectrogram.get()),static_cast<SampleListener *>(m_sampleModelHandler.get())};
}

void Gui::addListener(ControlsPanelListener *listener)
{
    m_controlsPanel->addActionListener(listener);
    listener->setControlsPanelModel(m_controlsPanel->model());
}