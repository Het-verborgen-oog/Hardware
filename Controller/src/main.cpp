#include <Arduino.h>
#include <string.h>

// TODO: Make sure pins are equal to the ones currently in use, so the client wont have to switch stuff around

// PIN DEFINES
#define MotorPin 12
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
#define BaudRate 9600
#define MessageDelay 50

// CYCLING DEFINES
#define ResetDelay 200

#define VerticalArraySize 5
#define HorizontalArraySize 15

int VerticalData[VerticalArraySize];
int HorizontalData[HorizontalArraySize];

int CycleState = LOW;

int HorizontalTilt, VerticalTilt, Speed;

void setup()
{
  pinMode(MotorPin,INPUT);
  pinMode(HorizontalPin,INPUT);
  pinMode(VerticalPin,INPUT);
  Serial.begin(BaudRate);
}

int CalculateAverage(int* array, int size, int data)
{
  int total = 0;
  for (int i = 0; i < size - 1; i++)
  {
    *array = *(array + 1);
    total += *array;
    array++;
  }
  *array = data;
  total += data;
  return total / size;
}

int debug = 0;

void ReadSpeed() // Will return the speed that the thing is being driven by.
{
  int check = digitalRead(MotorPin);

  if(CycleState != check)
  {
      Speed = 5;
      CycleState = check;
  }
  else
  {
    Speed = 0;
  }
  return;
}

void ResetRotations()
{
  Speed = 0;
}

void SendMessage(char protocol[], int value)
{
  Serial.print(StartMarker);
  Serial.print(protocol);
  Serial.print(PayloadMarker);
  Serial.print(value);
  Serial.println(EndMarker);
  delay(20);
}

void loop()
{
  HorizontalTilt = analogRead(HorizontalPin);
  VerticalTilt = analogRead(VerticalPin);

  ReadSpeed();

  SendMessage(SpeedProtocol,Speed);
  SendMessage(HorizontalProtocol,CalculateAverage(&HorizontalData[0],HorizontalArraySize,HorizontalTilt));
  SendMessage(VerticalProtocol,CalculateAverage(&VerticalData[0],VerticalArraySize,VerticalTilt));
}