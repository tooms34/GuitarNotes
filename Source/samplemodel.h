#pragma once

#include <JuceHeader.h>

class SampleModel : public juce::ChangeListener, public juce::ChangeBroadcaster, private Timer
{
public:
    SampleModel();
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    const juce::AudioBuffer<float> &sampleBuffer() const
    {
        return m_sampleBuffer;
    }
    void timerCallback() override;

void clear();

private:
    juce::AudioBuffer<float> m_sampleBuffer;
    bool m_dataChanged = false;
};

class SampleListener : public juce::ChangeListener
{
public:
    void setModel(std::shared_ptr<SampleModel> model) { m_model = model; }

    const juce::AudioBuffer<float>& sampleBuffer()const{
        return m_model->sampleBuffer();
    }

protected:
    std::shared_ptr<SampleModel> m_model;
};