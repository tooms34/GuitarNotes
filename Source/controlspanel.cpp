#include "controlspanel.h"

ControlsPanel::ControlsPanel() : m_model(std::make_shared<ControlsPanelModel>())
{
  pauseButton = std::make_unique<TextButton>("Pause");
  pauseButton->setClickingTogglesState (true);
  addAndMakeVisible(*pauseButton);
  addAndMakeVisible(zoomHorizontal);
  addAndMakeVisible(zoomVertical);
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
  updateModel();
}

void ControlsPanel::updateModel()
{
  m_model->pauseOn = pauseButton->getToggleState();
  zoomHorizontal.setEnabled(m_model->pauseOn );
  zoomVertical.setEnabled(m_model->pauseOn );
  m_model->zoomHValue = zoomHorizontal.getValue();
  m_model->zoomVValue = zoomVertical.getValue();
}

void ControlsPanel::resized()
{
  juce::Grid grid;

  grid.rowGap = 5_px;
  grid.columnGap = 5_px;
  grid.templateColumns = {juce::Grid::TrackInfo(juce::Grid::Fr(20)),
  juce::Grid::TrackInfo(juce::Grid::Fr(40)),
  juce::Grid::TrackInfo(juce::Grid::Fr(40))
  };

  grid.templateRows = {juce::Grid::TrackInfo(juce::Grid::Fr(100))};

  grid.items.addArray({
    GridItem(*pauseButton),
      GridItem(zoomHorizontal),
      GridItem(zoomVertical)}
    );

  grid.performLayout(getLocalBounds());
}