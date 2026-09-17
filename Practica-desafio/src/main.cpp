#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "FS.h"
#include "SPIFFS.h"

WebServer server(80);

// 1. Función para la ruta HTML raíz ("/")
void handleRoot() {
  if (SPIFFS.exists("/index.html")) {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  } else {
    server.send(404, "text/plain", "Archivo index.html no encontrado");
  }
}

// 2. Función para la ruta REST API ("/api/status")
void handleStatus() {
  String jsonResponse = "{";
  jsonResponse += "\"uptime_ms\":" + String(millis()) + ",";
  jsonResponse += "\"free_heap_bytes\":" + String(ESP.getFreeHeap()) + ",";
  jsonResponse += "\"spiffs_total_bytes\":" + String(SPIFFS.totalBytes()) + ",";
  jsonResponse += "\"spiffs_used_bytes\":" + String(SPIFFS.usedBytes());
  jsonResponse += "}";

  server.send(200, "application/json", jsonResponse);
}

// 3. Función auxiliar para rutas no encontradas (404)
void handleNotFound() {
  server.send(404, "application/json", "{\"error\": \"Ruta no encontrada\"}");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Inicializar SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Error al montar SPIFFS");
    return;
  }

  size_t totalBytes = SPIFFS.totalBytes();
  size_t usedBytes  = SPIFFS.usedBytes();
  size_t freeBytes  = totalBytes - usedBytes;
  Serial.println("\n--- ESTADO DEL DISCO (SPIFFS) ---");
  Serial.printf("Espacio total : %u bytes (%.2f KB)\n", totalBytes, totalBytes / 1024.0);
  Serial.printf("Espacio usado : %u bytes (%.2f KB)\n", usedBytes, usedBytes / 1024.0);
  Serial.printf("Espacio libre : %u bytes (%.2f KB)\n", freeBytes, freeBytes / 1024.0);
  Serial.println("----------------------------------");

  // Conectar a la red WiFi simulada de Wokwi
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Mapear cada ruta a su función correspondiente
  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP y API REST listos en http://localhost:8080");
}

void loop() {
  server.handleClient();
}