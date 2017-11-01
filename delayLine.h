//
//  delayLine.hpp
//  blJohn
//
//  Created by Gustavo Silveira on 5/4/17.
//
//

#ifndef delayLine_h
#define delayLine_h

#include <stdio.h>
#include "AudioStream.h"


class delayLine {
public:
    delayLine() {};
    //~delayLine() {};
    float delayTime; // in seconds
    void setup(int _length, float delayTime);
    float getSample();
    void setSample(int sample);
    void updatePointers();
    void setDelayTime(float delayTime);
    //void update();
    
        
private:
    int writePointer;
    float readPointer;
    // vector<float> buffer;
    float buffer[512];
    int length = 0.01;
    //uint16_t bufferIndex;
    float sampleRate;
};



#endif /* delayLine_h */
