#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
int statusSensor;

#include "FeatherShieldPinouts.h"
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);


void setup() {
  display.begin(0x3C, true);
  display.clearDisplay();
  Serial.begin(115200);
  pinMode(A2, INPUT);
  pinMode(A0, OUTPUT);
  display.setTextSize(2); //Set our text size, size 1 correlates to 8pt font
  display.setTextColor(SH110X_WHITE); //We're using a Monochrome OLED so color is
  display.setCursor(30, 25); //Start position for the font to appear
  display.setRotation(3);
  
}

void loop() {
  delay(200);
  if (digitalRead(A2)){
    Serial.println("Detect");
    delay(200);
  }else{
    Serial.println("Rien");
    delay(200);
  }
  
  
  display.display();


}
