/* This class helps to detect obstacle between laser and photoresistor.
To make laser's ray invisible system checks sensor in discreet moments of time.
You can set checking frequency low when someone interrupts laser's ray for invisibility
and make it high for quick response*/
#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

class LaserSensor
{
  public:
    LaserSensor(uint8_t, uint8_t); // first argument is sensorPin, second is laserPin
                            //  turns all other values to zero 
    void set_switching_lvl(uint16_t);
    void set_reading_delay(uint16_t); // delay between turning on the laser and reading data from ph-resistor
    void set_checking_frequencies(int, int); // firs one is for case if someone is inside 
    void start_detection();  // each %frequency  millis checks is someone inside turning value obstacle
                            // to true or false
                                             // and second for quick turning on the light
    bool has_obstacle();   // returns true if someone interrupts laser's ray long time
    uint16_t  get_photres();      // returns value of current resistance
    void print_photres(int timedelay, bool newline = false); // prints the value of resistance to the serial port

    
  private:
    uint8_t laserPin; // pin with connected laser
    uint8_t sensorPin; // pin with connected photoresistor
    unsigned long current_millis;
    unsigned long previous_millis;
    unsigned long old_show_millis;
    unsigned long long current_micros;
    unsigned long long previous_micros;
    int timing; // (current_millis - previous_millis >= timing)
    uint16_t timing_micros;
    int working_frequency; // the frequency of inspections when light is turned on
    int waiting_frequency; // the frequency of inspections when light is turned off
    uint16_t switching_level; // level of difference between is laser at photoseristor of not
    bool obstacle; // is someone interrupts laser's ray
    uint16_t sensor_value; // current photoresistance

    inline void update();
    inline void set_obstalce();
};
#endif

/*
Example 

#include "LaserSensor.h"

#define laser 2
#define photoresistor A3
#define light 8

LaserSensor light_control(photoresistor, laser);

unsigned long current_millis = 0;
unsigned long previous_millis = 0;

int light_level = 750;

int period_loop = 70;

void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  light_control.set_checking_frequencies(3000, 75);
  light_control.set_switching_lvl(light_level);
  light_control.set_reading_delay(100);
}

void loop() {
  current_millis = millis();
  light_control.srart_detection();
  light_control.print_photres(300);
  
  if(current_millis - previous_millis >= period_loop)
  {
      if(light_control.has_obstacle())
      {
        digitalWrite(light, HIGH);
      }
       
      if(!light_control.has_obstacle())
      {
          digitalWrite(light, LOW);
      }
      
    previous_millis = current_millis;
  }
  
  if(current_millis < previous_millis)
    previous_millis = current_millis;
}

*/
