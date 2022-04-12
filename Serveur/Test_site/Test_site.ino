#include <WiFi.h>  // Librairie Wifi.h
#include <WebServer.h>  // Librairie WebServer.h
#include "BluetoothSerial.h"

WebServer server(80);
BluetoothSerial SerialBT;

//char texteEtatIR[2][10] = {"Libre", "Occupé"}; // Affichage ETEINTE ou ALLUMEE

void handleRoot() {  // Début de la page HTML
   String page  = "<!DOCTYPE html>"
"<html lang'en'>"
"<head>"
    "<meta charset='UTF-8'>"
    "<meta http-equiv='X-UA-Compatible' content='IE=edge'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<link href='./style.css' rel='stylesheet'>"
    "<title>Manager</title>"
    "<style>"
        "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@100&display=swap');"
        
        "*{"
            "font-family:'Roboto', sans-serif;;"
           " margin: 0;"
            "transition: 2s linear;"
        "}"
        
        "hr{"
            "background-color: black;"
            "height : 5px;"
           " margin : 0;"
       " }"
        
        "."
       ".top{"
            "background-color: rgb(13, 133, 239);"
            "text-align: center;"
            "height : 10rem"
        "}"
        
        ".top h1 {"
            "padding-top: 15%;"
        "}"
        
        ".mid{"
            "display: flex;"
            "justify-content: space-around;"
            "align-items: center;"
            "background-color: rgb(222, 220, 220);"
            "height : 400px ;"
        "}"
        
        "footer{"
            "background-color: black;"
            "width : 100%;"
            "height: 100px;"
        "}"
        
        ".card{"
            "background-color: rgb(202, 200, 200);"
            "height : 60%;"
            "text-align: center;"
            "width : 160px;"
            "border-radius: 5%;"
        "}"
        
        ".card h2{"
            "padding-top: 5%;"
"}</style>"
"</head>"
"<body>"
    "<div class='top'> <h1>Parking Manager : </h1></div>"
    "<hr>"
    "<div class='mid'>"
        "<div class='card'>"
            "<h2>Place 1</h2>"

        "</div>"
        "<div class='card'>"
            "<h2>Place 2</h2>"
        "</div>"
    "</div>"
    "<footer></footer>"
    
"</body>"
"</html>";
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  SerialBT.begin("Ouistiti"); //Bluetooth device name

  WiFi.persistent(false);
  WiFi.begin("IPhone de Bob Rasowski", "azerty01");

  //server.on("/", handleRoot);  // Chargement de la page accueil
  server.begin();

}

void loop() {
  server.handleClient();
  if (SerialBT.available()) {
    Serial.println(SerialBT.read());
  }
}
