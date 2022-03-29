#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "888cd678-9b5b-4f8f-b972-028f5a74d798"
#define HEARTRATE_UUID "8154c981-fdc8-44a9-9ac3-1c74b1aa0121"
#define SATURATION_UUID "36b12a9f-02a0-4fb2-a46a-b8b7a17b26d4"


BLEServer* pServer = NULL;
BLEService* pService = NULL;
BLECharacteristic* pChar_HEARTRATE = NULL;
BLECharacteristic* pChar_SATURATION = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;


unsigned long startTime = 0;

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer){
    deviceConnected = true;
    BLEDevice::startAdvertising();
  };

  void onDisconnect(BLEServer* pServer){
    deviceConnected = false;
  }
};


void setup(){
  Serial.begin(115200);
  BLEDevice::init("Test ESP board");
  pServer = BLEDevice::createServer();
  pServer -> setCallbacks(new MyServerCallbacks());

  pService = pServer->createService(SERVICE_UUID);
  pChar_HEARTRATE = pService->createCharacteristic(
                      HEARTRATE_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pChar_SATURATION = pService->createCharacteristic(
                      SATURATION_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );   
  pChar_HEARTRATE->addDescriptor(new BLE2902());
  pChar_SATURATION->addDescriptor(new BLE2902()); 
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
  
}

void loop(){
  
  if (deviceConnected && (millis()-startTime>1000) ){
    pChar_HEARTRATE->setValue(value);
    pChar_HEARTRATE->notify();

    pChar_SATURATION->setValue(value);
    pChar_SATURATION->notify();
    value++;
    startTime = millis();
  }
  if (!deviceConnected && oldDeviceConnected) {
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("Client disconnected");
    oldDeviceConnected = deviceConnected;
  }
  if (deviceConnected && !oldDeviceConnected) {
    value = 0;
    Serial.println("Client connected");
    oldDeviceConnected = deviceConnected;
  }
  
}
