#include <WiFi.h>  // Librairie Wifi.h
#include <WebServer.h>  // Librairie WebServer.h
#include "BluetoothSerial.h"

WebServer server(80);
BluetoothSerial SerialBT;

//char texteEtatIR[2][10] = {"Libre", "Occupé"}; // Affichage ETEINTE ou ALLUMEE

void handleRoot() {  // Début de la page HTML
  String page = "<!DOCTYPE html>";
  page += "<html lang='en'>";
  page += "<head>";
      page+= "<meta charset='UTF-8'>";
      page+="<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
      page+="<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
      page+="<link href='./style.css' rel='stylesheet'>";
      page+="<title>Manager</title>";
      page+="<style>";
         page+="@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@100&display=swap');";
          
          page+="*{";
          page+="font-family:'Roboto', sans-serif;;";
            page+=  "margin: 0;";
            page+= "transition: 2s linear;";
         page+= "}";
          
         page+= "hr{";
             page+= "background-color: black;";
             page+="height : 5px;";
             page+= "margin : 0;";
         page+= "}";
          
         page+= ".top{";
             page+= "background-color: rgb(13, 133, 239);";
             page+= "text-align: center;";
            page+= "height : 10rem";
        page+=  "}";
          
         page+= ".top h1 {";
             page+= "padding-top: 15%;";
         page+= "}";
          
         page+= ".mid{";
            page+=  "display: flex;";
             page+= "justify-content: space-around;";
             page+= "align-items: center;";
             page+=" background-color: rgb(222, 220, 220);";
             page+= "height : 400px ;";
         page+= "}";
          
          page+= "footer{";
            page+=  "background-color: black;";
             page+= "width : 100%;";
            page+=  "height: 100px;";
         page+= "}";
          
          page+=".card{";
            page+=  "background-color: rgb(202, 200, 200);";
             page+= "height : 60%;";
             page+= "text-align: center;";
             page+= "width : 160px;";
             page+= "border-radius: 5%;";
         page+= "}";
          
         page+= ".card h2{";
              page+= "padding-top: 5%;";
  page+= "}</style>";
  page+="</head>";
  page+="<body>";
      page+="<div class='top'> <h1>Parking Manager : </h1></div>";
      page+="<hr>";
      page+="<div class='mid'>";
         page+= "<div class='card'>";
             page+= "<h2>Place 1</h2>";
  
          page+="</div>";
         page+= "<div class='card'>";
              page+="<h2>Place 2</h2>";
         page+= "</div>";
      page+="</div>";
      page+="<footer></footer>";
      
  page+="</body>";
  page+="</html>";

  server.setContentLength(page.length());
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);


  WiFi.persistent(false);
  WiFi.begin("IPhone de Bob Rasowski", "azerty01");
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
  server.begin();
  
  SerialBT.begin("Ouistiti"); //Bluetooth device name
  
  Serial.println("Serveur web actif");

}

void loop() {
  server.handleClient();
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
}
