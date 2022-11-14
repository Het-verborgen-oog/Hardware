#include <Arduino.h>

// PIN DEFINES
#define MotorPin 2
#define HorizontalPin A2
#define VerticalPin A1

//DATA DEFINES
#define StartMarker '@'
#define PayloadMarker ':'
#define EndMarker '#'

//SERIAL DEFINES
#define BaudRate 115200

bool sensorState;
int HorizontalVal, VerticalVal, SpeedVal;

void setup()
{
    Serial.begin(BaudRate);
}

void loop()
{

}

int CalculateSpeed()
{

}

void SendMessage()
{

}