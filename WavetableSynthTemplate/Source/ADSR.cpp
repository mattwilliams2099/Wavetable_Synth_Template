/*
  ==============================================================================

    ADSR.cpp
    Created: 12 Apr 2022 9:02:30am
    Author:  Matthew Williams

  ==============================================================================
*/

#include "ADSR.h"

float ADSR::getEnvelopeOutput()
{
    if (attackStage == true)
    {
        envelopeOutput += attackIncrement;
        if (envelopeOutput >= 1.0f)
        {
            attackStage = false;
            decayStage = true;
        }
    }
    else if (decayStage == true)
    {
        envelopeOutput -= decayIncrement;
        if (envelopeOutput = sustainLevel)
        {
            decayStage = false;
            sustainStage = true;
        }
    }
    else if (sustainStage == true)
        envelopeOutput = sustainLevel;
    else if (releaseStage == true)
    {
        envelopeOutput -= releaseIncrement;
        if (envelopeOutput = 0)
        {
            releaseStage = false;
        }
    }
        
        
    return envelopeOutput;
}

void ADSR::setAttackTime(float newValue)
{
    attackTime = millisecondsToSamples(newValue);
    attackIncrement = 1.0f / attackTime;
}

void ADSR::setDecayTime(float newValue)
{
    decayTime = millisecondsToSamples(newValue);
    decayIncrement = (1.0f - sustainLevel) / decayTime;
}

void ADSR::setSustainLevel(float newValue)
{
    sustainLevel = newValue;
}

void ADSR::setReleaseTime(float newValue)
{
    releaseTime = millisecondsToSamples(newValue);

}

float ADSR::millisecondsToSamples(float milliseconds)
{
    return (milliseconds / 1000) * sampleRate;
}
