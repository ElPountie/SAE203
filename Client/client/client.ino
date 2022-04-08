#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x7D, 0x67, 0x44};

typedef struct test_struct {
  bool capteurIR;
} test_struct;

test_struct myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(A2,INPUT);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent); 
//Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

 myData.capteurIR = digitalRead(A2);
 Serial.println(myData.capteurIR);
 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); 
 if (result == ESP_OK) {
    Serial.println("Sent with success");
 }
 else {
    Serial.println("Error sending the data");
 }
 delay(2000);
}
