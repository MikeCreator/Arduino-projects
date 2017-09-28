//This class helps to detect if someone came in the toilet using data from ultrasonic sensor
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
    void update();        // should be used in a cicle
    void print(uint16_t period, bool newline = 1); // sends data to serial port
    bool hasObstacle();   // checks if the is someone inside
    
  private:
    Ultrasonic ultrasonic;      // HC-SR04 sensor
    KalmanFilter Kfilter;       // filter for data from sensor
    uint8_t distance;           // from wall to the door
    uint8_t allowed_deviation;  // permissible deviation from standstill
    uint16_t reading_frequency; // time between data reading
    unsigned long current_millis;       //
    unsigned long previous_millis;      //
    unsigned long previous_millis_on;   //
    unsigned long previous_millis_off;  //auxiliary variables
    unsigned long print_millis;         //
    uint16_t stay_disabled_time;        //
    uint16_t stay_enabled_time;         //
    bool obstacle;                      //
    uint16_t read_dist;                 // distance data from sensor
    
    float getFiltered();            // returns filtered value
    void enableSwitchingLight();    // controls value of obstacle variable
    void disableSwitchingLight();   //
};

#endif
