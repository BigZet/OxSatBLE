#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#ifndef CONNECTOR_H
#define CONNECTOR_H

class BLEConnector {
  public:
    BLEServer *pServer;
    BLEService *pService;
    BLECharacteristic *pCharHEARTRATE;
                                         
    BLECharacteristic *pCharSPO2;

    BLECharacteristic *pCharBATTERY;
    BLEAdvertising *pAdvertising;
    uint8_t default_value[1] = {69};
    BLEConnector();
    boolean loadBLEDevice();
    uint32_t countClients();
    void setHeartRate(uint8_t hrate);
    void setSaturation();
    void setBattery();
};
#endif
