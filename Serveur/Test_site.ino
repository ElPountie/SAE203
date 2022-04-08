#include <WiFi.h>  // Librairie Wifi.h
#include <WebServer.h>  // Librairie WebServer.h
#include "FeatherShieldPinouts.h"

const char* ssid = "IPhone de Bob Rasowski";
const char* password = "azerty01";
int statusSensor;
bool capteurIR = digitalRead(A2);

WebServer server(80);


char texteEtatIR[2][10] = {"Libre", "Occupé"}; // Affichage ETEINTE ou ALLUMEE

void handleRoot() {  // Début de la page HTML
  String page = "<!DOCTYPE html>";
  page += "<meta http-equiv='refresh' content='10'>";
  page += "<html lang='fr'>";

  page += "<head>";
  page += "    <meta http-equiv='refresh' content='1'>";
  page += "    <title>Serveur ESP32</title>";
  page += "    <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'/>";
  page += "    <link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";  // Utilisation du css
  page += "</head>";

  page += "<body>";
  page += "    <div class='w3-card w3-blue w3-padding-small w3-jumbo w3-center'>";
  page += "        <p>ÉTAT LED: "; page += texteEtatIR[capteurIR]; page += "</p>";
  page += "    </div>";

  page += "    <div class='w3-center w3-padding-16'>";
  page += "        <p>Ce serveur est hébergé sur un ESP32</p>";
  page += "        <i>Créé par Tommy Desrochers</i>";
  page += "    </div>";

  page += "</body>";
  page += "</html>";  // Fin de la page HTML

  server.setContentLength(page.length());  // Permet l'affichage plus rapide après chaque clic sur les boutons
  server.send(200, "text/html", page);
}

void handleNotFound() { // Page Not found
  server.send(404, "text/plain", "404: Not found");
}

void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  delay(1000);
  Serial.println("\n");

  pinMode(A0, OUTPUT); // Définition de la led en OUTPUT
  digitalWrite(A0, 0);  // Initialisation de la led à 0 (éteinte)

  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  Serial.print("Attente de connexion ...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie !");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);  // Chargement de la page accueil
  server.onNotFound(handleNotFound);  // Chargement de la page Not found
  server.begin();

  Serial.println("Serveur web actif");
}

void loop() {
  server.handleClient();
}
