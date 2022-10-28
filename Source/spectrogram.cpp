#include "spectrogram.h"
#include "SinWaveAudio.h"

void Spectrogram::setData(std::vector<float> &&data)
{
    m_data = std::move(data);
}

void Spectrogram::paint(juce::Graphics &g)
{
    g.fillAll(color);
    g.setColour(juce::Colours::red);
}

SpatialSoundViewer::SpatialSoundViewer()
{
       //setBufferSize(1000);
}

void SpatialSoundViewer::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    auto sourceAudio = static_cast<SinWaveAudio *>(source);
    const auto sourceBuffer = sourceAudio->buffer();           
    const auto startTargetSample=sampleBuffer.getNumSamples();
    sampleBuffer.setSize(sourceBuffer.getNumChannels(),sampleBuffer.getNumSamples()+sourceBuffer.getNumSamples(),true,false,true);
    for (auto chan = 0; chan < sampleBuffer.getNumChannels(); ++chan)
    {
        sampleBuffer.copyFrom(chan, startTargetSample, sourceBuffer,chan,0, sourceBuffer.getNumSamples());        
    }
    
    repaint();
}

void SpatialSoundViewer::paint(Graphics &g)
{
    g.fillAll(juce::Colours::white);

    auto area = getLocalBounds().toFloat();
    // auto channelHeight = r.getHeight() / (float) 2.0;

 
    g.setColour(juce::Colours::red);
    const int windowSize = 1024;
    for (auto chan = 0; chan < sampleBuffer.getNumChannels(); ++chan)
    {

        const int index = std::max(int(sampleBuffer.getNumSamples())-windowSize,0);
        
        const auto *data = sampleBuffer.getReadPointer(chan, index);
        Path p = pathFromChannel(data, sampleBuffer.getNumSamples() - index);
     
        g.fillPath(p, AffineTransform::fromTargetPoints(0.0f, -1.0f, area.getX(), area.getY(),
                                                        0.0f, 1.0f, area.getX(), area.getBottom(),
                                                        (float)windowSize, -1.0f, area.getRight(), area.getY()));
    }
}

Path SpatialSoundViewer::pathFromChannel (const float* data , size_t size)const
 {
     Path path;
    path.preallocateSpace (size);

    for (int i = 0; i < size; ++i)
    {        
        if (i == 0)
            path.startNewSubPath (0.0f, data[i]);
        else
            path.lineTo ((float) i, data[i]);
    }

    
    path.closeSubPath();
    return path;
}