#include "MedianFilter.h"

MedianFilter::MedianFilter():
queue_size(SIZE)
{}

void MedianFilter::init(MedianFilterInitStruct initStruct)
{
  pin = initStruct.pin;
  reading_frequency = initStruct.reading_frequency;
  pinMode(pin, INPUT);
}

void MedianFilter::update()
{
  current_millis = millis();
  if(current_millis - previous_millis >= reading_frequency)
  {
    // adding new value to the queue
    for(uint8_t i(1); i < queue_size; i++)
    {
      queue[i-1] = queue[i];
    }
    queue[queue_size-1] = analogRead(pin);

    previous_millis = current_millis;
  }

  // out of range defense
  if (previous_millis > current_millis) previous_millis = current_millis;
}

uint16_t MedianFilter::getFiltered()
{
  //creating a temporary array
  uint16_t temp_queue[queue_size];
  for(uint8_t i(0); i < SIZE; i++)
  {
    temp_queue[i] = queue[i];
  }
  // sorting it
  for(uint8_t i(0); i < queue_size; i++)
    for(uint8_t j(1); j < queue_size-i; j++)
      if(temp_queue[j-1] > temp_queue[j])
      {
        uint16_t temp = temp_queue[j-1];
        temp_queue[j-1] = temp_queue[j];
        temp_queue[j] = temp;
      }
    
  register uint16_t result = temp_queue[queue_size/2];
  return result;
}

void MedianFilter::print(uint16_t printing_frequency, bool newline = 1)
{
  //send data to serial port
  if(current_millis - previous_print_millis >= printing_frequency)
  {
    Serial.print(analogRead(pin));
    Serial.print(" ");
    if (newline)
      {
        Serial.println(getFiltered());
      }
    else
      {
        Serial.print(getFiltered());
        Serial.print(" ");
      }
    previous_print_millis = current_millis;
  }
    // out of range defense
    if (previous_print_millis > current_millis) previous_print_millis = current_millis;

}
