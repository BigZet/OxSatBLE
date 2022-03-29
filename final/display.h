#include <Arduino.h>
#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
  public:
    Display();
    void drawText(String text);
    void drawTextFlow(String text);
    void drawProgressBarD(int num);
    void drawSin();
    void drawMainUI(uint8_t battery, uint8_t pulse, uint8_t saturation,
    uint8_t lastTime, int clientsOnline);
    void drawMeasureUI(uint8_t rt_pulse, uint8_t rt_saturation,
    uint8_t progress, String controller_mode);
    void drawSlideLeft();
    void drawSlideRight();
    void clear();
};

#endif
