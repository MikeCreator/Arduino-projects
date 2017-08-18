    #include "LaserSensor.h"
    
    LaserSensor::LaserSensor(uint8_t _sensorPin, uint8_t _laserPin):
      sensorPin(_sensorPin),
      laserPin(_laserPin),
      current_millis (0),
      previous_millis(0),
      old_show_millis(0),
      current_micros(0),
      previous_micros(0),
      working_frequency(0),
      waiting_frequency(0),
      timing(0),
      timing_micros(0),
      switching_level(0),
      obstacle(false),
      sensor_value(0)
    {
      pinMode(sensorPin, INPUT);
      pinMode(laserPin, OUTPUT);
    }

    void LaserSensor::set_checking_frequencies(int frequency1, int frequency2)
    {
      working_frequency = frequency1;
      waiting_frequency = frequency2;
      timing = min(frequency1, frequency2);
    }
    
    void LaserSensor::set_switching_lvl(uint16_t level)
    {
     switching_level = level;
    }

    
    void LaserSensor::set_reading_delay(uint16_t value)
    {
      timing_micros = value;
    }
    
    void LaserSensor::start_detection()
    {
      current_millis = millis();
      current_micros = micros();
      if (current_millis - previous_millis >= timing)
      {
        LaserSensor::update();
      }

      if(current_millis < previous_millis)
      {
        previous_millis = current_millis;
      }
      
      if(current_micros < previous_micros)
      {
        previous_micros = current_micros;
      }
      
    }

    bool LaserSensor::has_obstacle()
    {
      return obstacle;
    }

    uint16_t LaserSensor::get_photres()
    {
      digitalWrite(laserPin, HIGH);
      if(current_micros - previous_micros >= timing_micros)
        {
          sensor_value = analogRead(sensorPin);
          digitalWrite(laserPin, LOW);
          previous_micros = current_micros;
        }
      return sensor_value;
    }

    

    void LaserSensor::print_photres(int timedelay, bool newline)
    {
      if(current_millis - old_show_millis >= timedelay)
      {
        if(newline) {
          Serial.println(get_photres());
        }
        else {
          Serial.print(get_photres());
        }
        old_show_millis = current_millis;
      }
      
      if(current_millis < old_show_millis) {
        old_show_millis = current_millis;
      }
    }

    inline void LaserSensor::update()
     {
        digitalWrite(laserPin, HIGH);
        if(current_micros - previous_micros >= timing_micros)
        {
          sensor_value = analogRead(sensorPin);
          digitalWrite(laserPin, LOW);
          set_obstalce();
          previous_micros = current_micros;
          previous_millis = current_millis;
        }
    }

     inline void LaserSensor::set_obstalce()
       {
          if(sensor_value < switching_level)
          {
            obstacle = true;
            timing = working_frequency;
          }
          else {
            obstacle = false;
            timing = waiting_frequency;
          }
       }


