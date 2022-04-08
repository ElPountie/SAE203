#include <WiFi.h>  // Librairie Wifi.h
#include <WebServer.h>  // Librairie WebServer.h
#include <BLEDevice.h>
#include "site.h"
#include <BLEUtils.h>
#include <BLEServer.h>#include "FeatherShieldPinouts.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

const char* ssid = "IPhone de Bob Rasowski";
const char* password = "azerty01";

WebServer server(80);


char texteEtatIR[2][10] = {"Libre", "Occupé"}; // Affichage ETEINTE ou ALLUMEE

void handleRoot() {  // Début de la page HTML
  server.setContentLength(page.length());  // Permet l'affichage plus rapide après chaque clic sur les boutons
  server.send(200, "text/html", page);
}

void handleNotFound() { // Page Not found
  server.send(404, "text/plain", "404: Not found");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Long name works now");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
         
  delay(1000);
  Serial.println("\n");

  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  Serial.print("Attente de connexion ...");
  Serial.println("Server started");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie !");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  server.on("/", handleRoot);  // Chargement de la page accueil
  server.onNotFound(handleNotFound);  // Chargement de la page Not found
  server.begin();

  Serial.println("Serveur web actif");
}

void loop() {
  server.handleClient();
}
