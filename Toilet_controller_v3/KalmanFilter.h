#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 


class KalmanFilter
{
  public:
  
    KalmanFilter(float averageDeviation, float reactionSpeed);
    float doFiltration(float val);  //filtration function
 
  private:
    float average_deviation; 
    float reaction_speed; // reaction speed to change (selected manually)
    float Pc;   //
    float G;    //
    float P;    //  auxiliary variables
    float Xp;   //
    float Zp;   //
    float Xe;   //
};

#endif
