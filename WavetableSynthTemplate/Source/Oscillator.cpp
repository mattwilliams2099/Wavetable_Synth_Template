/*
  ==============================================================================

    Oscillator.cpp
    Created: 11 Apr 2022 12:12:29pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Oscillator.h"


Oscillator::Oscillator(std::vector<float> waveTable, double samplerate)
    : wavetable { std::move (waveTable) }, sampleRate {samplerate}
{
}

void Oscillator::setFrequency(float frequency)
{
    indexIncrement = frequency * static_cast<float>(wavetable.size()) / static_cast<float>(sampleRate);
}

float Oscillator::getSample()
{
    const auto sample = linearInterpolate();
    index += indexIncrement;
    index = std::fmod (index, static_cast<float>(wavetable.size()));
    return sample;
}

float Oscillator::linearInterpolate()
{
    const auto truncatedIndex = static_cast<int>(index);
    const auto nextIndex = (truncatedIndex + 1) % static_cast<int>(wavetable.size());
    const auto nextIndexWeight = index - static_cast<float>(truncatedIndex);
    const auto truncatedIndexWeight = 1.0f - nextIndexWeight;

    return truncatedIndexWeight * wavetable[truncatedIndex] + nextIndexWeight * wavetable[nextIndex];
}

void Oscillator::stop()
{
    index = 0.0f;
    indexIncrement = 0.0f;
}

bool Oscillator::isPlaying()
{
    return indexIncrement != 0.0f;
}