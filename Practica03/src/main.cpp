//libraries:
#include "HelperOLED.h"

//variables globales:
const short LED_PIN = 2; // Pin for the LED
const short POTE = 32;
HelperOLED oled; 

// Create an instance of the HelperOLED class
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POTE, INPUT);
  
   // Initialize the OLED display
   oled.begin();
  
  // Display a startup message on the OLED 
  oled.updateOLEDString("START");
  delay(1000); // Wait for 1 second for the message to be visible
}

void loop() {
    int potValue = analogRead(POTE); // Read the potentiometer value
    analogWrite(LED_PIN, potValue / 4); // Map the potentiometer value (0-4095) to PWM range (0-1023) and write to the LED
    oled.updateOLED(potValue); // Update the OLED display with the potentiometer value
    delay(1000); // Delay for 1 second
}
