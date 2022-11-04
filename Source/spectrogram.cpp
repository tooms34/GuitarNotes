#include "spectrogram.h"


void Spectrogram::setData(std::vector<float> &&data)
{
    m_data = std::move(data);
}

void Spectrogram::paint(juce::Graphics &g)
{
    g.fillAll(color);
    g.setColour(juce::Colours::red);
} 