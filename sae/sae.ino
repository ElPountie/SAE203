

#include "FeatherShieldPinouts.h"
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;


uint8_t address[6]  = {0x3C, 0x61, 0x05, 0x4A, 0xD5, 0x68};
String name = "Ouistiti";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;
void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  SerialBT.begin(name, true);
  Serial.println("Client ON");
  connected = SerialBT.connect(name);
  SerialBT.connect();
  if (connected){
    Serial.println("Connexion Bluetooth ON");
  }else{
     Serial.println("Error Connect, retry incoming");
     while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
    
  }

}

void loop() {
  delay(200);
  if (digitalRead(A2)) {
    Serial.println("Detect");
    delay(200);
  } else {
    Serial.println("Rien");
    delay(200);
  }
  if (SerialBT.available()){
    SerialBT.write(digitalRead(A2));
  }
  delay(200);

}
