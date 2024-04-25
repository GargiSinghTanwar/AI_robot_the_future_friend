#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>         //download here: https://www.electronoobs.com/eng_arduino_Adafruit_GFX.php
#include <Adafruit_SSD1306.h>     //downlaod here: https://www.electronoobs.com/eng_arduino_Adafruit_SSD1306.php
Adafruit_SSD1306 display(5);

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32 or 64 from eBay)
  delay(100);
  display.clearDisplay();
  display.setTextSize(1);    
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.display();
  delay(100);
}

void loop() {
  if(Serial.available()>0){
    String incommingString = Serial.readString();    
    display.clearDisplay();       
    display.println(incommingString);   
    display.display();    
  }
}