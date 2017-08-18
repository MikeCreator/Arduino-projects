#include "Fan.h"

  void Fan::init(FanInitStruct initStruct)
  {
    fan_pin = initStruct.fan_pin;
    light_pin = initStruct.light_pin;
    stay_off_time = initStruct.stay_off_time*1000; //convert from sec to millis
    stay_on_time = initStruct.stay_on_time*1000;
    pinMode(fan_pin, OUTPUT);
  }
  
  void Fan::update()
  {
    current_millis = millis();
    
    if(digitalRead(light_pin) == HIGH)
    {
      enableUsingFan();
    }
    else
    {
      disableUsingFan();
    }

    if(current_millis < previous_millis_on) previous_millis_on = current_millis;
    if(current_millis < previous_millis_off) previous_millis_off = current_millis;
  }

  void Fan::enableUsingFan()
  {
    if(current_millis - previous_millis_on >= stay_off_time)
      {
        digitalWrite(fan_pin, HIGH);
        previous_millis_off = current_millis;
      }
  }

  void Fan::disableUsingFan()
  {
    previous_millis_on = current_millis;
    if(current_millis - previous_millis_off >= stay_on_time)
    {
      digitalWrite(fan_pin, LOW);
    }
  }
