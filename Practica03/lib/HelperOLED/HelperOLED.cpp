#include "HelperOLED.h"

HelperOLED::HelperOLED(): _display(128, 64, &Wire, -1) {
    //inicializa tus atributos propios aquí si es necesario
}  

void HelperOLED::begin() {
    _display.begin(0x3C, true); // Initialize the display at I2C address 0x3C
    _display.clearDisplay(); // Clear the display buffer
    _display.setTextSize(1); // Set text size
    _display.setTextColor(SH110X_WHITE); // Set text color
}

// put function definitions here:
void HelperOLED::updateOLED(int valor) {
  _display.clearDisplay(); // Clear the display buffer
  _display.setCursor(0, 0); // Set cursor to top-left corner
  //display.println(txt); // Print the text to the display buffer
  float voltage = (valor / 4095.0) * 5.0; // Convert potentiometer value to voltage (assuming 3.3V reference)
  _display.printf("POTE: %d|Volt: %.2f", valor, voltage); // Print the potentiometer value to the display buffer  _display.display(); // Update the display with the buffer content
  _display.display();
}

void HelperOLED::updateOLEDString(String txt) {
  _display.clearDisplay(); // Clear the display buffer
  _display.setCursor(0, 0); // Set cursor to top-left corner
  _display.println(txt); // Print the text to the display buffer
  _display.display(); // Update the display with the buffer content
}