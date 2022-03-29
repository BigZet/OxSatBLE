#include <Arduino.h>
#include "display.h"
#include "connect.h"
#include "stateManager.h"

void StateManager::loadMainWindow(){
  
  
  Serial.println("Load Main Window");
  int battery = 0;
  for (int i = 1; i<=100; i+=1){
    battery += 1;
    uint8_t hrate = random(90, 150);
    display->drawMainUI(battery, hrate, random(70, 97), i%10, ble_connector->countClients());
    ble_connector->setHeartRate(hrate);
    delay(100);
  }
}

void StateManager::loadMeasurementWindow(){
  Serial.println("Load Measurement Window");
  display->clear();
  for (int i = 1; i<=100; i+=1){
    display->drawMeasureUI(0, 0, i, "active");
    delay(50);
  }
}

void StateManager::toMainState(){
  current_state = MAIN_WINDOW;
  display->drawSlideRight();
  init();
}

void StateManager::toMeasurementState(){
  current_state = MEASUREMENT_WINDOW;
  display->drawSlideLeft();
  init();
}



void StateManager::init(){
  if (current_state == INIT){
    Serial.println("INIT STATE");
  }
  if (current_state == MAIN_WINDOW){
    Serial.println("MAIN STATE");
    loadMainWindow();
  }
  if (current_state == MEASUREMENT_WINDOW){
    Serial.println("MEASUREMENT STATE");
    loadMeasurementWindow();
  }
  
  
}
