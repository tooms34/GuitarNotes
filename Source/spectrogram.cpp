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

SpatialSoundViewer::SpatialSoundViewer() : thumbnailCache(5), // [4]
                                           thumbnail(512, formatManager, thumbnailCache)
{
    ;
}

void SpatialSoundViewer::changeListenerCallback(juce::ChangeBroadcaster *source)
{

    //std::cout << "received" << std::endl;
    auto sourceAudio=static_cast<SinWaveAudio*>(source);
    thumbnail.reset(2,44100,sampleBuffer.getNumSamples());
    const auto& sampleBuffer{sourceAudio->buffer()};
    thumbnail.addBlock(sampleBuffer.getNumSamples(), sampleBuffer,0,sampleBuffer.getNumSamples());
    repaint();
}

void SpatialSoundViewer::paint(juce::Graphics &g) 
{
   // std::cout<<"paint"<<std::endl;
   if (thumbnail.getNumChannels() == 0)
    {
        ;
    }
    else
    {
        g.fillAll(juce::Colours::white);
        g.setColour(juce::Colours::red);
        thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
    }
}

/*   void SinWaveAudio::updateThumbnail()
{
  
}*/