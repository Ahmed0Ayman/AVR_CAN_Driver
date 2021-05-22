
/*
 * HAL_EXTI.h
 *
 * Created: 5/8/2021 12:58:53 AM
 *  Author: Ahmed_Ayman
 */ 
#ifndef __EXTIT__
#define __EXTIT__

#include <avr/interrupt.h>
#include "HAL_GPIO.h"
#include <stdint.h>

typedef void(*PtrFun)(void); 

#define EXTI_NUM_0					0x01u
#define EXTI_NUM_1					0x02u
#define EXTI_NUM_2					0x00u
	
#define  EXTI_EDGE_LOW_LENEL		0X00U       
#define  EXTI_EDGE_ANY_LENEL        0X01U
#define  EXTI_EDGE_FAILING_EDGE     0X02U       
#define  EXTI_EDGE_RISING_EDGE      0X03U


typedef struct
{
	uint8_t EXTI_NUM ;				  /* must be one of EXTI_NUM_*/
	uint8_t EXTI_EDGE_DETECTION ;    /* must be one of EXTI_EDGE_ */
	
}EXIT_Handler_t;



/*
 * brief this function used to enable and configure the selected INIT 
 * param : Handler is pointer to struct hold all INIT configurations 
 * return : void 
 */
void EXTI_Init(EXIT_Handler_t * Handler);




/*
 * brief this function used to call back user function when the INIT0 is triggered
 * param : PtrToFun pointer to  user function  
 * return : void 
 */
void EXIT_INT0_CallBack(PtrFun PtrToFun);




/*
 * brief this function used to call back user function when the INIT1 is triggered
 * param : PtrToFun pointer to  user function  
 * return : void 
 */
void EXIT_INT1_CallBack(PtrFun PtrToFun);




/*
 * brief this function used to call back user function when the INIT2 is triggered
 * param : PtrToFun pointer to  user function  
 * return : void 
 */
void EXIT_INT2_CallBack(PtrFun PtrToFun);






/*
 * brief : this function used to disable the determined INIT  
 * param : Handler is a pointer to struct that hold all information a bout the INIT 
 * return : void 
*/  
void EXIT_DISABLE(EXIT_Handler_t * Handler);







/*
 * brief : this function used to generate an software interrupt on a configured pin 
 * param : Handler is a pointer to struct that hold all information a bout the INIT 
 * return : void 
*/  
void EXTI_Gen_SoftWareINIT(EXIT_Handler_t * Handler);



#endif