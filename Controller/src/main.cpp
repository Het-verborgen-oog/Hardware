#include <Arduino.h>
#include <string.h>

// PIN DEFINES
#define MotorPin 2
#define HorizontalPin A2
#define VerticalPin A1

// DATA DEFINES
#define StartMarker '@'
#define PayloadMarker ':'
#define EndMarker '#'

#define SpeedProtocol "SPD"
#define HorizontalProtocol "HRZ"
#define VerticalProtocol "VER"

// SERIAL DEFINES
#define BaudRate 115200
#define MessageDelay 50

// CONVERSION DEFINES
#define UpperAngle 45
#define LowerAngle -45

bool sensorState;
int HorizontalTilt, VerticalTilt, Speed;

void setup()
{
  Serial.begin(BaudRate);
}

void loop()
{
  HorizontalTilt = ReadHorizontalTilt();
  VerticalTilt = ReadVerticalTilt();
  Speed = ReadSpeed();
  SendMessage();
}

int ReadSpeed() // Will return the speed that the thing is being driven by.
{
  return 0;
}

int ReadHorizontalTilt()
{
  return map(analogRead(HorizontalPin), 0, 1024, LowerAngle, UpperAngle);
}

int ReadVerticalTilt()
{
  return map(analogRead(VerticalPin), 0, 1024, LowerAngle, UpperAngle);
}

void SendMessage()
{
  Serial.write(StartMarker + SpeedProtocol  + PayloadMarker + Speed + EndMarker + '\n');
  Serial.write(StartMarker + HorizontalProtocol + PayloadMarker + HorizontalTilt + EndMarker + '\n');
  Serial.write(StartMarker + VerticalProtocol + PayloadMarker + VerticalTilt + EndMarker + '\n');
  delay(MessageDelay);
}