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
    
    uint8_t pin;
    uint16_t reading_frequency;
    
    unsigned long current_millis;
    unsigned long previous_millis;
    unsigned long previous_print_millis;
    
  public:
    MedianFilter();
    void init(MedianFilterInitStruct);
    void update();
    uint16_t getFiltered();
    void print(uint16_t printing_frequency, bool newline = 1);
};

