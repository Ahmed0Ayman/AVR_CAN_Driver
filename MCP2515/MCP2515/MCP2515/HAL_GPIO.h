/*
 * HAL_GPIO.h
 *
 * Created: 5/13/2021 11:19:19 PM
 *  Author: Ahmed_Ayman
 */


#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include "GPIOTYPEDEF.h"
#include <avr/io.h>
#include <avr/sleep.h>

typedef struct 
{
	uint8_t pinS ;
	uint8_t mode ;
	uint8_t pull ;

	
}GPIO_InitTypeDef;

typedef struct    // typedef struct hold the info. about the selected sleep mode 
{
	uint8_t Sleep_Mode ;
	uint8_t WakeUpSource ;
	uint8_t IntLevelSense ;

}SleepModeConf;


#define GPIO_PIN_0   0X01U
#define GPIO_PIN_1   0X02U
#define GPIO_PIN_2   0X04U
#define GPIO_PIN_3   0X08U
#define GPIO_PIN_4   0X10U
#define GPIO_PIN_5   0X20U
#define GPIO_PIN_6   0X40U
#define GPIO_PIN_7   0X80U
#define GPIO_PIN_ALL 0XFFU

#define GPIO_MODE_INPUT    0X00U
#define GPIO_MODE_OUTPUT    0X01U


#define  GPIO_NOPULL        0X00U
#define  GPIO_PULLUP        0X01U



/* IN data sheet their is a multiple sources 
* can wake up the MCU but the external interrupt in 
* a common one between all modes */
  

#define SLEEP_MODE_SOURCE_INT0         0X40U  

#define SLEEP_MODE_SOURCE_INT1         0X80U  

#define SLEEP_MODE_SOURCE_INT2         0X20U  

#define INT1_0_LOW_LEVEL_SET           0X00U

#define INT1_0_ANY_LEVEL_SET           0X01U

#define INT1_0_RISING_EDGE_SET         0X02U

#define INT1_0_FAILING_EDGE_SET        0X03U

#define INT2_FAILING_EDGE_SET          0X00U
 
#define INT2_RISING_EDGE_SET           0X01U


void HAL_GPIO_INIT_PIN(GPIO_TypeDef * PORT, GPIO_InitTypeDef *  PIN_CONFIG);

GPIO_PinState HAL_GPIO_READPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM);

void HAL_GPIO_WRITEPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM,GPIO_PinState PIN_STATE);

void HAL_GPIO_TOGGLE_PIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM);




// sleep function APIs

void HAL_GPIO_SLEEP_MODE_INIT(SleepModeConf * SleepModeInit);

void SleepModeDisable(void);

void SleepModeStart(void);

void HAL_GPIO_SLEEP_MODE_INIT(SleepModeConf * SleepModeInit);

void SleepModeEnable(void);

void HAL_GPIO_WRITEPORT(GPIO_TypeDef * PORT,uint8_t PINS,GPIO_PinState PINS_STATE);


#endif /* HAL_GPIO_H_ */