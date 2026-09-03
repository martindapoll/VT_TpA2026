#include <Arduino.h>
#include <WiFi.h>

void enviarRespuesta(WiFiClient client, String state);

const char *SSID = "Wokwi-GUEST";
const char *PASS = "";
const short PIN_LED = 26;
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWIFI Conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (client) // Conexión HTTP entrante
  {
    Serial.println("Cliente HTTP conectado...");
    String header = "";
    String currentLine = "";

    while (client.connected())
    {
      if (client.available()) //IDEM que en la conexión serial
      {
        char c = client.read();
        header += c;

        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            // Respuesta según la URL
            if (header.indexOf("GET /api/LedON") >= 0)
            {
              digitalWrite(PIN_LED, HIGH);
              enviarRespuesta(client, "1");
            }
            else if (header.indexOf("GET /api/LedOFF") >= 0)
            {
              digitalWrite(PIN_LED, LOW);
              enviarRespuesta(client, "0");
            }
            else
            {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html; charset=utf-8");
              client.println("Connection: close");
              client.println();
              //enviar página HTML:
              client.println(R"(<!DOCTYPE html>
              <html lang="es">
              <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>ESP32 Servidor Web</title>
              </head>
              <body>
                <h1>Control de LED ESP32</h1>
                <h3> Servidor WEB corriendo en ESP32 simulado. </h3>
                <p>Comandos:</p>
                <p>/api/LedON: Enciende el LED</p>
                <p>/api/LedOFF: Apaga el LED</p>
              </body>
              </html>)");
            }
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}

void enviarRespuesta(WiFiClient client, String state){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  client.print("{\"status\":\"success\",\"state\":" + state + "}");
}