/*
 * I2C.c
 *
 * Created: 3/12/2014 12:05:38 PM
 *  Author: Ebrahim Hamouda
 */
#include "I2C.h"
#include <avr/interrupt.h>


/* MACROS

*/
#define SLAVE_ADD 0x01
#define I2C_BUSY (!(TWCR & (1 << TWINT)))
#define CAN_FRAM_SIZE 2

Call_backTX_t Static_callBackTx;
Call_backRecive_t Static_CallBackRX;

volatile uint8 Current_Index=0 ;
volatile uint8 CanFrame[8];

ISR(TWI_vect)
{
	switch (I2C_GetStatus())
	{
	case SALVE_RX_DATA_ACK:
		CanFrame[Current_Index++] = I2C_ReadWithACKAndInterrupt();
		break;
	case SALVE_RX_ADD_ACK:
		Current_Index = 0;
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
	case STOP_RX :
	/*
	Make sure you are in really stop 
	*/
	if (I2C_GetStatus() == STOP_RX)
	{
		Static_CallBackRX(CanFrame);
		TWCR |= (1 << TWINT);
	}
	break;
	case 0x28 :
		
	default:
		break;
	}
}

void I2C_Init()
{
	// Bit Rate: 62.500 kHz
	TWBR = 0x00;
	TWSR = 0x00;
	// General Call Recognition: ON
	TWAR = 0x01; 
	TWCR = (1 << TWEN);	   //enable TWI
}

void I2C_setOwnSlaveAddress(uint8 add)
{
	TWAR = add << 1; 
}

void I2C_Start(void)
{
	/* Clear the TWINT flag before sending the start bit TWINT=1 "MUST"
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	// Wait for TWINT flag set in TWCR Register (start bit is send successfully)
	while (I2C_BUSY);
}

void I2C_Stop(void)
{
	/* Clear the TWINT flag before sending the stop bit TWINT=1 
	 * send the stop bit by TWSTO=1 
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void I2C_Write(unsigned char data)
{
	// Put data On TWI Register
	TWDR = data;
	/* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	// Wait for TWINT flag set in TWCR Register(data is send successfully)
	while (I2C_BUSY)
		;
}

void I2C_TxWithInterrupt(unsigned char data)
{
	// Put data On TWI Register
	TWDR = data;
	/* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 * Enable interrupt bit
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
	//don't have to Wait for TWINT flag set in TWCR Register(data is send successfully)
}

unsigned char I2C_ReadWithACK(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	// Wait for TWINT flag set in TWCR Register (data received successfully)
	while (I2C_BUSY)
		;
	// Read Data
	return TWDR;
}

unsigned char I2C_ReadWithACKAndInterrupt(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 * Enable interrupt 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE);

	/* don't have to Wait for TWINT flag set in TWCR Register 
	(data received successfully) 
     Read Data*/
	return TWDR;
}

void I2C_AssignCallBackRX(Call_backRecive_t pass_callBack)
{
	/*
	*assign callBack function to call when data received  
	*/
	Static_CallBackRX = pass_callBack;
	TWCR |= (1 << TWEN) | (1 << TWEA) | (1 << TWIE); // to enable interrupts
}

void I2C_WaitForRx()
{
	/*
	*assign callBack function to call when data received  
	*/
	TWCR |= (1 << TWEN) | (1 << TWEA) | (1 << TWIE); // to enable interrupts
}

unsigned char I2C_ReadWithNACK(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	// Wait for TWINT flag set in TWCR Register (data received successfully)
	while (I2C_BUSY)
		;
	// Read Data
	return TWDR;
}

unsigned char I2C_GetStatus(void)
{
	unsigned char status;
	status = TWSR & 0xF8; //masking to eliminate prescaler 3 bits
	return status;
}

void I2C_AssignCallBackTx(Call_backTX_t pass_callBackFuncation)
{
	Static_callBackTx = pass_callBackFuncation;
}

void i2c_disable_interrupt()
{
	TWCR &= ~(1 << 0); // disable interrupt
}
