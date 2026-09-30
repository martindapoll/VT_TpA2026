#include <Arduino.h>
#include <UniversalTelegramBot.h>
#include <WifiClientSecure.h> //Permite crear un cliente seguro
#include <WiFi.h>

const char* BOT_TOKEN = "8638725405:AAHNDFZkm4ggwFRjS9KrBgehDdatR5K9z24";
WiFiClientSecure client;

UniversalTelegramBot bot(BOT_TOKEN, client);
const unsigned long TIEMPO_MIN = 1000;
const short PIN_RELAY = 26;
long time_ant = 0;

//Permite procesar los n mensajes del canal del BOT
void processMessages(int n){
    for (int i = 0; i < n; i++)
    {
      String chat_id = bot.messages[i].chat_id;
      String text = bot.messages[i].text;
      Serial.println("Comando recibido: " + text);
      
      if (text == "/start"){
        bot.sendMessage(chat_id, "Bienvenido\n");
        bot.sendMessage(chat_id, "Comando ON26: Enciende el RELAY\n");
        bot.sendMessage(chat_id, "Comando OFF26: Apaga el RELAY\n");
      }
      //procesar el texto como comando para la ESP32
      else if(text == "ON26"){
          digitalWrite(PIN_RELAY, HIGH);
          bot.sendMessage(chat_id, "Relay encendido!!!"); //responde texto
      }else if(text == "OFF26"){
          digitalWrite(PIN_RELAY, LOW);
          bot.sendMessage(chat_id, "Relay apagado!!!"); //responde texto
      }else{
         bot.sendMessage(chat_id, "Comando ignorado!!!"); //responde texto
      }
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(PIN_RELAY, OUTPUT);
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // necesita de un CERTIFICADO
    // Conectar a la red WiFi simulada de Wokwi
    WiFi.begin("Wokwi-GUEST", "");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }

}

void loop() {
   if(millis() - time_ant > TIEMPO_MIN){
      int n = bot.getUpdates(bot.last_message_received + 1);
      while(n){
        Serial.println("Comunicación desde el BOT");
        processMessages(n);
        n = bot.getUpdates(bot.last_message_received + 1);
      }
   }
}

