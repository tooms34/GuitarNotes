#include "audioprovider.h"
#include "SinWaveAudio.h"
 
AudioProvider::AudioProvider()
{
    sinWave = std::make_unique<SinWaveAudio>();
    juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                      [this](bool granted)
                                      {
                                          int numInputChannels = granted ? 2 : 0;
                                          audioDeviceManager.initialise(0, 2, nullptr, true, {}, nullptr);
                                      });
    audioSourcePlayer.setSource(sinWave.get());
    audioDeviceManager.addAudioCallback(&audioSourcePlayer);

    // audioSourcePlayer.setSource(&transportSource);
}

AudioProvider::~AudioProvider()
{
    audioSourcePlayer.setSource(nullptr);

    audioDeviceManager.removeAudioCallback(&audioSourcePlayer);
}
 