//
//  BLPulse.cpp
//  blJohn-
//
//  Created by Gustavo Silveira on 5/4/17.
//
//

#include "BLPulse.h"


void AudioSynthWaveformBlPulse::begin(float _amp, float _freq, float _pulseWidth) {
    sampleRate = AUDIO_SAMPLE_RATE_EXACT;
    //sampleRate = 44100;
    amp = _amp;
    freq = _freq;
    initialSaw.begin(_freq, amp);
    
    myDelayLine.setup(512, 0.01);
    
    setPulseWidth(_pulseWidth);    
    changePulseWidth();
    

}

float AudioSynthWaveformBlPulse::getSample() {
    
    float currentSample = initialSaw.getSample();
    myDelayLine.setSample(currentSample);
    float buffSample = myDelayLine.getSample();
//    
//    
    currentSample += (buffSample*-1);
    
//        return sample * amp - ( (pulseWidth - 0.5) * (amp * 2)) ; // The weird substraction is to center the signal around zero
    currentSample *= amp;
    int sample = (int)currentSample;
    return sample;
    //return currentSample;
}

void AudioSynthWaveformBlPulse::update() {
    
    
    audio_block_t *block;
    block = allocate();
    if (block == NULL) return;
    
    for (int i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
        int currentSample = 0;
        //changePulseWidth();
        currentSample = getSample();
        block->data[i] = currentSample;
    }
    transmit(block);
    release(block);
    
}

void AudioSynthWaveformBlPulse::frequency(float _freq) {
    initialSaw.frequency(_freq);
    freq = _freq;
    //calculateDelayInSamples();
    
    setPulseWidth(pulseWidth);
    changePulseWidth();
}

void AudioSynthWaveformBlPulse::amplitude(float _amp) {
    amp = _amp;
}

void AudioSynthWaveformBlPulse::changePulseWidth() {
    //pulseWidth = _pulseWidth;
    // set a delay here based on the pulse width
    delayTime = (1.0 / freq) * pulseWidth;
    myDelayLine.setDelayTime(delayTime);
    
    
}

void AudioSynthWaveformBlPulse::setPulseWidth(float _pulseWidth) {
    pulseWidth = _pulseWidth;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

