#pragma once

#include <JuceHeader.h>

#include <shared_mutex>
#include "controlspanellistener.h"


class SampleModel : public juce::ChangeListener, public juce::ChangeBroadcaster, private Timer
{
public:
    SampleModel();
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    juce::AudioBuffer<float> sampleBuffer() const;
   
    void timerCallback() override;

    void clear();

private:
    juce::AudioBuffer<float> m_sampleBuffer;
    bool m_dataChanged = false;
    mutable std::shared_mutex mutex;
};

class SampleListener : public juce::ChangeListener
{
public:
    void setModel(std::shared_ptr<SampleModel> model) { m_model = model; }

    const juce::AudioBuffer<float> sampleBuffer() const
    {
        return m_model->sampleBuffer();
    }

protected:
    std::shared_ptr<SampleModel> m_model;
 
};


class SampleModelHandler : public ControlsPanelListener,public SampleListener{
public:
   void actionListenerCallback(const String &message) override;
   void changeListenerCallback(juce::ChangeBroadcaster *)override{;}

};
