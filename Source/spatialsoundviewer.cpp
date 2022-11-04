#include "spatialsoundviewer.h"
#include "SinWaveAudio.h"
#include "controlspanel.h"

 
SpatialSoundViewer::SpatialSoundViewer()
{
       //setBufferSize(1000);
}

void SpatialSoundViewer::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (m_state==State::Pause){
        return;
    }
    auto sourceAudio = static_cast<SinWaveAudio *>(source);
    const auto sourceBuffer = sourceAudio->buffer();           
    const auto startTargetSample=sampleBuffer.getNumSamples();
    sampleBuffer.setSize(sourceBuffer.getNumChannels(),sampleBuffer.getNumSamples()+sourceBuffer.getNumSamples(),true,false,true);
    for (auto chan = 0; chan < sampleBuffer.getNumChannels(); ++chan)
    {
        sampleBuffer.copyFrom(chan, startTargetSample, sourceBuffer,chan,0, sourceBuffer.getNumSamples());        
    }
    
    const auto leftX = std::max(int(sampleBuffer.getNumSamples())-10240,0);
    const auto rightX = sampleBuffer.getNumSamples() ;
    m_rectangleViewport = Rectangle<int>::leftTopRightBottom(leftX, MaxGlobalY,rightX, MinGlobalY);
    updateMatrix();
    repaint();
}

void SpatialSoundViewer::actionListenerCallback(const juce::String &message)
{
    if (message == "Pause")
    {
        m_state = (m_controlModel->pauseOn) ? State::Pause: State::Play;
    }
    else if (message == "ZoomH")
    {
       // std::cout << "----->" << m_controlModel->zoomHValue;
       const auto center = m_rectangleViewport.getCentreX();
       std::cout<<"c->"<<center<<"  "<<m_rectangleViewport.getX()<<"  "<<m_rectangleViewport.getRight()<<std::endl;
       std::cout<<m_rectangleViewport.getWidth()<<"  "<<sampleBuffer.getNumSamples()<<std::endl;
       const auto width = int(float(sampleBuffer.getNumSamples()) / float(m_controlModel->zoomHValue)) ;
       m_rectangleViewport.setLeft(std::max(0,center-width/2));
       m_rectangleViewport.setRight(m_rectangleViewport.getX()+width);
       

    }
    else if (message == "ZoomV")
    {
      
    }
    updateMatrix();
    repaint();
}


 std::pair<float,float> SpatialSoundViewer::amplitudeMinMax()const{
                                              
        return {float(m_rectangleViewport.getBottom())/float(m_controlModel->zoomVValue*10'000),float(m_rectangleViewport.getY())/float(m_controlModel->zoomVValue*10'000)};
    }

 

    void SpatialSoundViewer::paint(Graphics &g)
    {
        g.fillAll(juce::Colours::white);

    
        // auto channelHeight = r.getHeight() / (float) 2.0;

        g.setColour(juce::Colours::red);

        const size_t windowSize = size_t(m_rectangleViewport.getWidth());

       
        // std::cout<<minAmp<< " "<<maxAmp<<std::endl;
        for (auto chan = 0; chan < sampleBuffer.getNumChannels(); ++chan)
        {

            const auto *data = sampleBuffer.getReadPointer(chan, m_rectangleViewport.getX());
            if (m_drawMode == DrawMode::Points)
            {
            
                
                for (size_t pos = 0; pos < windowSize; ++pos)
                {
                    float posCoord[2] = {float(pos), float(data[pos])};
                    fromPhysicsToViewportMatrix.transformPoint(posCoord[0], posCoord[1]);
                    //std::cout<<pos<<" "<<posCoord[0]<<" "<<posCoord[0]-old<<std::endl;
                   // old=posCoord[0];
                    g.drawEllipse(posCoord[0], posCoord[1], 3, 3, 2);
                }
            }
            else
            {
                Path p = pathFromChannel(data, windowSize);
                // const float windowSize=m_rectangleViewport.getWidth();
                g.fillPath(p, fromPhysicsToViewportMatrix);
            }
        }
    }

Path SpatialSoundViewer::pathFromChannel (const float* data , size_t size)const
 {
     Path path;
    path.preallocateSpace (int(size));

    for (int i = 0; i < int(size); ++i)
    {        
        if (i == 0)
            path.startNewSubPath (0.0f, (data[i]));
        else
            path.lineTo ((float) i, (data[i]));
    }

    
    path.closeSubPath();
    return path;
}

void SpatialSoundViewer::setControlsPanelModel(std::shared_ptr<ControlsPanelModel> model){
    m_controlModel=model;
    updateMatrix();
}


void SpatialSoundViewer::mouseDown 	( 	const juce::MouseEvent &  	event	) 
    {
          const auto mousePos = event.getPosition();           
            Point<float> posCoord{float(mousePos.x), float(mousePos.y)};
            fromGlobalToViewportMatrix.inverted().transformPoint(posCoord.x, posCoord.y);         
        m_rectanglePreviousPosition=posCoord;
    }

    void SpatialSoundViewer::mouseUp	( 	const juce::MouseEvent &  	event	) 
    {

    }

    
void SpatialSoundViewer::mouseDrag (const juce::MouseEvent& e) 
    {
        if (e.mods.isRightButtonDown())
        {
            const auto mousePos = e.getPosition();           
            Point<float> posCoord{float(mousePos.x), float(mousePos.y)};
            fromGlobalToViewportMatrix.inverted().transformPoint(posCoord.x, posCoord.y);           
            const juce::Point<int> move{-int(posCoord.x-m_rectanglePreviousPosition.x),-int(posCoord.y-m_rectanglePreviousPosition.y)};
            int translateX=0;
            if (sampleBuffer.getNumSamples()>=m_rectangleViewport.getRight()+move.x && 
            m_rectangleViewport.getX()>=-move.x)
            {
                translateX=move.x;
            }
            int translateY=0;
            std::cout<<move.y<<std::endl;
            if (-1000<m_rectangleViewport.getBottom()+move.y && 
            1000>m_rectangleViewport.getY()+move.y)
            {
                 std::cout<<m_rectangleViewport.getBottom()<<" "<<m_rectangleViewport.getY()<<std::endl;
                translateY=move.y;
            }
            m_rectangleViewport.translate(translateX,translateY);
            m_rectanglePreviousPosition=posCoord;
            updateMatrix();
            repaint();

        }
        else if(e.mods.isLeftButtonDown())
        {
            const auto mousePos = e.getPosition();
            float posCoord[2] = {float(mousePos.x), float(mousePos.y)};
            fromGlobalToViewportMatrix.inverted().transformPoint(posCoord[0], posCoord[1]);
            std::cout << posCoord[0] << " " << posCoord[1] << std::endl;
        }
    }


 void SpatialSoundViewer::resized(){
     updateMatrix();  
 }

 void SpatialSoundViewer::updateMatrix()
 {
     fromPhysicsToGlobalMatrix=AffineTransform::fromTargetPoints(0, 0.1, 0, MaxGlobalY,
                                                0, -0.1, 0, MinGlobalY,
                                                1, 0.1, 1, MaxGlobalY);
     if (!m_controlModel)
     {
         return;
     }
     const auto [minAmp, maxAmp] = amplitudeMinMax();
     auto area = getLocalBounds().toFloat();
     fromGlobalToViewportMatrix = AffineTransform::fromTargetPoints(0, MaxGlobalY, area.getX(), area.getY(),
                                                0, MinGlobalY, area.getX(), area.getBottom(),
                                                float(m_rectangleViewport.getWidth()), MaxGlobalY, area.getRight(), area.getY());

    fromPhysicsToViewportMatrix=fromPhysicsToGlobalMatrix.followedBy(fromGlobalToViewportMatrix);
 }