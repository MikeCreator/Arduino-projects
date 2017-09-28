//controls fan dependently of time that light is switched on or switched off in the toilet

#ifndef FAN_H
#define FAN_H


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

struct FanInitStruct
{
  uint8_t fan_pin;
  uint8_t light_pin;
  uint32_t stay_off_time; //seconds
  uint32_t stay_on_time; //seconds
};

class Fan
{
  public:
    Fan(){};
    void init(FanInitStruct);
    void update();
    
  private:
    uint8_t fan_pin;      //pins
    uint8_t light_pin;    //
    uint32_t stay_off_time; // time that light should be enabled before fan will turn on   | milliseconds
    uint32_t stay_on_time; // time that fan should work after light is turned off           | milliseconds
    
    unsigned long current_millis;       //
    unsigned long previous_millis_on;   //  auxiliary variables
    unsigned long previous_millis_off;  //

    void enableUsingFan();
    void disableUsingFan();
};

#endif 
