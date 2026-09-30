#include <Arduino.h>
// Load Wi-Fi library
#include <WiFi.h>
#include <PubSubClient.h>
void callback(char* topic, byte * message, unsigned int length);

// Replace with your network credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverMQTT = "test.mosquitto.org";
const short puertoMQTT = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 1000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  client.setServer(serverMQTT, puertoMQTT);
  client.setCallback(callback);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    String clientId = "ESP32Client-" + String(WiFi.macAddress());
    if (client.connect(clientId.c_str())) {
      Serial.println("connected to Mosquitto!");
      client.subscribe("test/command"); // suscribo al topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte * message, unsigned int length){
    String cmd = "";
    int i;
    for(i=0; i< length; i++){
        cmd += (char)message[i];
    }
    cmd.trim();
    //Procesar el cmd:
    Serial.println("In: " + cmd);
    if (cmd == "ON26") {
      digitalWrite(output26, HIGH);
      Serial.println("-> Ejecutado: output26 HIGH");
    } else if (cmd == "OFF26") {
      digitalWrite(output26, LOW);
      Serial.println("-> Ejecutado: output26 LOW");
    } else if (cmd == "ON27") {
      digitalWrite(output27, HIGH);
      Serial.println("-> Ejecutado: output27 HIGH");
    } else if (cmd == "OFF27") {
      digitalWrite(output27, LOW);
      Serial.println("-> Ejecutado: output27 LOW");
    }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Mantiene viva la conexión y procesa mensajes
}