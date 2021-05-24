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



CANMesg_t TXMesg ;
CANMesg_t RecievedMesg ;
uint8_t counter ;
uint16_t  eepromadd ;
int main(void)
{
	/* vector table relocated to bootloader section */
		GICR = 1 << IVCE ; 
		GICR = 1 << IVSEL ;
	DDRD = 0xe0;
	
	/*
	 * here how to set the message to send 
	
	TXMesg.CANControl.EXT_Field = 1 ;
	TXMesg.CANControl.LEN_Field = 8;
	TXMesg.CANControl.RTR_Field = 0;
	TXMesg.ID = 0xff9 ;
	TXMesg.MesgData[0] = 1;
	TXMesg.MesgData[1] = 2;
	TXMesg.MesgData[2] = 3;
	TXMesg.MesgData[3] = 4;
	*/
	
	
	uint8_t sreg;  /* Temp var to hold the status register value */
	uint32_t page_Num = 0; /* here we have 4 pages form 0 -3 */
	uint16_t Avr_Word =0; 
	unsigned char *buf = NULL;	
	
	
	
	MCP2515_init();   /* initialize the MCP2515 chip */
	LCD_Initializaion(); /* initialize LCD */
	

    /* Replace with your application code */
    while (1) 
    {

		///* first in this example we will we polling mode next example we will we interrupt mode  */
		//if (MCP2515_Read_Register(CANINTF) & 0x01) 
		//{
				//MCP2515_receiveMesg(&RecievedMesg);
				//eeprom_write_block(RecievedMesg.MesgData ,eepromadd ,8 );
				//eepromadd += 8;
				//counter++ ;
			LCD_Send_An_Integer_WithLoc(2,10,counter,3);

		//}
		//
		/* now we received our message successfully so we need to carry out the boot operation */
		if (counter >= 22)
		{
		cli();

		/* Disable interrupts before start nay operation on the flash as explained in the data sheet */
		sreg = SREG;
		
		/* flash the code */
		for ( page_Num =0;page_Num <4 ;page_Num++)	 /* iterate on the for pages */
		{

			eeprom_busy_wait ();
			boot_page_erase_safe (page_Num*SPM_PAGESIZE);
			boot_spm_busy_wait ();      /* Wait until the memory is erased */

			for (int iterator=0; iterator<SPM_PAGESIZE; iterator+=2) /* fill the temp buffer */
			{
				
				Avr_Word = eeprom_read_byte(buf++);
				Avr_Word |= eeprom_read_byte(buf++) << 8;
				
				boot_page_fill_safe (iterator, Avr_Word); /* write to the temp flash buffer */
			}
			boot_page_write_safe (page_Num*SPM_PAGESIZE);     /* Store temp flash buffer in flash page */
			boot_spm_busy_wait();							 /* Wait until write operation is ended */
			boot_rww_enable ();


		}
		/* branch to the application section in the flash */
			LCD_Send_A_String_WithLoc(1,3,"branching to ");
			LCD_Send_A_String_WithLoc(2,3,"image");
			_delay_ms(3000);
			LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);

		SREG = sreg;
		asm ( "jmp 0x0000" );			
			
			
			
			
		}
		
	_delay_ms(200);
		
		LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);
    }
	return 0 ;
}

ISR(INT0_vect)
{

	counter++;

	MCP2515_receiveMesg(&RecievedMesg);
	eeprom_write_block(RecievedMesg.MesgData ,eepromadd ,8 );
	eepromadd += 8;
	PORTD = 0x80;

}