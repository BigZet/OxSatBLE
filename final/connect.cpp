#include <Arduino.h>
#include <heltec.h>
#include "uuids.h"
#include "connect.h"
#include <BLE2902.h>

BLEConnector::BLEConnector(){}

boolean BLEConnector::loadBLEDevice(){
    BLEDevice::init("HeartRate Sensor");
    pServer = BLEDevice::createServer();
    pService = pServer->createService(SERVICE_UUID);
    pCharHEARTRATE = pService->createCharacteristic(
                                        HEARTRATE_UUID,
                                        BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE |
                                        BLECharacteristic::PROPERTY_NOTIFY |
                                        BLECharacteristic::PROPERTY_INDICATE);
                                         
    pCharSPO2 = pService->createCharacteristic(
                                        SPO2_UUID,
                                        BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE);

    pCharBATTERY = pService->createCharacteristic(
                                        BATTERY_UUID,
                                        BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE);
    pCharHEARTRATE->addDescriptor(new BLE2902());
    pCharHEARTRATE->setValue(default_value, 1);
    pCharSPO2->setValue(default_value, 1);
    pCharBATTERY->setValue(default_value, 1);
    pService->start();

    pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    return true;
}

uint32_t BLEConnector::countClients(){
  return pServer->getConnectedCount();
}


void BLEConnector::setHeartRate(uint8_t hrate){
  uint8_t set_value[1] = {hrate};
  pCharHEARTRATE->setValue(set_value, 1);
  pCharHEARTRATE->notify();
}
