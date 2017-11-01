//
//  BLSaw.cpp
//  
//
//  Created by John Thompson on 4/19/17.
//
//

#include "BLSaw.h"

void AudioSynthWaveformBlSaw::begin(float _amp, float _freq) {
    
    freq = _freq;
    amp = _amp;
    phase = 0;
    sampleRate = AUDIO_SAMPLE_RATE_EXACT;
    
}

float AudioSynthWaveformBlSaw::getSample() {
    

    phaseInc = freq / AUDIO_SAMPLE_RATE_EXACT; //put this in the seFreq function
    phase += phaseInc;
    
    if(phase > 1) {
        phase -= 1;
    }
    
    
    float T0 = phaseInc;
    float P0 = sampleRate / freq;
    
    float h = 1; // what is h? the gradient?
    float T2 = T0+T0; // double the phaseIncrement
    float T3 = T2+T0; // triple the phaseIncrement
    float cdc = T3;
    float DC = 1 + cdc;
    
    //# -- coefficients (13 operations)
    
    float a31 = -h/3.;
    float a11 = T2;					//# a
    float a01 = 2 * h - DC;			//# maaa		# a
    float a32 = 2 * h / 3.;			//# m
    float a22 = -3 * h;				//# m
    float a12 = T2 - a22;			//# a			# a
    float a02 = h - DC;			//# a			# a
    float a33 = a31;
    float a23 = -a22;				//# a
    float a13 = T2 - 9*h;			//# am			# a
    float a03 = 9*h - DC;			//# a
    
    
    if (phase >= T3){
        //# outside
        currentSample = 2*phase - DC;								//# MA
        
    }else if(phase >= T2){
        //# inside
        float D = phase * P0;										//# M
        currentSample = ((a33*D + a23)*D + a13)*D + a03;		//# MAMAMA
        
    }else if(phase >= T0){
        //# inside
        float D = phase * P0;										//# M
        currentSample = ((a32*D + a22)*D + a12)*D + a02;		//# MAMAMA
        
    }else{
        //# inside
        float D = phase * P0;										//# M
        currentSample = (a31*D*D + a11)*D + a01;				//# MMAMA
    }
    
    // std::cout << currentSample << std::endl;
    currentSample =  (currentSample * amp) * 32767;
    sample = (int) currentSample;
    
    
    return sample;
    
}

//float AudioSynthWaveformBlSaw::getSample() {
//    
//    return sample;
//
//}

void AudioSynthWaveformBlSaw::update(void) {
    
    audio_block_t *block;
    block = allocate();
    if (block == NULL) return;
    
    for (int i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
        //AUDIO_BLOCK_SAMPLES
        int currentSample = 0;
        currentSample = getSample();
        block->data[i] = currentSample;
    }
    transmit(block, 0);
    release(block);
}

void AudioSynthWaveformBlSaw::frequency(float _freq) {
    
    freq = _freq;
}

void AudioSynthWaveformBlSaw::amplitude (float _amp) {
     amp = _amp;
}

float AudioSynthWaveformBlSaw::getFreq() {
    return freq;
}
