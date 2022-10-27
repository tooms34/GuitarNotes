#pragma once

#include <JuceHeader.h>

class Spectrogram : public juce::Component
{
public:
    Spectrogram() = default;
    void setData(std::vector<float> &&data);
    void paint(juce::Graphics &g) override;

    juce::Colour color;

private:
    std::vector<float> m_data;
};

class SpatialSoundViewer : public juce::Component,
                           public juce::ChangeListener
{
public:
    SpatialSoundViewer();
    void paint(juce::Graphics &g) override;
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    juce::AudioThumbnail thumbnail;
    juce::AudioThumbnailCache thumbnailCache;
    juce::AudioFormatManager formatManager;
};