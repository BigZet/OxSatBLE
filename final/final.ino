#include <Arduino.h>
#include <heltec.h>
#include "uuids.h"
#include "display.h"
#include "connect.h"
#include "stateManager.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


Display display;
BLEConnector ble_connector;
StateManager stateManager;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/,
    false /*LoRa Disable*/,
    true /*Serial Enable*/,
    true /*PABOOST Enable*/);
  display = Display();
  ble_connector = BLEConnector();
  ble_connector.loadBLEDevice();
  stateManager = StateManager(&display, &ble_connector);
  analogSetCycles(8);                   // Set number of cycles per sample, default is 8 and provides an optimal result, range is 1 - 255
  analogSetSamples(1);                  // Set number of samples in the range, default is 1, it has an effect on sensitivity has been multiplied
  analogSetClockDiv(1);                 // Set the divider for the ADC clock, default is 1, range is 1 - 255
  analogSetAttenuation(ADC_11db);       // Sets the input attenuation for ALL ADC inputs, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
  analogSetPinAttenuation(36,ADC_11db); // Sets the input attenuation, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
  analogSetPinAttenuation(37,ADC_11db);
  adcAttachPin(37);
  adcStart(37);
  while(adcBusy(37));
  float voltageDivider = 338;
  int readValue = 0;
  int nbMeasurements = 10;
  for (int i = 0; i < nbMeasurements; i++) {
    readValue += analogRead(37);
    delay(100);
  }
  Serial.printf("Battery power in GPIO 37: ");
  Serial.println((readValue/nbMeasurements)/voltageDivider);
  adcEnd(37);
  
  
}

void loop() {
  stateManager.toMainState();
  stateManager.toMeasurementState();
  
}
