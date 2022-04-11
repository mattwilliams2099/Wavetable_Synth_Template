/*
  ==============================================================================

    Wavetable.cpp
    Created: 11 Apr 2022 11:34:43am
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Wavetable.h"

void WavetableSynth::prepareToPlay(double samplerate)
{
    this->sampleRate = samplerate;
    initialiseOscillators();
}

void WavetableSynth::initialiseOscillators()
{
    constexpr auto NUM_OSCILLATORS = 128;
    const auto wavetable = generateSineWavetable();
    oscillators.clear();
    for (auto i = 0; i < NUM_OSCILLATORS; i++)
    {
        oscillators.emplace_back(wavetable, sampleRate);
    }
}

std::vector<float> WavetableSynth::generateSineWavetable()
{
    constexpr auto WAVETABLE_LENGTH = 64;
    std::vector<float> sineWavetable (WAVETABLE_LENGTH);
    const auto PI = std::atanf(1.0f) * 4;
    for (auto i = 0; i < WAVETABLE_LENGTH; i++)
    {
        sineWavetable[i] = std::sinf(2.0f * PI * static_cast<float>(i) / static_cast<float>(WAVETABLE_LENGTH));
    }
    return sineWavetable;
}


void WavetableSynth::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto currentSample = 0;

    for (const auto midiMessage : midiMessages)
    {
        const auto midiEvent = midiMessage.getMessage();
        const auto midiEventSample = static_cast<int>(midiEvent.getTimeStamp());

        render(buffer, currentSample, midiEventSample);
        handleMidiEvent(midiEvent);

        currentSample = midiEventSample;
    }
    render(buffer, currentSample, buffer.getNumSamples());

}

void WavetableSynth::handleMidiEvent(const juce::MidiMessage& midiEvent) 
{
    if (midiEvent.isNoteOn())
    {
        const auto oscillatorId = midiEvent.getNoteNumber();
        const auto frequency = midiToHz(oscillatorId);
        oscillators[oscillatorId].setFrequency(frequency);
    }
    else if (midiEvent.isNoteOff())
    {
        const auto oscillatorId = midiEvent.getNoteNumber();
        oscillators[oscillatorId].stop();
    }
    else if (midiEvent.isAllNotesOff())
    {
        for (auto& oscillator : oscillators)
        {
            oscillator.stop();
        }

    }
}

float WavetableSynth::midiToHz(int midiNote)
{
    return 400.0f * std::powf(2.0f, (midiNote - 69.0f) / 12.0f);
}

void WavetableSynth::render(juce::AudioBuffer<float>& buffer, int startSample, int endSample)
{
    auto* firstChannel = buffer.getWritePointer(0);
    for (auto& oscillator : oscillators)
    {
        if (oscillator.isPlaying())
        {
            for (auto sample = startSample; sample < endSample; ++sample)
            {
                firstChannel[sample] += oscillator.getSample();
            }
        }
    }

    for (auto channel = 1; channel < buffer.getNumChannels(); channel++)
    {
        std::copy(firstChannel + startSample, firstChannel + endSample, buffer.getWritePointer(channel) + startSample);
    }
}
