#include "SoundSensor.h"

  SoundSensor::SoundSensor(uint8_t _trig_pin, uint8_t _echo_pin, float _average_deviation, float _reaction_speed):
    ultrasonic(_trig_pin, _echo_pin),
    Kfilter(_average_deviation, _reaction_speed)
    {}

  void SoundSensor::init(SoundInitStruct initStruct)
  {
    distance = initStruct.distance;
    allowed_deviation = initStruct.allowed_deviation;
    reading_frequency = initStruct.reading_frequency;
    stay_enabled_time = stay_disabled_time = initStruct.filter_time;
  }
       
  void SoundSensor::update()
  {
    current_millis = millis();
    if(current_millis - previous_millis >= reading_frequency)
    {
      read_dist = ultrasonic.Ranging(CM);
      
      if(abs(uint16_t(getFiltered())-distance) > allowed_deviation)
      {
        enableSwitchingLight();
      }
      else
      {
        disableSwitchingLight();
      }
      
      previous_millis = current_millis;
    }
   
    if(current_millis < previous_millis) previous_millis = current_millis;
  }

  bool SoundSensor::hasObstacle()
  {
    return (obstacle);
  }
  
  void SoundSensor::print(uint16_t period, bool newline)
  {
    if(current_millis - print_millis >= period)
    { 
      if(newline)
      {
        Serial.print(read_dist);
        Serial.print(' ');
        Serial.print(getFiltered());
        Serial.print(' ');
        Serial.println(int(getFiltered()));
      }
      else {
        Serial.print(read_dist);
        Serial.print(' ');
        Serial.print(getFiltered());
        Serial.print(' ');
        Serial.print(int(getFiltered()));
        Serial.print(' ');
      }
      print_millis = current_millis;
    }
    if(current_millis < print_millis) print_millis = current_millis;
  }

  float SoundSensor::getFiltered()
  {
    return Kfilter.doFiltration(read_dist);
  }

  void SoundSensor::enableSwitchingLight()
  {
    if(current_millis - previous_millis_on >= stay_disabled_time)
      {
        obstacle = true;
        previous_millis_off = current_millis;
      }
  }
    
  void SoundSensor::disableSwitchingLight()
  {
    previous_millis_on = current_millis;
    if(current_millis - previous_millis_off >= stay_enabled_time)
    {
      obstacle = false;
    }
  }

