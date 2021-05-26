
/*
 * Boot.c
 *
 * Created: 5/25/2021 7:59:01 PM
 *  Author: Ahmed_Ayman
 */ 

#include "Boot.h"




PRIVATE uint8_t PageNum  ;






/* 
 * brief : this function used to validity of received checksum
 * param :  LineParsing pointer to struct that hold the parsing information about specific line
 * return true or false 
 */ 
PUPLIC bool Validit_CheckSum( HEXImageLine_t * LineParsing)
{
	
	uint8_t CalCulCheckSum =0 , iterat = 0 ;
	
	for(iterat = 0   ; iterat<LineParsing->DataSize+4 ; iterat++)
	{
		eeprom_busy_wait();
		CalCulCheckSum += eeprom_read_byte((uint8_t*)((LineParsing->LineStartAddr) + iterat));
	}
	
	if	(((~CalCulCheckSum) +1)== LineParsing->ReceivedCheckSum)
	return true ;
	else
	return false ;
	
	
	
}/* END_FUN Validit_CheckSum() */



/* 
 * brief :  this function used to parse each line in the HEX file 
 *  each line has the following format    :llaaaatt[dd...]cc
 *
 * param :  LineStartAddr location of the first byte in the ImageLine 
 * param :  LineParsing pointer to struct that hold the parsing information about specific line 
 * return true or false 
 */ 
PUPLIC bool Parse_Image(uint8_t LineStartAddr , HEXImageLine_t * LineParsing)
{

	LineParsing->LineType = eeprom_read_byte((uint8_t*)(LineStartAddr+3));
	LineParsing->LineStartAddr = LineStartAddr ;
	if (LineParsing->LineType == HEX_LINE_DATA_RECORD)  /* data line */ 
	{
		LineParsing->DataSize = eeprom_read_byte((uint8_t*)LineStartAddr);
		LineParsing->NextLineStartAddr = LineStartAddr + LineParsing->DataSize + 5 ;
		LineParsing->ReceivedCheckSum = eeprom_read_byte((uint8_t*)(LineStartAddr + LineParsing->DataSize + 4));
		
	}
	else if(LineParsing->LineType  == HEX_LINE_END_FILE)
	{
		LineParsing->DataSize = 0 ;
		return true ;

	}
	
	return Validit_CheckSum(LineParsing);
	
	
	

}/* END_FUN Parse_Image() */





/* 
 * brief :  this function used to flash the specific image 
 *  each line has the following format    :llaaaatt[dd...]cc
 *
 * param :  LineParsing pointer to struct that hold the parsing information about specific line 
 * return true or false 
 */ 
 PUPLIC bool StoreHexImageInFlashImage( HEXImageLine_t * LineParsing)
{
	uint16_t Avr_Word = 0 ,Status =0  ;
	while(1)
	{

		eeprom_busy_wait ();
		boot_page_erase_safe (PageNum * SPM_PAGESIZE);
		boot_spm_busy_wait ();      /* Wait until the memory is erased */
		for (uint8_t iterat =0 ;iterat < SPM_PAGESIZE ;)
		{
			Status = Parse_Image(LineParsing->NextLineStartAddr,LineParsing) ;
			if(LineParsing->DataSize == 0 )  break;
					
			for (uint8_t DataSize = 1 ;DataSize < LineParsing->DataSize ;   )
			{
				Avr_Word = eeprom_read_byte((uint8_t*)(LineParsing->LineStartAddr+3+DataSize++));
				Avr_Word |= eeprom_read_byte((uint8_t*)(LineParsing->LineStartAddr+3+DataSize++)) << 8;

				boot_page_fill_safe (iterat, Avr_Word); /* write to the temp flash buffer */
								iterat +=2;
			}
			

			
			
		}

		boot_page_write_safe (PageNum * SPM_PAGESIZE);     /* Store temp flash buffer in flash page */
		boot_spm_busy_wait();							 /* Wait until write operation is ended */
		boot_rww_enable ();		
		if(LineParsing->DataSize == 0 ) break;	

	
		PageNum++; 

	}
	
	if ((Status == true))
	{
		return true ;
	}else{
		return false;
	}
	
	
	
	
}/* END_FUN StoreHexImageInFlashImage() */