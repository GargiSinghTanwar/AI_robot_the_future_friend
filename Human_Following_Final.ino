#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

int EN_A = 5; // Enable pin for first motor
int IN1 = 9; // Control pin for first motor
int IN2 = 8; // Control pin for first motor
int IN3 = 7; // Control pin for second motor
int IN4 = 6; // Control pin for second motor
int EN_B = 3; // Enable pin for second motor
int x;
int y;
int w;
int h;

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX


void move_right()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);    
    Serial.println("Moving Right"); 
    delay(500);   
}
void move_left()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Moving Left");   
    delay(500);
}
void move_forward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Moving Forward"); 
    delay(500);
}
void stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    Serial.println("Stopping");
    delay(500);
}

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
    pinMode(EN_A, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(EN_B, OUTPUT);

    while (!huskylens.begin(mySerial)) {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1. Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2. Please recheck the connection."));
        delay(100);
    }
}

void loop() {
    if (!huskylens.request())
        Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned())
        Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available())
        Serial.println(F("No block or arrow appears on the screen!"));
    else {
        Serial.println(F("\n\n\n###########"));
        while (huskylens.available()) {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);

              analogWrite(EN_A, 100);
              analogWrite(EN_B, 100);

              x = result.xCenter;
              y = result.yCenter;
              w = result.width;
              h = result.height;
              Serial.print("X coordinate: ");
              Serial.println(x);
              Serial.print("Y coordinate: ");
              Serial.println(y);              
              Serial.print("BOX WIDTH: ");
              Serial.println(w);
              Serial.print("BOX HEIGHT: ");
              Serial.println(h);
              
              if (x > 170 & x < 320)
                {
                  move_right();                                
                }
                else if (x > 0 & x < 130)
                {
                  move_left(); 
                }
              if (w < 50)
              {
                move_forward();
                  //delay(3000);
               }
                      
              stop();
        }
    }
}

void printResult(HUSKYLENSResult result) {
    if (result.command == COMMAND_RETURN_BLOCK) {
        Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
    } else if (result.command == COMMAND_RETURN_ARROW) {
        Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
    } else {
        Serial.println("Object unknown!");
    }
}
