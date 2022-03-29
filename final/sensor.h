#include <Arduino.h>
#include <heltec>

#ifndef SENSOR_H
#define SENSOR_H

#define BUFFER_LENGTH 128

class SensorManager {
  public:
    int ledBrightness;
    int sampleAverage;
    int ledMode;
    int sampleRate;
    int pulseWidth;
    int adcRange;
    int lastHRate;
    int lastSPO2;
    int HRateBuffer[BUFFER_LENGTH];
    int SPO2Buffer[BUFFER_LENGTH];
    SensorManager(int ledBrightness, int sampleAverage, int ledMode, int sampleRate, int pulseWidth, int adcRange);
    void setConfig(int ledBrightness, int sampleAverage, int ledMode, int sampleRate, int pulseWidth, int adcRange);
    void init();
    void warming();
    int* measure(int durancy);
    void check();
    void fullCycle();
    int getLastHrate();
    int getLastSPO2();
    
};
#endif
