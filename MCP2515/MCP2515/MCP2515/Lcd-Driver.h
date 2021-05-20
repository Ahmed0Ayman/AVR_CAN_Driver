 /*
 * Lcd_Driver.h
 *
 * Created: 4/12/2021 3:14:06 PM
 * Author : Ahmed_Ayman
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#define  F_CPU 16000000
#include <stdint.h>
#include <util/delay.h>
#include "HAL_GPIO.h"


/*
these are the connected pins of lcd
you can change the pin in here 
*/ 



#define LCD_RS_GPIOB (GPIO_PIN_1)
#define LCD_EN_GPIOB (GPIO_PIN_3)
// we are always use LCD in write mode so you can connect  pin always to ground
#define LCD_RW_GPIOB (GPIO_PIN_2)
#define LCD_D4_GPIOA (GPIO_PIN_4)
#define LCD_D5_GPIOA (GPIO_PIN_5)
#define LCD_D6_GPIOA (GPIO_PIN_6)
#define LCD_D7_GPIOA (GPIO_PIN_7)



//some of common commands that used with lcd
#define LCD_COMMANED_CLEAR_LCD						0X01U
#define LCD_COMMANED_RETURN_HOME					0X02U
#define LCD_COMMANED_SHIFT_RIGHT					0X05U
#define LCD_COMMANED_SHIFT_LEFT						0X07U
#define LCD_COMMANED_CLEAR_CURSOR_ON				0X0AU
#define LCD_COMMANED_CLEAR_CURSOR_OFF				0X0CU
#define LCD_2LINE_4_BIT_MODE                        0x28u






void LCD_Send_A_Character_With_CurrLoc(uint8_t character);

void LCD_Send_A_Character_WithLoc(uint8_t y,uint8_t x,uint8_t ch);

void LCD_Send_A_String_With_CurrLoc(uint8_t *string);

void LCD_Send_A_Command(uint8_t command);

// used to initialize LCD
void LCD_Initializaion(void);

// move the cursor to specific location
void LCD_Goto_Location(uint8_t y , uint8_t x);

void LCD_Send_A_String_WithLoc(uint8_t y, uint8_t x, uint8_t *StringOfCharacters);

void LCD_Send_An_Integer_WithLoc(uint8_t y, uint8_t x, uint16_t IntegerToDisplay, uint8_t NumberOfDigits);

void LCD_Send_4BitData(uint8_t data);

void LCD_Send_A_Float_withloc(uint8_t y, uint8_t x ,  float number ,uint16_t precision);

void LCD_Send_An_Integer_With_CurrLoc(uint16_t IntegerToDisplay, uint8_t NumberOfDigits);



#endif /* LCD-DRIVER_H_ */