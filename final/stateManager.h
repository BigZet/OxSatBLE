#include <Arduino.h>
#include "display.h"
#include "connect.h"
#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

class StateManager {
  enum State
  {
    INIT,
    MAIN_WINDOW,
    MEASUREMENT_WINDOW,
    EXIT,
  };
  public:
    Display* display;
    BLEConnector* ble_connector;
    StateManager(){};//Странный костыль, я хз почему в C++ при объявлении переменной класса, происходит ее инициализация и вызов этого конструктора... C++ пощади...
    StateManager(Display* disp, BLEConnector* ble_conn){
      display = disp;
      ble_connector = ble_conn;
      Serial.println(ble_connector -> countClients());
    };
    State current_state = INIT;
    int getCurrentState();
    void init();
    void loadMainWindow();
    void loadMeasurementWindow();
    void toMainState();
    void toMeasurementState();
};
#endif
