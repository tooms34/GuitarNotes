#include "spatialsoundviewer.h"
#include "SinWaveAudio.h"
#include "controlspanel.h"

SpatialSoundViewer::SpatialSoundViewer()
{
    // setBufferSize(1000);
}

void SpatialSoundViewer::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (m_state == State::Pause)
    {
        return;
    }
    auto sourceAudio = static_cast<SinWaveAudio *>(source);
    const auto sourceBuffer = sourceAudio->buffer();
    const auto startTargetSample = sampleBuffer.getNumSamples();
    sampleBuffer.setSize(sourceBuffer.getNumChannels(), sampleBuffer.getNumSamples() + sourceBuffer.getNumSamples(), true, false, true);
    for (auto chan = 0; chan < sampleBuffer.getNumChannels(); ++chan)
    {
        sampleBuffer.copyFrom(chan, startTargetSample, sourceBuffer, chan, 0, sourceBuffer.getNumSamples());
    }

    const auto leftX = std::max(int(sampleBuffer.getNumSamples()) - 512, 0);
    const auto rightX = sampleBuffer.getNumSamples();
    m_rectangleViewport = Rectangle<int>::leftTopRightBottom(leftX, MaxGlobalY, rightX, MinGlobalY);
    updateMatrix();
    repaint();
}

void SpatialSoundViewer::actionListenerCallback(const juce::String &message)
{
    if (message == "Pause")
    {
        m_state = (m_controlModel->pauseOn) ? State::Pause : State::Play;
    }
    else if (message == "ZoomH")
    {
        // std::cout << "----->" << m_controlModel->zoomHValue;
        const auto center = m_rectangleViewport.getCentreX();
        std::cout << "c->" << center << "  " << m_rectangleViewport.getX() << "  " << m_rectangleViewport.getRight() << std::endl;
        std::cout << m_rectangleViewport.getWidth() << "  " << sampleBuffer.getNumSamples() << std::endl;
        const auto width = int(float(sampleBuffer.getNumSamples()) / float(m_controlModel->zoomHValue));
        m_rectangleViewport.setLeft(std::max(0, center - width / 2));
        m_rectangleViewport.setRight(std::min(sampleBuffer.getNumSamples() , center + width / 2));
    }
    else if (message == "ZoomV")
    {
        const auto height = int(float(MaxGlobalY - MinGlobalY) / float(m_controlModel->zoomVValue));
        const auto center = m_rectangleViewport.getCentreY();
        m_rectangleViewport.setBottom(std::min(MaxGlobalY, center + height / 2));
        m_rectangleViewport.setTop(std::max(MinGlobalY, center - height / 2));        
    }
    updateMatrix();
    repaint();
}

void SpatialSoundViewer::paint(Graphics &g)
{
    g.fillAll(juce::Colours::white);

    // auto channelHeight = r.getHeight() / (float) 2.0;

    g.setColour(juce::Colours::red);

    auto area = getLocalBounds();

    // std::cout<<minAmp<< " "<<maxAmp<<std::endl;
    for (auto chan = 0; chan < sampleBuffer.getNumChannels(); ++chan)
    {

        const auto *data = sampleBuffer.getReadPointer(chan, 0);
        if (m_drawMode == DrawMode::Points)
        {

            for (size_t pos = area.getX(); pos <= area.getRight(); ++pos)
            {
                float posCoord[2] = {float(pos), 0};
                fromViewportToGlobalMatrix.transformPoint(posCoord[0], posCoord[1]);
                
                const int index=std::min(sampleBuffer.getNumSamples()-1,std::max(0,int(posCoord[0])));
             //  std::cout<<pos<<" "<<index<<std::endl;
                posCoord[1]=data[index];
                fromPhysicsToViewportMatrix.transformPoint(posCoord[0], posCoord[1]);
                
                g.drawEllipse(pos, int(posCoord[1]), 3, 3, 2);
            }
        }
        else
        {
            /*Path p = pathFromChannel(data, windowSize);
            // const float windowSize=m_rectangleViewport.getWidth();
            g.fillPath(p, fromPhysicsToViewportMatrix);*/
        }
    }
}

Path SpatialSoundViewer::pathFromChannel(const float *data, size_t size) const
{
    Path path;
    path.preallocateSpace(int(size));

    for (int i = 0; i < int(size); ++i)
    {
        if (i == 0)
            path.startNewSubPath(0.0f, (data[i]));
        else
            path.lineTo((float)i, (data[i]));
    }

    path.closeSubPath();
    return path;
}

void SpatialSoundViewer::setControlsPanelModel(std::shared_ptr<ControlsPanelModel> model)
{
    m_controlModel = model;
    updateMatrix();
}

void SpatialSoundViewer::mouseDown(const juce::MouseEvent &event)
{
    const auto mousePos = event.getPosition();
    Point<float> posCoord{float(mousePos.x), float(mousePos.y)};
    fromGlobalToViewportMatrix.inverted().transformPoint(posCoord.x, posCoord.y);
    m_rectanglePreviousPosition = posCoord;
}

void SpatialSoundViewer::mouseUp(const juce::MouseEvent &event)
{
}

void SpatialSoundViewer::mouseDrag(const juce::MouseEvent &e)
{
    if (e.mods.isRightButtonDown())
    {
        const auto mousePos = e.getPosition();
        Point<float> posCoord{float(mousePos.x), float(mousePos.y)};
        fromGlobalToViewportMatrix.inverted().transformPoint(posCoord.x, posCoord.y);
        const juce::Point<int> move{-int(posCoord.x - m_rectanglePreviousPosition.x), -int(posCoord.y - m_rectanglePreviousPosition.y)};
        int translateX = 0;
        if (sampleBuffer.getNumSamples() >= m_rectangleViewport.getRight() + move.x &&
            m_rectangleViewport.getX() >= -move.x)
        {
            translateX = move.x;
        }
        int translateY = 0;
        std::cout << move.y << std::endl;
        if ( m_rectangleViewport.getY() + move.y>=MinGlobalY &&
            MaxGlobalY >= m_rectangleViewport.getBottom() + move.y)
        {
            std::cout << m_rectangleViewport.getBottom() << " " << m_rectangleViewport.getY() << std::endl;
            translateY = move.y;
        }
        m_rectangleViewport.translate(translateX, translateY);
        m_rectanglePreviousPosition = posCoord;
        updateMatrix();
        repaint();
    }
    else if (e.mods.isLeftButtonDown())
    {
        const auto mousePos = e.getPosition();
        float posCoord[2] = {float(mousePos.x), float(mousePos.y)};
        fromGlobalToViewportMatrix.inverted().transformPoint(posCoord[0], posCoord[1]);
        std::cout << posCoord[0] << " " << posCoord[1] << std::endl;
    }
}

void SpatialSoundViewer::resized()
{
    updateMatrix();
}

void SpatialSoundViewer::updateMatrix()
{
    fromPhysicsToGlobalMatrix = AffineTransform::fromTargetPoints(0, 0.1, 0, MaxGlobalY,
                                                                  0, -0.1, 0, MinGlobalY,
                                                                  1, 0.1, 1, MaxGlobalY);
    if (!m_controlModel)
    {
        return;
    }

    auto area = getLocalBounds().toFloat();
    fromGlobalToViewportMatrix = AffineTransform::fromTargetPoints(m_rectangleViewport.getX(), m_rectangleViewport.getY(), area.getX(), area.getY(),
                                                                   m_rectangleViewport.getX(), m_rectangleViewport.getBottom(), area.getX(), area.getBottom(),
                                                                   m_rectangleViewport.getRight(), m_rectangleViewport.getY(), area.getRight(), area.getY());

    fromPhysicsToViewportMatrix = fromPhysicsToGlobalMatrix.followedBy(fromGlobalToViewportMatrix);
    fromViewportToGlobalMatrix=fromGlobalToViewportMatrix.inverted();
}