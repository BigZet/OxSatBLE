#include <Arduino.h>
#include <heltec>

#ifndef BATTERY_H
#define BATTERY_H

class BatteryManager {
  public:
    int GPIOVoltagePin;
    int analogCycles;
    int analogSamples;
    int analogClockDiv;
    float voltageDivider;
    int nbMeasurements;
    float lastVoltage;
    int full_battery_mah;
    int full_battery_voltage;
    BatteryManager(int iGPIOVoltagePin, int ianalogCycles, int ianalogSamples, int ianalogClockDiv, int ivoltageDivider, int inbMeasurements);
    void setConfig(int iGPIOVoltagePin, int ianalogCycles, int ianalogSamples, int ianalogClockDiv, int ivoltageDivider, int inbMeasurements);
    float measureVoltage(int inbMeasurements);
    float getBatteryProcent();
    void deepSleepCommand();
    void wakeUpCommand();
    
};
#endif
