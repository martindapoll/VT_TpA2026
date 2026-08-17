#ifndef HelperOLED_h
#define HelperOLED_h

#include <Arduino.h>
#include<Adafruit_SH110X.h>
#include <Wire.h>

class HelperOLED {
  public:
    HelperOLED();
    void begin();
    void updateOLED(int valor);
    void updateOLEDString(String txt);
  private:
    Adafruit_SH1106G _display;
};  

#endif // HelperOLED_h