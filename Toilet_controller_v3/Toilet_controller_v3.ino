#include "LaserSensor.h"
#include "SoundSensor.h"
#include "Fan.h"

#define laser 2
#define photoresistor A3
#define light 8
#define trig_pin 6
#define echo_pin 5
#define average_deviation 0.3
#define reaction_speed 0.004

LaserSensor laser_sensor(photoresistor, laser);
SoundSensor soundSensor(trig_pin, echo_pin, average_deviation, reaction_speed);
Fan fan;

void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  SoundInitStruct soundSensorInit;
  //  soundSensorInit.trig_pin = 6;
  //  soundSensorInit.echo_pin = 5;
  //  soundSensorInit.average_deviation = 0.3; 
  //  soundSensorInit.reaction_speed = 0.004;
    soundSensorInit.distance = 114;
    soundSensorInit.allowed_deviation = 3;
    soundSensorInit.reading_frequency = 300;
    soundSensorInit.filter_time = 400;
  soundSensor.init(soundSensorInit);
  
  FanInitStruct fanInitStruct;
    fanInitStruct.fan_pin = 3;
    fanInitStruct.light_pin = light;
    fanInitStruct.stay_off_time = 90; //seconds
    fanInitStruct.stay_on_time = 120; //seconds
  fan.init(fanInitStruct);
    
  laser_sensor.set_checking_frequencies(3000, 75);
  laser_sensor.set_switching_lvl(350);
  laser_sensor.set_reading_delay(100);
}

void loop() {
  laser_sensor.start_detection();
  soundSensor.update();
  fan.update();
  
  //soundSensor.print(30, 1);
  //laser_sensor.print_photres(30, 1);

 if( laser_sensor.has_obstacle() || soundSensor.hasObstacle())
 {
  digitalWrite(light, HIGH);
 }
 else
 {
    digitalWrite(light, LOW);
 }
}


