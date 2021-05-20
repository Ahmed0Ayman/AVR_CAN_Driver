/*
 * HAL_GPIO.c
 *
 * Created: 4/12/2021 3:13:45 PM
 *  Author: Ahmed_Ayman
 */ 


#include "HAL_GPIO.h"



void HAL_GPIO_INIT_PIN(GPIO_TypeDef * PORT, GPIO_InitTypeDef *  PIN_CONFIG)
{

		if(PIN_CONFIG->mode == GPIO_MODE_OUTPUT)
		{
			PORT->DDR_REG  |= PIN_CONFIG->pinS ;      //SET ALL PINS AS OUTPUT
			if(PIN_CONFIG->pull == GPIO_PULLUP)
			{
			PORT->PORT_REG |= PIN_CONFIG->pinS ;     // SET PULL UP RES.
			}
		}else{  // PINS MODE CONFIGURED AS INPUT
			
			PORT->DDR_REG &= ~(PIN_CONFIG->pinS);
		}

}

GPIO_PinState HAL_GPIO_READPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM)
{
	if(PORT->PIN_REG & PIN_NUM)
	{
		return GPIO_PIN_SET ;
	}
	else
	{
		return GPIO_PIN_RESET ;
	}
}

void HAL_GPIO_WRITEPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM,GPIO_PinState PIN_STATE)
{
	if(PIN_STATE != GPIO_PIN_RESET)
	{
		PORT->PORT_REG |= PIN_NUM ;
	}
	else
	{
		PORT->PORT_REG &= ~(PIN_NUM);
	}
	
}

void HAL_GPIO_WRITEPORT(GPIO_TypeDef * PORT,uint8_t PINS,GPIO_PinState PINS_STATE)
{
	PORT->PORT_REG &=~(PINS);
	PORT->PORT_REG |=(PINS_STATE);
}


void HAL_GPIO_TOGGLE_PIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM)
{
	    uint8_t old_state = PORT->PIN_REG;
		PORT->PORT_REG = (~((old_state)&(PIN_NUM))&(PIN_NUM));   
}

void HAL_GPIO_SLEEP_MODE_INIT(SleepModeConf * SleepModeInit)
{
	// enable external interrupt 
    /*
	here we init. external int source */

	GICR |= SleepModeInit->WakeUpSource ;  // enable external interrupt 
	if(SleepModeInit->WakeUpSource  == SLEEP_MODE_SOURCE_INT1)
	MCUCR |= (SleepModeInit->IntLevelSense) << 2; // select the INT1 interrupt level 
	else if((SleepModeInit->WakeUpSource)  == SLEEP_MODE_SOURCE_INT0)
	MCUCR |= SleepModeInit->IntLevelSense ; // select the INT0  interrupt level
	else
	MCUCSR |= SleepModeInit->IntLevelSense << 6 ;   // set INT2 level

	MCUCR |= SleepModeInit->Sleep_Mode << 4;

	SREG |= 0x80;    // set I bit enable global interrupt	
}

void SleepModeStart(void)
{
__asm__ __volatile__ ( "sleep\n\t" :: );   // call sleep instruction inline asm 
}

void SleepModeDisable(void)
{
	MCUCR &= 0x7f;  // set SE bit to enable sleep mode 
}

void SleepModeEnable(void)
{
	MCUCR |= 0x80;  // set SE bit to enable sleep mode 
}
