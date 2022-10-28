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
                           public juce::ChangeListener,
                           public juce::ActionListener

{
 enum class State{
     Pause,
     Play
 };
public:
    SpatialSoundViewer();
        
    void changeListenerCallback(juce::ChangeBroadcaster *source) override; 
    void 	actionListenerCallback (const String &message) override;

    void 	paint (Graphics &) override;

    Path pathFromChannel (const float* data , size_t size)const;
 private:
    juce::AudioBuffer<float> sampleBuffer;
    State m_state{State::Play};
};