#pragma once

#include <JuceHeader.h>
#include "controlspanellistener.h"

#include "samplemodel.h"

struct ControlsPanelModel;
 


class SpatialSoundViewer : public juce::Component,
                           public SampleListener,
                           public ControlsPanelListener

{
    enum class State
    {
        Pause,
        Play
    };

    enum class DrawMode
    {
        Path,
        Points,
        Line
    };

public:
    SpatialSoundViewer();

    void setControlsPanelModel(std::shared_ptr<ControlsPanelModel> model)override;
    

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void actionListenerCallback(const String &message) override;

    void paint(Graphics &) override;

    Path pathFromChannel(const float *data, size_t size) const;

    void resized()override;
    
    void mouseDrag (const juce::MouseEvent& e)override;
    void mouseDown 	( 	const juce::MouseEvent &  	event	)override;
     void mouseUp 	( 	const juce::MouseEvent &  	event	)override;

private:

    std::pair<float,float> amplitudeMinMax()const;
    void updateMatrix();

    

private:
   
    State m_state{State::Play};
    DrawMode m_drawMode = DrawMode::Points;
    juce::Rectangle<int> m_rectangleViewport;
    juce::Point<float> m_rectanglePreviousPosition;
    //const std:pair<float,float> m_focusRectangleCenter;
    //const std::pair<float,float> 
    //std::pair<int, int> m_sampleRange = {0, 10239};
    //std::pair<float, float> m_amplitudeRange = {-1, 1};
     
    juce::AffineTransform fromPhysicsToGlobalMatrix;
    juce::AffineTransform fromGlobalToViewportMatrix;
    juce::AffineTransform fromPhysicsToViewportMatrix;  
     juce::AffineTransform fromViewportToGlobalMatrix;    

    const int MaxGlobalY=1000;
    const int MinGlobalY=-1000;
};