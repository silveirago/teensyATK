//
//  BLPulse.h
//  blJohn-
//
//  Created by Gustavo Silveira on 5/4/17.
//
//

#ifndef BLPulse_h
#define BLPulse_h

#include <stdio.h>
#include "AudioStream.h"
// #include "audioTools.h"
#include "BLSaw.h"
#include "delayLine.h"
//#include <math.h>


class AudioSynthWaveformBlPulse : public AudioStream {

public:
    AudioSynthWaveformBlPulse() : AudioStream(0, NULL){}
    void begin(float _amp, float _freq, float _pulse_width);
    void update();
    float getSample();
    void frequency(float _freq);
    void amplitude(float _amp);
    float getPulseWidth;
    void setPulseWidth(float _pulseWidth);
    void changePulseWidth();
    void calculateDelayInSamples();
    

private:

    float sampleRate;
    float delayTime;
    float pulseWidth;
    float amp;
    float freq;
   // int bufferPointer;
    AudioSynthWaveformBlSaw initialSaw;
    delayLine myDelayLine;
    //void updatePointers(); //***


    
};


#endif /* BLPulse_h */
