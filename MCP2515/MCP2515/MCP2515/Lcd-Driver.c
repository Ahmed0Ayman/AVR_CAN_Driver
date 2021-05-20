 /*
 * Lcd_Driver.c
 *
 * Created: 4/12/2021 3:14:06 PM
 * Author : Ahmed_Ayman
 */
#include "LCD-Driver.h"

// used by lcd_driver to configure gpio for gpio module
static GPIO_InitTypeDef LCD_GPIO_Handler ;

// start position for x & y location 
static uint8_t column_position [2] = {0x80,0xc0};


static void LCD_Triger_Enable(void);

static void LCD_Triger_Enable(void)
{
	HAL_GPIO_WRITEPIN(GPIOB,LCD_EN_GPIOB,GPIO_PIN_SET);  // set enable pin
	_delay_us(1);
	HAL_GPIO_WRITEPIN(GPIOB,LCD_EN_GPIOB,GPIO_PIN_RESET); // reset enable pin 
	_delay_ms(2);	
	
}

void LCD_Send_4BitData(uint8_t data)
{
	
		HAL_GPIO_WRITEPORT(GPIOA,LCD_D7_GPIOA|LCD_D6_GPIOA|LCD_D5_GPIOA|LCD_D4_GPIOA,(data & 0xf0));  // set the high nibble
		LCD_Triger_Enable();
		HAL_GPIO_WRITEPORT(GPIOA,LCD_D7_GPIOA|LCD_D6_GPIOA|LCD_D5_GPIOA|LCD_D4_GPIOA,((data & 0x0f)<<4)); // set the low nibble 
		LCD_Triger_Enable();

}

void LCD_Send_A_Character_With_CurrLoc(uint8_t character)
{
	HAL_GPIO_WRITEPIN(GPIOB,LCD_RS_GPIOB,GPIO_PIN_SET);
	HAL_GPIO_WRITEPIN(GPIOB,LCD_RW_GPIOB,GPIO_PIN_RESET);

	LCD_Send_4BitData(character);

}

void LCD_Send_A_Command(uint8_t command)
{
	
	HAL_GPIO_WRITEPIN(GPIOB,LCD_RS_GPIOB|LCD_RW_GPIOB,GPIO_PIN_RESET);
	LCD_Send_4BitData(command);
	
}


void LCD_Send_A_Character_WithLoc(uint8_t y,uint8_t x,uint8_t ch)
{
	
	LCD_Goto_Location(y,x);
	HAL_GPIO_WRITEPIN(GPIOB,LCD_RS_GPIOB,GPIO_PIN_SET);
	HAL_GPIO_WRITEPIN(GPIOB,LCD_RW_GPIOB,GPIO_PIN_RESET);
	LCD_Send_4BitData(ch);
	
}

void LCD_Send_A_String_With_CurrLoc(uint8_t *string)
{
	while (*string != 0)
	{
		LCD_Send_A_Character_With_CurrLoc(*string++);
	}
}

void LCD_Goto_Location(uint8_t y , uint8_t x)
{
	LCD_Send_A_Command(column_position[y-1]+(x-1));
}


void LCD_Initializaion(void)
{
	_delay_ms(20);
	// initialize portB pin 1,2,3 as output
	LCD_GPIO_Handler.mode = GPIO_MODE_OUTPUT ;
	LCD_GPIO_Handler.pinS = LCD_RW_GPIOB |LCD_RS_GPIOB |LCD_EN_GPIOB ;
	LCD_GPIO_Handler.pull =GPIO_NOPULL ;
	HAL_GPIO_INIT_PIN(GPIOB,&LCD_GPIO_Handler);
	
	// initialize portA pin 4,5,6,7 as output	
	LCD_GPIO_Handler.pinS = LCD_D4_GPIOA|LCD_D5_GPIOA|LCD_D6_GPIOA|LCD_D7_GPIOA;
	HAL_GPIO_INIT_PIN(GPIOA,&LCD_GPIO_Handler);

	LCD_Send_A_Command(0x33U); // LCD initialization command 
	LCD_Send_A_Command(0x32U);
	LCD_Send_A_Command(LCD_2LINE_4_BIT_MODE);
	LCD_Send_A_Command(LCD_COMMANED_CLEAR_CURSOR_OFF);
	LCD_Send_A_Command(LCD_COMMANED_CLEAR_LCD);
	
}

void LCD_Send_A_String_WithLoc(uint8_t y, uint8_t x, uint8_t *StringOfCharacters)
{
	LCD_Goto_Location(y,x);
	while (*StringOfCharacters != 0)
	{
		LCD_Send_A_Character_With_CurrLoc(*StringOfCharacters++);
	}
}

void LCD_Send_An_Integer_WithLoc(uint8_t y, uint8_t x, uint16_t IntegerToDisplay, uint8_t NumberOfDigits)
{
	uint8_t StringToDisplay[NumberOfDigits];
	itoa(IntegerToDisplay,StringToDisplay,10);
	for (uint16_t i=0;i<NumberOfDigits;i++)
	LCD_Send_A_Character_With_CurrLoc(' ');
	
	LCD_Send_A_String_WithLoc(y,x,StringToDisplay);
}

void LCD_Send_A_Float_Withloc(uint8_t y, uint8_t x ,  float number , uint16_t precision)
{
	LCD_Goto_Location(y,x);
	
	float after=10.0;

	if (precision == 1 )		after = after *1;

	else if (precision==2)	after = 100.0;

	else if (precision==3)	after = 1000.0;

	else if (precision==4)	after = 10000.0;

	else if (precision==5)	after = 100000.0;

	else if (precision==6)	after = 1000000.0;

	else if (precision==7)	after = 10000000.0;

	else if (precision==8)	after = 100000000.0;

	uint16_t intValue = (uint16_t)number;
	float diffValue = number - (float)intValue;
	uint16_t decimalValue = (uint16_t)(diffValue * after);
	
	
	LCD_Send_An_Integer_With_CurrLoc(intValue,5);
	LCD_Send_A_Character_With_CurrLoc('.');
	LCD_Send_An_Integer_With_CurrLoc(decimalValue,5);
}

void LCD_Send_An_Integer_With_CurrLoc(uint16_t IntegerToDisplay, uint8_t NumberOfDigits)
{
		uint8_t StringToDisplay[NumberOfDigits];
		itoa(IntegerToDisplay,StringToDisplay,10);
		LCD_Send_A_String_With_CurrLoc(StringToDisplay);
	
}

