#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
//AudioSynthWaveformBlSaw       waveform;      //xy=1624,808 //bandlimited Saw (works)
AudioSynthWaveformBlPulse       waveform;      //xy=1624,808 //bandlimited Pulse (doesn't work)
//AudioSynthWaveform       waveform;      //xy=1624,808 //teensy's waveform, not bandlimited
AudioOutputI2S           i2s1;           //xy=1841.9999999999995,809.9999999999998
AudioOutputUSB           usb1;           //xy=1855.9999999999995,879.9999999999998
AudioConnection          patchCord1(waveform, 0, i2s1, 0);
AudioConnection          patchCord2(waveform, 0, usb1, 0);
AudioConnection          patchCord3(waveform, 0, usb1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1764.9999999999986,999.9999999999992
// GUItool: end automatically generated code


void setup() {
  Serial.begin(9600);

  AudioMemory(80);

  sgtl5000_1.enable(); //starts sgtl5000

  //waveform.begin(0.5, 200, WAVEFORM_SAWTOOTH); // Teensy wave - not bandlimited
  //waveform.begin(0.5, 200); //bandlimited saw (amp, freq)
  waveform.begin(0.5, 200, 0.5); //bandlimited pulse (amp, freq, pwm)

}

void loop() {

  int potVal = analogRead(A0);
  int freq = map(potVal, 0, 1023, 80, 2000);

  waveform.frequency(freq);

 // Serial.println(freq);

}

