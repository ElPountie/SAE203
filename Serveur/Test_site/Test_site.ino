#include <WiFi.h>  // Librairie Wifi.h
#include <WebServer.h>  // Librairie WebServer.h
#include <esp_now.h>
#include "FeatherShieldPinouts.h"

const char* ssid = "IPhone de Bob Rasowski";
const char* password = "azerty01";
int statusSensor;
bool capteurIR = digitalRead(A2);
typedef struct test_struct {
  bool capteurIR;
} test_struct;

test_struct myData;

WebServer server(80);

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.capteurIR);
}

char texteEtatIR[2][10] = {"Libre", "Occupé"}; // Affichage ETEINTE ou ALLUMEE

void handleRoot() {  // Début de la page HTML
  String page = "<!DOCTYPE html>";
  page += "<html lang='en'>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<link href='./style.css' rel='stylesheet'>";
  page += "<title>Manager</title>";
  page += "<style>";
  page += "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@100&display=swap');";

  page += "*{";
  page += "font-family:'Roboto', sans-serif;;";
  page +=  "margin: 0;";
  page += "transition: 2s linear;";
  page += "}";

  page += "hr{";
  page += "background-color: black;";
  page += "height : 5px;";
  page += "margin : 0;";
  page += "}";

  page += ".top{";
  page += "background-color: rgb(13, 133, 239);";
  page += "text-align: center;";
  page += "height : 10rem";
  page +=  "}";

  page += ".top h1 {";
  page += "padding-top: 15%;";
  page += "}";

  page += ".mid{";
  page +=  "display: flex;";
  page += "justify-content: space-around;";
  page += "align-items: center;";
  page += " background-color: rgb(222, 220, 220);";
  page += "height : 400px ;";
  page += "}";

  page += "footer{";
  page +=  "background-color: black;";
  page += "width : 100%;";
  page +=  "height: 100px;";
  page += "}";

  page += ".card{";
  page +=  "background-color: rgb(202, 200, 200);";
  page += "height : 60%;";
  page += "text-align: center;";
  page += "width : 160px;";
  page += "border-radius: 5%;";
  page += "}";

  page += ".card h2{";
  page += "padding-top: 5%;";
  page += "}</style>";
  page += "</head>";
  page += "<body>";
  page += "<div class='top'> <h1>Parking Manager : </h1></div>";
  page += "<hr>";
  page += "<div class='mid'>";
  page += "<div class='card'>";
  page += "<h2>Place 1</h2>";

  page += "</div>";
  page += "<div class='card'>";
  page += "<h2>Place 2</h2>";
  page += "</div>";
  page += "</div>";
  page += "<footer></footer>";

  page += "</body>";
  page += "</html>;";

  server.setContentLength(page.length());  // Permet l'affichage plus rapide après chaque clic sur les boutons
  server.send(200, "text/html", page);
}

void handleNotFound() { // Page Not found
  server.send(404, "text/plain", "404: Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(A2, INPUT);
  delay(1000);
  Serial.println("\n");

  pinMode(A0, OUTPUT); // Définition de la led en OUTPUT
  digitalWrite(A0, 0);  // Initialisation de la led à 0 (éteinte)

  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  Serial.print("Attente de connexion ...");

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } 
  esp_now_register_recv_cb(OnDataRecv);
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
