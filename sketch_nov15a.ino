#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <FS.h>
#include <SPIFFS.h>

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

const char* apSSID = "Esp32_calculator";
const char* apPassword = "12345678";

void setup() {
  Serial.begin(115200);
  if (MDNS.begin("esp32")) {  
    Serial.println("mDNS responder started");
  } else {
    Serial.println("mDNS initialization failed!");
  }
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(apSSID, apPassword);

  Serial.println("Access Point Started");
  Serial.println("IP Address: " + WiFi.softAPIP().toString());

  // Serve HTML, CSS, and JS files
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/bootstrap.min.css", "text/css");
  });
  server.on("/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/bootstrap.bundle.min.js", "application/javascript");
  });
  server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/app.js", "application/javascript");
  });
  server.on("/functions.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/functions.js", "application/javascript");
  });
  server.on("/delete.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/delete.jpg", "image/png");
  });

  server.on("/close-button.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/close-button.png", "image/png");
  });
  server.on("/down-arrow.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/down-arrow.png", "image/png");
  });
  server.on("/function-f.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/down-arrow.png", "image/png");
  });
  server.on("/remove-icon.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/remove-icon.png", "image/png");
  });
  server.on("/sort-down.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/sort-down.png", "image/png");
  });
  server.on("/triangle.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/triangle.png", "image/png");
  });
  server.begin();
}

void loop() {
  // Nothing to do here
}
