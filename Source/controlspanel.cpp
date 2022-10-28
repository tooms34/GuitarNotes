#include "controlspanel.h"

 

ControlsPanel::ControlsPanel()
{
  pauseButton=std::make_unique<TextButton>("Pause");
  addAndMakeVisible(*pauseButton);
  
  pauseButton->onClick = [this]
  { std::cout<<"pushed"; };

 
}

void ControlsPanel::resized()
{
  juce::Grid grid;

  grid.rowGap = 5_px;
  grid.columnGap = 5_px;
  grid.templateRows = {juce::Grid::TrackInfo(juce::Grid::Fr(100))};
                    
                      
  grid.templateColumns = {juce::Grid::TrackInfo(juce::Grid::Fr(50))};

  
  grid.items.addArray({GridItem(*pauseButton)});
                       
  grid.performLayout(getLocalBounds());
}