#include "Analog_Temp.h"
#include <avr/pgmspace.h>
#include <Arduino.h>
Analog_Temp::Analog_Temp(int pin)
	{
		SensorPin = pin;
		pinMode(SensorPin, INPUT);
		prevmillis = 0;
		oldmillis = 0;
		showmillis = 0;
    i = 0;
    timedelay = 50;
	BEDTEMPTABLE_LEN = (sizeof(temptable_11) / sizeof(*temptable_11));
    
	}

	void Analog_Temp::Gettemp()
	{
		unsigned long currentmillis = millis();
		// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
		if (i < NUMSAMPLES && currentmillis - prevmillis >= timedelay)
		{
			samples[i] = analogRead(SensorPin);
			i++;
			prevmillis = currentmillis;
			if (i == NUMSAMPLES)
			{
				i = 0;
				nextstep = true;
			}
		}
		// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ

		if (nextstep == true)
		{
			average = 0;
			for (int j = 0; j < NUMSAMPLES; j++)
			{
				average += samples[j];
			}
			average /= NUMSAMPLES;
			nextstep = false;
		}
		// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
	}

	float Analog_Temp::CurrentTemp()
	{
		unsigned long currentmillis = millis();
		Gettemp();
		if (currentmillis <= timedelay*NUMSAMPLES)
			return  analog_temp(analogRead(SensorPin));
		else return analog_temp(average);
		
	}

//int BEDTEMPTABLE_LEN = (sizeof(temptable_11) / sizeof(*temptable_11));
#define PGM_RD_W(x)   (short)pgm_read_word(&x)
	//short PGM_RD_W(short x)
	//{ 
	//	return x;
	//}
	/////////////////
	float Analog_Temp::analog_temp(int raw)
	{
		float celsius = 0;
		byte i;

		for (i = 1; i < BEDTEMPTABLE_LEN; i++)
		{
			if (PGM_RD_W(temptable_11[i][0]) > raw)
			{
				celsius = PGM_RD_W(temptable_11[i - 1][1]) +
					(raw - PGM_RD_W(temptable_11[i - 1][0])) *
					(float)(PGM_RD_W(temptable_11[i][1]) - PGM_RD_W(temptable_11[i - 1][1])) /
					(float)(PGM_RD_W(temptable_11[i][0]) - PGM_RD_W(temptable_11[i - 1][0]));
				break;
			}
		}

		// Overflow: Set to last value in the table
		if (i == BEDTEMPTABLE_LEN) celsius = PGM_RD_W(temptable_11[i - 1][1]);

		return celsius;
	}

	void Analog_Temp::PeriodShowTemp(unsigned long frequency, bool enter, char* message)
	{
		Showfrequency = frequency;
		NewLine = enter;
		int i(0);
		Message = message;

		unsigned long currentmillis = millis();
		Gettemp();

		if (currentmillis - showmillis >= Showfrequency)
		{
			Serial.print(Message);
			if (NewLine) Serial.println(analog_temp(average));
			else Serial.print(analog_temp(average));
			showmillis = currentmillis;
		}
	}

  const short Analog_Temp::temptable_11[12][2] PROGMEM = {
    { 832, 65 },
    { 858, 60 },
    { 883, 55 },
    { 904, 50 },
    { 924, 45 },
    { 940, 40 },
    { 955, 35 },
    { 968, 30 },
    { 977, 25 },
    { 987, 20 },
    { 994, 15 },
    { 999, 10 }
  };

