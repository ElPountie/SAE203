#include <WiFi.h>  // Librairie Wifi.h
#include <WebServer.h>  // Librairie WebServer.h
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const char* ssid = "IPhone de Bob Rasowski";
const char* password = "azerty01";

unsigned long previousMillis = 0;
unsigned long interval = 30000;



BluetoothSerial SerialBT;
WebServer server(80);
int IR = 0;
int IR1 = 0;
int IR2 = 0;

char texteEtatIR[2][10] = {"Libre", "Occupé"}; // Affichage ETEINTE ou ALLUMEE

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void handleRoot() {  // Début de la page HTML
  String page = "<!DOCTYPE html>";
  page += "<html lang='en'>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta http-equiv='refresh' content='1.5' />";
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
  page += "<h3>"; page += texteEtatIR[IR1]; page += "<h3>";


  page += "</div>";
  page += "<div class='card'>";
  page += "<h2>Place 2</h2>";
  page += "<h3>"; page += texteEtatIR[IR2]; page += "<h3>";
  page += "</div>";
  page += "</div>";
  page += "<footer></footer>";

  page += "</body>";
  page += "</html>";

  server.setContentLength(page.length());
  server.send(200, "text/html", page);
}// Fin page HTML




void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  initWiFi();
  SerialBT.begin("Ouistiti"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  server.on("/", handleRoot);  // Chargement de la page accueil
  server.begin();

}

void loop() {
  server.handleClient();
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
  if (SerialBT.available()) {
    IR = SerialBT.read();
    if (IR == 0) {
      IR1 = 0;
    }
    else if (IR == 1) {
      IR1 = 1;
    }
    else if (IR == 3) {
      IR2 = 0;
    }
    else if (IR == 2) {
      IR2 = 1;
    }
  }
  //Serial.println(IR); // Test pour voir si on le bluetooth envoie les valeurs
  delay(200);
}
