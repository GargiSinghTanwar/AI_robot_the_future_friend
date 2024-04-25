#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

Adafruit_SSD1306 display(5);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SoftwareSerial SIM900A(2,3);

void setup() {
  Serial.begin(115200);
  SIM900A.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  mlx.begin();

  delay(100);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.display();
  delay(100);

  Serial.println("Text Message Module Ready & Verified");
  delay(100);
  Serial.println("Type s to send message or r to receive message");
}

void loop() {
  // Temperature Sensor
  float ambientTempC = mlx.readAmbientTempC();
  float objectTempC = mlx.readObjectTempC();

  Serial.print("Ambient = "); Serial.print(ambientTempC);
  Serial.print("*C\tObject = "); Serial.print(objectTempC); Serial.println("*C");
  
  // OLED Display
  display.clearDisplay();       
  display.print("Ambient: "); display.println(ambientTempC);
  display.print("Object: "); display.println(objectTempC);
  display.display();

  // Emergency Message
  if (objectTempC > 17.8) {  // Temperature above 100°F
    sendEmergencyMessage();
  }

  // UART Communication
  String sensorData = String(ambientTempC) + "," + String(objectTempC);
  Serial.println(sensorData);

  delay(500);
}

void sendEmergencyMessage() {
  display.print("Sending Emergency Message please wait….");
  SIM900A.println("AT+CMGF=1"); //Text Mode initialization
  delay(1000);
  display.print("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+919027953208\"\r"); // Receiver’s Mobile Number
  delay(1000);
  display.print("Set SMS Content");
  SIM900A.println("Emergency: Temperature is above 100°F!");// Message content
  delay(100);
  display.print("Done");
  SIM900A.println((char)26);// delay(1000);
  display.print("Emergency Message sent successfully");
}
