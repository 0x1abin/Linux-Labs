//
//mydht11.c
//
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32

int pinNumber =1; //use gpio1 to read data



uint8 readSensorData(int *tmp, int *rh)
{
	uint32 databuf;
	uint8 crc;
	uint8 i;

	pinMode(pinNumber,OUTPUT); // set mode to output
	digitalWrite(pinNumber, 1); // output a high level
	delay(2000);

	pinMode(pinNumber,OUTPUT); // set mode to output
	digitalWrite(pinNumber, 0); // output a high level
	delay(25);
	digitalWrite(pinNumber, 1); // output a low level
	pinMode(pinNumber, INPUT); // set mode to input
	pullUpDnControl(pinNumber,PUD_UP);

	delayMicroseconds(27);
	if(digitalRead(pinNumber)==0) //SENSOR ANS
	{
		while(!digitalRead(pinNumber)); //wait to high

		for(i=0; i<32; i++)
		{
			while(digitalRead(pinNumber)); //data clock start
			while(!digitalRead(pinNumber)); //data start
			delayMicroseconds(HIGH_TIME);
			databuf*=2;
			if(digitalRead(pinNumber)==1) //1

			{
				databuf++;
			}
		}

		for(i=0; i<8; i++)
		{
			while(digitalRead(pinNumber)); //data clock start
			while(!digitalRead(pinNumber)); //data start
			delayMicroseconds(HIGH_TIME);
			crc*=2;
			if(digitalRead(pinNumber)==1) //1
			{
				crc++;
			}
		}
		
		*tmp = (databuf>>8)&0xff;
		*rh  = (databuf>>24)&0xff;
		
		return 1;
	}
	else
	{
		return 0;
	}
}

void Init_DHT11()
{
	printf("Use GPIO1 to read data!\n");

	if (-1 == wiringPiSetup())
	{
		printf("Setup wiringPi failed!");
		return 1;
	}

	pinMode(pinNumber, OUTPUT); // set mode to output
	digitalWrite(pinNumber, 1); // output a high level
	printf("Init_DHT11_Over!\n");
}

int main (void)
{

	Init_DHT11();
	
	
}

