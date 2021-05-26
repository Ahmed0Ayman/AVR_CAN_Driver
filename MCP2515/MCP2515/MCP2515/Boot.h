
/*
 * Boot.h
 *
 * Created: 5/25/2021 7:59:16 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef __BootLoader__
#define __BootLoader__




#include <stdbool.h>
#include <stdint.h>
#include <avr/boot.h>
#include <avr/eeprom.h>



#define PRIVATE static
#define PUPLIC


#define HEX_LINE_DATA_RECORD			0x00u

#define HEX_LINE_END_FILE				0x01u

#define HEX_LINE_EXTENDED_SEGMANT		0x02u




typedef struct 
{
	uint8_t LineStartAddr ;
	uint8_t NextLineStartAddr ;
	uint8_t DataSize ;
	uint8_t ReceivedCheckSum ;
	uint8_t LineType  ;
	
}HEXImageLine_t;




/* 
 * brief : this function used to validity of received checksum
 * param :  LineParsing pointer to struct that hold the parsing information about specific line 
 * return true or false 
 */ 
PUPLIC bool Validit_CheckSum( HEXImageLine_t * LineParsing);





/* 
 * brief :  this function used to parse each line in the HEX file 
 *  each line has the following format    :llaaaatt[dd...]cc
 *
 * param :  LineStartAddr location of the first byte in the ImageLine 
 * param :  LineParsing pointer to struct that hold the parsing information about specific line 
 * return true or false 
 */ 
PUPLIC bool Parse_Image(uint8_t LineStartAddr , HEXImageLine_t * LineParsing);








/* 
 * brief :  this function used to flash the specific image 
 *  each line has the following format    :llaaaatt[dd...]cc
 *
 * param :  LineParsing pointer to struct that hold the parsing information about specific line 
 * return true or false 
 */ 
 PUPLIC bool StoreHexImageInFlashImage( HEXImageLine_t * LineParsing);














#endif