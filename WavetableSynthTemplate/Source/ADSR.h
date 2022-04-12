/*
  ==============================================================================

    ADSR.h
    Created: 12 Apr 2022 9:02:30am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include <vector>

class ADSR
{
private:
    std::vector<float> envelope;
    float attackTime;
    float decayTime;
    float sustainLevel;
    float releaseTime;

    float attackIncrement;
    float decayIncrement;
    float releaseIncrement;
    
    float millisecondsToSamples(float milliseconds);

    float envelopeOutput = 0.0f;

    bool attackStage = 0;
    bool decayStage = 0;
    bool sustainStage = 0;
    bool releaseStage = 0;

    float sampleRate = 44100.0f;
public:
    float getEnvelopeOutput();
    
    void setAttackTime(float newValue);
    void setDecayTime(float newValue);
    void setSustainLevel(float newValue);
    void setReleaseTime(float newValue);
    
    void keyDown() { attackStage = true; }
    void keyRelease() 
    {

        attackStage = false;
        decayStage = false;
        sustainStage = false;
        releaseStage = true;
    }

};