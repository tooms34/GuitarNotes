#include "spectrogram.h"


Spectrogram::Spectrogram():  forwardFFT (10),  spectrogramImage (Image::RGB, 512, 512, true)
{
    m_fftData.resize(fftSize);
    
}

 Spectrogram::~Spectrogram(){
int x=2;
 }

void Spectrogram::paint(juce::Graphics &g)
{
    g.fillAll (Colours::black);

        g.setOpacity (1.0f);
        g.drawImage (spectrogramImage, getLocalBounds().toFloat());
}

void Spectrogram::changeListenerCallback(juce::ChangeBroadcaster *)
{
    
    const auto &inputData = sampleBuffer();
    if (size_t(inputData.getNumSamples()) < size_t(m_fftData.size()))
    {
        return;
    }
    const auto leftX =  int(inputData.getNumSamples()) - int(m_fftData.size());
    const auto chan = 0;
    const auto *dataInput = inputData.getReadPointer(chan, leftX);
    memcpy(m_fftData.data(), dataInput, sizeof(float) * m_fftData.size());
    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform(m_fftData.data());

    const auto border=4;
    const auto imageWidth = int(spectrogramImage.getWidth()-border);
    const auto imageHeight = int(spectrogramImage.getHeight()-border);

    // find the range of values produced, so we can scale our rendering to
    // show up the detail clearly    
    const auto minmaxLevel=FloatVectorOperations::findMinAndMax(m_fftData.data(), fftSize/2);

    auto fnAccum=[this,imageWidth](size_t fftDataSize,int xPos){
             size_t posXStart=size_t(float(fftDataSize)/float(imageWidth)*float(xPos));
            size_t posXEnd=size_t(float(fftDataSize)/float(imageWidth)*float(xPos+1));
            posXEnd=std::min(fftDataSize-1,posXEnd);
            float fAccum{0.0f};
           
            for(size_t x=posXStart;x<=posXEnd;++x){
                    jassert(x>=0 && x<fftSize);
                    fAccum+=m_fftData[x];
            }
            return fAccum/float(posXEnd-posXStart+1);
            
    };
     
    Graphics g (spectrogramImage);
    g.setColour(juce::Colours::red);
    for (auto x = border; x < imageWidth; ++x)
    {
        const float accumAmp=fnAccum(fftSize/2,x); 
        
        const int y= int(float(accumAmp-minmaxLevel.getStart())/float(minmaxLevel.getLength())*float(imageHeight));
        //std::cout<<x<<" "<<accumAmp<<" "<<y<<std::endl;
        jassert(imageHeight && y>=0);
        g.drawEllipse(float(x), float(std::min(border,int(imageHeight-y-1))), 3, 3, 2);
        
    }
    repaint();
}