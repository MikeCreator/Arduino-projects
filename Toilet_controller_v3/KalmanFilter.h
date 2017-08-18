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
  
    KalmanFilter(float averageDeviation, float reactionSpeed);  //среднее отклонение и скорость реакции
    float doFiltration(float val);  //функция фильтрации
 
  private:
    float average_deviation;  // среднее отклонение
    float reaction_speed; // скорость реакции на изменение (подбирается вручную)
    float Pc;
    float G;
    float P;
    float Xp;
    float Zp;
    float Xe;   
};

#endif
