#include "roombaDefines.h"
#include <SoftwareSerial.h>
const int RELAY_PIN = 3;
unsigned long minutes = 3000;

int rxPin = 10;
int txPin = 11;
SoftwareSerial Roomba(rxPin, txPin);

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial) {}
  Roomba.begin(19200);
  while (!Roomba) {}
  pinMode(ddPin, OUTPUT);
//  pinMode(buttonPin, INPUT_PULLUP); // connected to Arduino pin 12 and used for "starting"

  delay(2000);

  wakeUp();
  startSafe();
  drive(500, 0);
  digitalWrite(RELAY_PIN, HIGH);
  delay(3000); // 3000
  driveStop();
  turnCCW(500,30);
  drive(500,0);
  digitalWrite(RELAY_PIN, LOW);
  delay(4000); // 4000
  //  driveStop();
//  turnCW(500,30);
//  drive(500,0);
// delay(1000);
// driveStop();
// turn CCW(500,50);
  digitalWrite(RELAY_PIN, HIGH);
  delay(3000); // 3000
  digitalWrite(RELAY_PIN, LOW);
  delay(1000);
  driveStop();
  

}

void loop()
{
//  if (millis() < minutes * .5) {
//    if (Serial.available() > 0) {
//    String message = Serial.readString();
//    if (message == "forward") {
//      drive(500, 0);
//      delay(1000);
//      driveStop();
//    } else if (message == "right") {
//      turnCW(500, 10);
//      delay(1000);
//      driveStop();
//    } else if (message == "left") {
//      turnCCW(500, 10);
//      delay(1000);
//      driveStop();
//    } else {
//      delay(1000);
//      driveStop();
//    }
//    int randChance = random(1,7);
//    if (randChance == 1){
//      digitalWrite(RELAY_PIN, HIGH);
//    } else if (randChance == 7) {
//      digitalWrite(RELAY_PIN, LOW);
//    } else if (randChance == 6) {
//      digitalWrite(RELAY_PIN, LOW);
//      }
//  }
//  } else {
//    delay(1000);
//    driveStop();
//    delay(1000);
//    digitalWrite(RELAY_PIN, LOW);
//  }
}

void wakeUp (void)
{
  //  setWarningLED(ON);
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
}

void startSafe()
{
  Roomba.write(128);  //Start
  Roomba.write(132);  //Safe mode
  delay(1000);
}

void drive(int velocity, int radius)
{
  clamp(velocity, -500, 500); //def max and min velocity in mm/s
  clamp(radius, -2000, 2000); //def max and min radius in mm

  Roomba.write(137);
  Roomba.write(velocity >> 8);
  Roomba.write(velocity);
  Roomba.write(radius >> 8);
  Roomba.write(radius);
}

//---------------------------------------------------------------

void driveWheels(int right, int left)
{
  clamp(right, -500, 500);
  clamp(left, -500, 500);

  Roomba.write(145);
  Roomba.write(right >> 8);
  Roomba.write(right);
  Roomba.write(left >> 8);
  Roomba.write(left);
}

//---------------------------------------------------------------
void driveWheelsPWM(int rightPWM, int leftPWM)
{
  clamp(rightPWM, -255, 255);
  clamp(leftPWM, -255, 255);

  Roomba.write(146);
  Roomba.write(rightPWM >> 8);
  Roomba.write(rightPWM);
  Roomba.write(leftPWM >> 8);
  Roomba.write(leftPWM);
}

//---------------------------------------------------------------
void turnCW(unsigned short velocity, unsigned short degrees)
{
  drive(velocity, -1);
  clamp(velocity, 0, 500);
  delay(6600);
  drive(0, 0);
}

//---------------------------------------------------------------
void turnCCW(unsigned short velocity, unsigned short degrees)
{
  drive(velocity, 1);
  clamp(velocity, 0, 500);
  delay(6600);
  drive(0, 0);
}

//---------------------------------------------------------------
void driveStop(void)
{
  drive(0, 0);
}

//---------------------------------------------------------------
void driveLeft(int left)
{
  driveWheels(left, 0);
}

//---------------------------------------------------------------
void driveRight(int right)
{
  driveWheels(0, right);
}