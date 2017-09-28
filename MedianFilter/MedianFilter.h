//Realisation of median filter

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define SIZE 11 //size of queue

struct MedianFilterInitStruct
{
    uint8_t pin;
    uint16_t reading_frequency;  
};

class MedianFilter
{
  private:
    uint8_t queue_size;
    uint16_t queue[SIZE];
    
    uint8_t pin;  //  pin, to which sensor is connected
    uint16_t reading_frequency; // friquency for reading data from a sensor
    
    unsigned long current_millis;
    unsigned long previous_millis;
    unsigned long previous_print_millis;
    
  public:
    MedianFilter();
    void init(MedianFilterInitStruct);
    void update(); // use in a cicle
    uint16_t getFiltered(); // returns filtered value
    void print(uint16_t printing_frequency, bool newline = 1); // sends data to serial port
};

