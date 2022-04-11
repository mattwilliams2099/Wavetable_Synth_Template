/*
  ==============================================================================

    Oscillator.h
    Created: 11 Apr 2022 12:12:29pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include <vector>
#include <cmath>

class Oscillator
{
private:
    std::vector<float> wavetable;
    double sampleRate;
    float index = 0.0f;
    float indexIncrement = 0.0f;
    float linearInterpolate();

public:
    Oscillator(std::vector<float> waveTable, double samplerate);
    void setFrequency(float frequency);
    float getSample();
    void stop();
    bool isPlaying();
};
