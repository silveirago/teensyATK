//
//  delayLine.cpp
//  blJohn
//
//  Created by Gustavo Silveira on 5/4/17.
//
//

#include "delayLine.h"

void delayLine::setup(int _length, float delayTime) {
    
    sampleRate = AUDIO_SAMPLE_RATE_EXACT;
    //sampleRate = 44100;
    length = _length;
    //buffer = (float *)malloc(sizeof(float)*length);
    
    for(int bufferIndex = 0; bufferIndex<length; bufferIndex++) {
        buffer[bufferIndex] = (0);
    }
    writePointer = 0;
     setDelayTime(delayTime);
     //delete buffer;
    
}

//void delayLine::updatePointers() {
//    writePointer++;
//    readPointer++;
//    
//    if(readPointer >= length-1) { readPointer -= length; }
//    if(writePointer >= length-1) { writePointer -= length; }
//}

float delayLine::getSample() {
    int sampleBefore = (int)readPointer;
    int sampleAfter = (sampleBefore + 1)%length;
    float fractionalAmount = readPointer - (float) sampleBefore;
    float interpolatedSample = ((1.0 - fractionalAmount) * (float)buffer[sampleBefore]) + (fractionalAmount * (float)buffer[sampleAfter]);
     //setSample(interpolatedSample);
    //updatePointers();
    readPointer++;
    if(readPointer >= length-1) { readPointer -= length; }
    if(writePointer >= length-1) { writePointer -= length; }
    
    return interpolatedSample;
    
}

void delayLine::setSample(int sample) {
    buffer[writePointer] = sample;
    //updatePointers();
    writePointer++;
    
    if(readPointer >= length-1) { readPointer -= length; }
    if(writePointer >= length-1) { writePointer -= length; }
}

void delayLine::setDelayTime(float delayTime)
{
    float delayTimeInSamples = delayTime * sampleRate;
    readPointer = (float) writePointer - delayTimeInSamples;
    while(readPointer < 0) {
        readPointer += (float) length;
    }
}

//
//void delayLine::update() {
//    
//    audio_block_t *block;
//    block = allocate();
//    if (block == NULL) return;
//    
//    for (int i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
//        int currentSample = 0;
//        currentSample = getSample();
//        block->data[i] = currentSample;
//    }
//    transmit(block);
//    release(block);
//}
//
