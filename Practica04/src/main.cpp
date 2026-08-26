#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <DHT.h>

void updateOLED(float t, float h);

const short LED_PIN = 12;
const short DTH22_PIN = 23;

Adafruit_SH1106G display =  Adafruit_SH1106G(128, 64, &Wire, -1); // manejador del OLED(pantalla)
DHT sensor(DTH22_PIN, DHT22); // manejador del sensor

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT); //salida

    display.begin(0x3C, true);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
}

void loop() {
    float temp = sensor.readTemperature();
    float hum = sensor.readHumidity();
    updateOLED(temp, hum);

    //Mostrar en el display las lecturas
    if(temp >= 20)
        digitalWrite(LED_PIN, HIGH);
    else
       digitalWrite(LED_PIN, LOW);
    
    delay(100);
}


void updateOLED(float t, float h) {
  display.clearDisplay(); // Clear the display buffer
  display.setCursor(0, 0); // Set cursor to top-left corner
  display.printf("HUM: %.2f| TEMP:%.2f", h, t); // Print the potentiometer value to the display buffer  _display.display(); // Update the display with the buffer content
  display.display();
}