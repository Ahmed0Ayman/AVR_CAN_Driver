/*
 * MCP2515.c
 *
 * Created: 5/20/2021 10:04:30 PM
 * Author : Ahmed_Ayman
 */ 

#define  F_CPU 160000000
#include <avr/io.h>
#include "HAL_SPI.h"
#include "MCP2515.h"
#include <util/delay.h>
#include "Lcd-Driver.h"


CANMesg_t TXMesg ;
CANMesg_t RecievedMesg ;
uint8_t counter ;
int main(void)
{
	DDRD = 0xe0;
	TXMesg.CANControl.EXT_Field = 1 ;
	TXMesg.CANControl.LEN_Field = 8;
	TXMesg.CANControl.RTR_Field = 0;
	TXMesg.ID = 0xff9 ;
	TXMesg.MesgData[0] = 1;
	TXMesg.MesgData[1] = 2;
	TXMesg.MesgData[2] = 3;
	TXMesg.MesgData[3] = 4;
	
	MCP2515_init();
	LCD_Initializaion();
    /* Replace with your application code */
    while (1) 
    {
		LCD_Send_An_Integer_With_CurrLoc(counter,3);
		MCP2515_SendCANmsg(&TXMesg,0);
		_delay_ms(200);
		LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);
    }
}

ISR(INT0_vect)
{

	counter++;

	MCP2515_receiveMesg(&RecievedMesg);

	PORTD = 0x80;

}