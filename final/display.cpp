#include "display.h"
#include <heltec.h>

void Display::drawText(String text){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 10, text);
  Heltec.display->display();
}

void Display::drawTextFlow(String text){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
  Heltec.display->display();
}

void Display::drawProgressBarD(int num){
  
  int progress, progress2;
  for (int i = 0; i<=100; i++){
    progress = i % 100;
    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
    Heltec.display->drawString(64, 15, String(progress));
    Heltec.display->drawProgressBar(0, 48, 120, 5, progress);
    Heltec.display->display();
    delay(100);
  }
  
}

void Display::drawSin(){
  Heltec.display->clear();
  int progress = 0;
  int lastprogress = 0;
  int progress2 = 0;
  int lastprogress2 = 0;
  for (int i = 1; i<=128; i++){
    lastprogress = progress;
    lastprogress2 = progress2;
    progress = (int)(sin(0.0174533*i*32)*10);
    progress2 = (int)(cos(0.0174533*i*16)*10);
    Heltec.display->drawLine(i-1, lastprogress+10, i, progress+10);
    Heltec.display->drawLine(i-1, lastprogress2+30, i, progress2+30);
    Heltec.display->display();
    delay(10);
  }
}

void Display::drawMainUI(uint8_t battery, uint8_t pulse,
uint8_t saturation, uint8_t lastTime, int clientsOnline){
  Heltec.display->clear();
  int battery_progress = battery % 101;
  char HR_string[60];
  sprintf(HR_string, "%d bpm", pulse);
  char LASTTIME_string[60];
  sprintf(LASTTIME_string, "Last measure: %d sec ago", lastTime);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(2, 0, "iHeart");
  Heltec.display->drawString(0, 0, "i");
  Heltec.display->drawString(1, 0, "i");
  Heltec.display->drawString(0, 20, HR_string);
  Heltec.display->drawString(70, 20, String(saturation) + "%");
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 40, LASTTIME_string);
  Heltec.display->drawString(0, 50, "Connected clients: "+String(clientsOnline));
  
  Heltec.display->drawProgressBar(65, 5, 35, 7, battery_progress);
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 2, String(battery) + "%");
  Heltec.display->display();
  
}


void Display::drawMeasureUI(uint8_t rt_pulse, uint8_t rt_saturation,
uint8_t progress, String controller_mode){
  
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);

  int measure_progress = progress % 100;
  Heltec.display->drawProgressBar(14, 42, 100, 5, measure_progress);

  int progress_sin = (int)((sin(0.0174533*progress*20)+1)*6);
  Heltec.display->drawVerticalLine(measure_progress+14, progress_sin+20, 35-(progress_sin+20));
  
  Heltec.display->drawString(14, 50, "Measure mode: "+controller_mode);

  
  Heltec.display->display();
  
}

void Display::drawSlideLeft(){
  for (int i = 0; i<=127; i+=2){
    Heltec.display->fillRect(i, 0, 1, 64);
    Heltec.display->display();
    delay(2);
  }
  for (int i = 1; i<=127; i+=2){
    Heltec.display->fillRect(i, 0, 1, 64);
    Heltec.display->display();
  }
}

void Display::drawSlideRight(){
  for (int i = 127; i>=0; i-=2){
    Heltec.display->fillRect(i, 0, 1, 64);
    Heltec.display->display();
    delay(2);
  }
  for (int i = 126; i>=0; i-=2){
    Heltec.display->fillRect(i, 0, 1, 64);
    Heltec.display->display();
    delay(1);
  }
}

void Display::clear(){
  Heltec.display->clear();
}
Display::Display(){
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
}
