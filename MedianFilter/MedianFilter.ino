#include "MedianFilter.h"

 MedianFilter MFilter;
 
void setup() {
  Serial.begin(9600);
 MedianFilterInitStruct InitStructure;
  InitStructure.pin = A0;
  InitStructure.reading_frequency = 30;
  MFilter.init(InitStructure);
}

void loop() {
  MFilter.update();
  MFilter.print(30);

}
