#pragma once
#include <avr/pgmspace.h>

	class Analog_Temp
	{
	
		int SensorPin;
		int NUMSAMPLES = 5;
		int BEDTEMPTABLE_LEN;
		float average;
		int samples[5];
		bool nextstep;
		unsigned long prevmillis;
		unsigned long oldmillis;
		unsigned long showmillis;
		int i;
		int timedelay;

		unsigned long Showfrequency;
		bool NewLine;
		char* Message;

		static const short temptable_11[12][2];

		float analog_temp(int);
		void Gettemp();

	public:
		Analog_Temp(int);	
		float CurrentTemp();
		void PeriodShowTemp(unsigned long frequency = 1000, bool enter = 0, char* message = " ");
	};

