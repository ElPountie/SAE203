//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Victor Tchistiak - 2019
//
//This example demostrates master mode bluetooth connection and pin 
//it creates a bridge between Serial and Classical Bluetooth (SPP)
//this is an extention of the SerialToSerialBT example by Evandro Copercini - 2018
//

#include "BluetoothSerial.h"
#include "FeatherShieldPinouts.h"
BluetoothSerial SerialBT;

String MACadd = "3C:61:05:4A:D5:68";
uint8_t address[6]  = {0x3C, 0x61, 0x05, 0x4A, 0xD5, 0x68};
//uint8_t address[6]  = {0x00, 0x1D, 0xA5, 0x02, 0xC3, 0x22};
String name = "Ouistiti";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;

void setup() {
  Serial.begin(115200);
  pinMode(A2,INPUT);
  //SerialBT.setPin(pin);
  SerialBT.begin("Ouistiti", true); 
  //SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  
  // connect(address) is fast (upto 10 secs max), connect(name) is slow (upto 30 secs max) as it needs
  // to resolve name to address first, but it allows to connect to different devices with the same name.
  // Set CoreDebugLevel to Info to view devices bluetooth address and device names
  connected = SerialBT.connect(name);
  //connected = SerialBT.connect(address);
  
  if(connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
}

void loop() {
  
  if (digitalRead(A2)){
    Serial.println("Detect");
    delay(200);
  }else{
    Serial.println("Rien");
    delay(200);
  }
  
  if (SerialBT.available()) {
    Serial.write(digitalRead(A2));
  }
  delay(20);
}
