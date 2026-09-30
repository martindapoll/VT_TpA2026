#include <Arduino.h>
#include<DHT.h>
#include<WiFi.h>
#include<ThingSpeak.h>

#define PIN_DHT 12
#define INTERVAL 1000
#define CHANNEL_ID 3516814

const char * API_KEY = "G504Q985XUC6NEKV";
WiFiClient client;
DHT sensor(PIN_DHT, DHT22);
long time_ant = 0;
void conectarWIFI();

void setup() {
  Serial.begin(115200);
  sensor.begin();
  conectarWIFI();
  ThingSpeak.begin(client);
}

void loop() {
  //Mínimo cada INTERVAL defido:
  if(millis()-time_ant >= INTERVAL){
    float t = sensor.readTemperature();
    float h = sensor.readHumidity();
    
    if(isnan(t) || isnan(h)){
      Serial.print("Error en la lectura del sensor DHT");
      return;
    }

    //Enviar datos al canal ThingSpeak:
    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    Serial.printf("Enviando datos | Temp: %.2f °C y Hum: %.2f %", t, h);
  
    ThingSpeak.writeFields(CHANNEL_ID, API_KEY);
    delay(1000);
  }
}


void conectarWIFI(){
    WiFi.begin("Wokwi-GUEST", "");
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }

    Serial.println("Conectado al WIFI!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

