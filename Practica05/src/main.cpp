#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>

void updateOLED(float t, float h);

Adafruit_SH1106G display =  Adafruit_SH1106G(128, 64, &Wire, -1); // manejador del OLED(pantalla)

//pines: señal CkL = A, señal DT = B
const short LED = 23, PIN_A = 18, PIN_B = 5, PIN_SW = 19;

void setup() {
    Serial.begin(115200);

    //init display:
    display.begin(0x3C, true);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
}

void loop() {
    //Completar según enunciado práctica 07 del apunte  
    delay(100);
}


void updateOLED(float t, float h) {
  display.clearDisplay(); // Clear the display buffer
  display.setCursor(0, 0); // Set cursor to top-left corner
  display.printf("HUM: %.2f| TEMP:%.2f", h, t); // Print the potentiometer value to the display buffer  _display.display(); // Update the display with the buffer content
  display.display();
}