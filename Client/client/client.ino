#include <WiFi.h>
#include <WiFiClient.h>
#include <esp_now.h>
#include <WiFiAP.h>

WiFiServer server(80);

bool statutsensor;
uint8_t broadcastAddress1[] = {0x3C, 0x71, 0xBF, 0x7D, 0x67, 0x44};

typedef struct test_struct {
  bool capteurIR;
} test_struct;

test_struct test;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet from: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A2,INPUT);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent); 
  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // register first peer
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  WiFi.begin("Ouistiti");
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
}

void loop() {
  // put your main code here, to run repeatedly:
 delay(5000);
 statutsensor = digitalRead(A2);
 test.capteurIR = statutsensor;
 
}
