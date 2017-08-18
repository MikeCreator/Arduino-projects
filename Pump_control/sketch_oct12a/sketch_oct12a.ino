#include "Analog_Temp.h"
#include <avr/pgmspace.h>
#include <Arduino.h>

Analog_Temp  first(A1);
Analog_Temp second(A2);
int powerPin = 9;
void setup()
{
  Serial.begin(9600);
  pinMode(powerPin, OUTPUT);
}
 unsigned long timeper = 300000;
  unsigned long timeper2 = 2100000;
  unsigned long timeper3 = 3600000;
  bool on = true;
  bool on2 = true;
  bool on3 = true;
  float off_temp_dif = 13.00;
  float on_temp_dif = 3.00;
  
void loop()
{
  
  //first.PeriodShowTemp(1000, 0);
  
  //second.PeriodShowTemp(1001, 1);
  if(abs(second.CurrentTemp()-first.CurrentTemp()) >=off_temp_dif) 
  {
    digitalWrite(powerPin, HIGH);
  }
  if(abs(second.CurrentTemp()-first.CurrentTemp())<on_temp_dif) digitalWrite(powerPin, LOW);
}

