#include "KalmanFilter.h"

  KalmanFilter::KalmanFilter(float averageDeviation, float reactionSpeed):
    average_deviation(averageDeviation),
    reaction_speed   (reactionSpeed),
    Pc  (0.0),
    G   (0.0),
    P   (1.0),
    Xp  (0.0),
    Zp  (0.0),
    Xe  (0.0)
    {}

 float KalmanFilter::doFiltration(float val) {  //функция фильтрации
  Pc = P + reaction_speed;
  G = Pc/(Pc + average_deviation);
  P = (1-G)*Pc;
  Xp = Xe;
  Zp = Xp;
  Xe = G*(val-Zp)+Xp;
  return(Xe);
}
