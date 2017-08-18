
#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#include "Ultrasonic.h"
#include "KalmanFilter.h"

struct SoundInitStruct{
 // uint8_t trig_pin;
 // uint8_t echo_pin;
 // float average_deviation; 
 // float reaction_speed;
  uint8_t distance;
  uint8_t allowed_deviation;
  uint16_t reading_frequency;
  uint16_t filter_time;
};

class SoundSensor
{
  public:
    SoundSensor(uint8_t _trig_pin, uint8_t _echo_pin, float _average_deviation, float _reaction_speed);
    void init(SoundInitStruct);
    void update();
    void print(uint16_t period, bool newline = 1);
    bool hasObstacle();
    
  private:
    Ultrasonic ultrasonic;
    KalmanFilter Kfilter;
    uint8_t distance;
    uint8_t allowed_deviation;  // допустимое отклонение от расстояния покоя
    uint16_t reading_frequency;
    unsigned long current_millis;
    unsigned long previous_millis;
    unsigned long previous_millis_on;
    unsigned long previous_millis_off;
    unsigned long print_millis;
    uint16_t stay_disabled_time;
    uint16_t stay_enabled_time;
    bool obstacle;
    uint16_t read_dist;
    
    float getFiltered();
    void enableSwitchingLight();
    void disableSwitchingLight();
};

#endif
