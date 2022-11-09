#include "controlspanel.h"

ControlsPanel::ControlsPanel() : m_model(std::make_shared<ControlsPanelModel>())
{
  pauseButton = std::make_unique<TextButton>("Pause");
  fftButton = std::make_unique<TextButton>("FFT");
  frequencySlider = std::make_unique<juce::Slider>(juce::Slider::Rotary,juce::Slider::TextBoxLeft);
  pauseButton->setClickingTogglesState (true);
  addAndMakeVisible(*pauseButton);
  addAndMakeVisible(zoomHorizontal);
  addAndMakeVisible(zoomVertical);
  addAndMakeVisible(*frequencySlider);
  frequencySlider->setRange(20,18000);
  zoomVertical.setRange(1,100);
  zoomHorizontal.setRange(1,100);

  pauseButton->onClick = [this]
  { updateModel();sendActionMessage("Pause"); };

  zoomHorizontal.onValueChange = [this]
  {
    updateModel();
    sendActionMessage("ZoomH");
  };
  zoomVertical.onValueChange = [this]
  {
    updateModel();
    sendActionMessage("ZoomV");
  };
    frequencySlider->onValueChange = [this]
  {
    updateModel();
    sendActionMessage("Frequency");
  };
  updateModel();
}

void ControlsPanel::updateModel()
{
  m_model->pauseOn = pauseButton->getToggleState();
  zoomHorizontal.setEnabled(m_model->pauseOn );
  zoomVertical.setEnabled(m_model->pauseOn );
  m_model->zoomHValue = zoomHorizontal.getValue();
  m_model->zoomVValue = zoomVertical.getValue();
  m_model->frequency = frequencySlider->getValue();
}

void ControlsPanel::resized()
{
  juce::Grid grid;

  grid.rowGap = 5_px;
  grid.columnGap = 5_px;
  grid.templateColumns = {juce::Grid::TrackInfo(juce::Grid::Fr(20)),
   juce::Grid::TrackInfo(juce::Grid::Fr(20)),
  juce::Grid::TrackInfo(juce::Grid::Fr(30)),
  juce::Grid::TrackInfo(juce::Grid::Fr(30))
  };

  grid.templateRows = {juce::Grid::TrackInfo(juce::Grid::Fr(150))};

  grid.items.addArray({GridItem(*pauseButton),
                       GridItem(*frequencySlider),
                       GridItem(zoomHorizontal),
                       GridItem(zoomVertical)});

  grid.performLayout(getLocalBounds());
}



void ControlsPanelListener::setControlsPanelModel(std::shared_ptr<ControlsPanelModel> model)
{
    m_controlModel = model;     
}