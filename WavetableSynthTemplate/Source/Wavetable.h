/*
  ==============================================================================

    Wavetable.h
    Created: 11 Apr 2022 11:34:43am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Oscillator.h"
#include <vector>
#include <cmath>
class WavetableSynth
{
public:
    void prepareToPlay (double samplerate);
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&);


private:
    void handleMidiEvent (const juce::MidiMessage& midiEvent);
    float midiToHz (int midiNote);
    void initialiseOscillators();
    double sampleRate;
    std::vector<Oscillator> oscillators;
    std::vector<float> generateSineWavetable();
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);

};