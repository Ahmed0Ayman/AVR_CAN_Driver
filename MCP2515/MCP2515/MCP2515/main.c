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
#include <avr/boot.h>
#include <avr/eeprom.h>
#include "Boot.h"



CANMesg_t RecievedMesg ;
uint16_t  eepromadd ;
HEXImageLine_t  LineParsing;

uint8_t MesStartLine =0,LineDataSize =0  ,ImageIsReady;


int main(void)
{
	
	
	
	/* vector table relocated to bootloader section */
		GICR = 1 << IVCE ; 
		GICR = 1 << IVSEL ;
		DDRD = 0xe0;
	
	uint8_t sreg;  /* Temp var to hold the status register value */


	
	MCP2515_init();   /* initialize the MCP2515 chip */
	LCD_Initializaion(); /* initialize LCD */
	

    /* Replace with your application code */
    while (1) 
    {

		LCD_Send_A_String_With_CurrLoc((uint8_t *)"Waiting Image");

		if(eepromadd > MesStartLine)
		{
			LineDataSize =  eeprom_read_byte((uint8_t *)MesStartLine);
			MesStartLine += eeprom_read_byte((uint8_t *)MesStartLine)+5;
			if(LineDataSize == 0x00 ) ImageIsReady = true;
		}
		
		
		
		
		
		
		/* now we received our message successfully so we need to carry out the boot operation */
		if (ImageIsReady)
		{
		cli();

		/* Disable interrupts before start nay operation on the flash as explained in the data sheet */
		sreg = SREG;
		
		if(StoreHexImageInFlashImage( & LineParsing)){
		
		/* branch to the application section in the flash */
			LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);
			LCD_Send_A_String_WithLoc(1,3,(uint8_t *)"branching to ");
			LCD_Send_A_String_WithLoc(2,3,(uint8_t *)"image");
			_delay_ms(3000);
			LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);

			SREG = sreg;
			asm ( "jmp 0x0000" );			
			//
			
		}
		else
		{
			LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);
			LCD_Send_A_String_With_CurrLoc((uint8_t *)"Invalid Image");
			
		}
		
		    }
	_delay_ms(200);
		
		LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);

	
	}
	return 0 ;
}

ISR(INT0_vect)
{
	
	MCP2515_receiveMesg(&RecievedMesg);
	eeprom_write_block((void *)RecievedMesg.MesgData ,(void *)eepromadd ,8 );
	eepromadd += 8;


}