/*
* DHT11.h
*
* Created: 4/27/2019 8:42:31 PM
*  Author: ebrah
*/


#ifndef DHT11_H_
#define DHT11_H_

#include "GPIO.h"
#include "common.h"
#include <avr/io.h>

#define DHT11_PIN   (0)
#define D_PORT      DDRD
#define O_PORT		PORTD
#define I_PORT      PIND

typedef struct
{
	uint8 I_RH;
	uint8 D_RH;
	uint8 I_Temp;
	uint8 D_Temp;
	uint8 CheckSum;
} DHT11_t;


DHT11_t DHT11_1;

void DHT11_RequestData();
void DHT11_GetResponse();
void DHT11_ReceiveData(DHT11_t*);

#endif /* DHT11_H_ */