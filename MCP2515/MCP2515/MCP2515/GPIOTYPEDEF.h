
/*
 * GPIOTYPEDEF.h
 *
 * Created: 5/13/2021 11:19:31 PM
 *  Author: Ahmed_Ayman
 */ 

#ifndef __GPIO_TYPEDEF_H_
#define __GPIO_TYPEDEF_H_
#include <stdint.h>


typedef struct 
{
	uint8_t PIN_REG;
	uint8_t DDR_REG;
	uint8_t PORT_REG;	
}GPIO_TypeDef;


typedef enum
{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET   =1
}GPIO_PinState;


#define PORTD_BASE    0X30U 
#define PORTC_BASE    0X33U 
#define PORTA_BASE    0X39U
#define PORTB_BASE    0X36U



#define SetBit(REG,BIT)            ((REG) |=(BIT))
#define ReadBit(REG,BIT)           (((REG)&(BIT))>>(BIT))
#define ClearBit(REG,BIT)          ((REG) &=(~BIT))
#define ClearREG(REG)              (REG=0x00U)
#define ReadREG(REG)               ((REG))




#define GPIOA  ((GPIO_TypeDef  *) PORTA_BASE)
#define GPIOB  ((GPIO_TypeDef  *) PORTB_BASE)
#define GPIOC  ((GPIO_TypeDef  *) PORTC_BASE)
#define GPIOD  ((GPIO_TypeDef  *) PORTD_BASE)








#endif /* TYPEDEF_H_ */