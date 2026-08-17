#include <Arduino.h>

const short GREEN_LED_PIN = 23; 
const short RELAY_PIN = 21; 

void setup() {  
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);

}

/**
 * MODIFICAR EL SKECTCH PARA QUE INTEPRETE LOS COMANDO "ON" / "OF"
 */
void loop() {
 
  if (Serial.available() != 0) {
    //char car = Serial.read();
    String cmd = Serial.readStringUntil('\n');
    delay(10);
    Serial.print("Command received: ");
    Serial.println(cmd);
    cmd.trim();
    cmd.toUpperCase();
    bool state_led = digitalRead(GREEN_LED_PIN);

    if (cmd == "ON") {
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Sistema activado!");
    }
    else if (cmd == "OFF") {
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Sistema desactivado!");
    }
  }


}

