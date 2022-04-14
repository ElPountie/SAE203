#include "FeatherShieldPinouts.h"
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;


uint8_t address[6]  = {0x3C, 0x71, 0xBF, 0x7D, 0x67, 0x44};
String name = "Ouistiti";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;
void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  SerialBT.begin(name, true);
  Serial.println("Client ON");
  connected = SerialBT.connect(name);
  SerialBT.connect();
  if (connected) {
    Serial.println("Connexion Bluetooth ON");
  } else {
    Serial.println("Error Connect, retry incoming");
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }

  }

}

void loop() {
  delay(200);
  if (connected){
  if (digitalRead(A2)) {
      Serial.println("Detect 2");
      SerialBT.write(1);
      delay(200);
    } else  {
      Serial.println(" nothing 2");
      SerialBT.write(0);
      delay(200);
    }
    if (digitalRead(A0)) {
      Serial.println("Detect 1");
      SerialBT.write(2);
      delay(200);
    } else {
      Serial.println("Nothing 1");
      SerialBT.write(3);
      delay(200);
    }
  }
}
