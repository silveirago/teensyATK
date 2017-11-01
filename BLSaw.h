//
//  BLSaw.h
//  
//
//  Created by John Thompson on 4/19/17.
//
//

#ifndef BLSaw_h
#define BLSaw_h

#include <stdio.h>
#include "AudioStream.h"

class AudioSynthWaveformBlSaw : public AudioStream {
    
public:
    AudioSynthWaveformBlSaw() : AudioStream(0, NULL){}
    void begin(float _freq, float _amp);
    virtual void update(void);
    float getSample();
    //void process();
    float getFreq();
    void frequency(float _freq);
    void amplitude (float _amp);
    
private:
    float sample;
    int sampleRate;
    float phase;
    float phaseInc;
    float freq;
    float currentSample;
    float amp;
    
    
};


#endif /* AudioSynthWaveformBlSaw */
