/*
 * MCP2515.h
 *
 * Created: 5/20/2021 10:05:10 PM
 *  Author: Ahmed_Ayman
 */ 

#ifndef __MCP2515__
#define __MCP2515__



#define F_CPU 16000000
#include "MCP2515_REG.h"
#include <util/delay.h>
#include <stdbool.h>
#include "HAL_EXIT.h"
#include "HAL_SPI.h"

#define PRIVATE static
#define PUBLIC 


typedef enum
{
	CAN_OK ,
	CAN_ERROR
}CANStatus;

typedef struct
{
	uint8_t LEN_Field : 4 ;
	uint8_t EXT_Field : 1 ;
	uint8_t RTR_Field : 1 ;
	
}CANControlField;

typedef struct
{
	uint32_t ID ;
	CANControlField CANControl;
	uint8_t MesgData[8];
	CANStatus status ;
	
}CANMesg_t;






#define NORMAL_MODE				(uint8_t)0X00
#define CONFIGURATION_MODE		(uint8_t)0X80
#define SLEEP_MODE				(uint8_t)0X20




/*
 * brief : this function used read command to read data from MCP specified register 
 * param : AddREG register addr that you need to read from 
 * return : the readed data 
 */
uint8_t MCP2515_Read_Register(uint8_t AddREG);



/*
 * brief : this function used write command to write data to MCP specified register 
 * param : AddREG register addr that you need to write data to 
 * param : value the value that you need to write to the register 
 * return : void 
 */
PUBLIC void MCP2515_Write_Register(uint8_t AddREG,uint8_t value);



/*
 * brief : this function used make software reset 
 * param : void 
 * return : void  
 */
PUBLIC void MCP2515_Rest(void);



/*
 * brief : this function used set bit timing registers 
 * param : rCNF1 CAN interface register 1 
 * param : rCNF2 CAN interface register 2
 * param : rCNF3 CAN interface register 3
 * return : void  
 */
PUBLIC void MCP2515_SetBitTiming(uint8_t rCNF1,uint8_t rCNF2,uint8_t rCNF3);





/*
 * brief : this function used set MCP mode operation 
 * param : mode 
 * return : void  
 */
PUBLIC void MCP2515_Set_OperMode(uint8_t mode);



/*
 * brief : this function used set MCP mask filter
 * param : n mask number
 * param : ID Identifier number
 * param : EXT used to determine if EXT identifier or normal id 
 * return : void  
 */
PUBLIC void MCP2515_SetMask(uint8_t n , uint32_t ID ,bool EXT);


/*
 * brief : this function used set MCP filter
 * param : n filter number
 * param : ID Identifier number
 * param : EXT used to determine if EXT identifier or normal id 
 * return : void  
 */
PUBLIC void MCP2515_SetFilter( uint8_t n, uint32_t ID ,bool EXT );


/*
 * brief : this function used set interrupt 
 * param : Init_Condition the interrupt enable bits
 * return : void  
 */
PUBLIC void MCP2515_Enable_Interrupt(uint8_t Init_Condition);



/*
 * brief : this function used set initialize the MCP  
 * param : void
 * return : void  
 */
PUBLIC void MCP2515_init(void);






/*
 * brief : this function used send message through CAN bus
 * param : TXnum buffer number
 * param : TransMesg struct hold all CAN message configuration 
 * return : void
 *  
 */
PUBLIC void MCP2515_SendCANmsg(CANMesg_t * TransMesg,uint8_t TXnum);





/*
 * brief : this function used to read pending message from Mailbox 
 * param : RecievedMesg pointer to struct that will hold all receive message information 
 * return : bool if false means their is no pending message to read   
 */
PUBLIC bool MCP2515_receiveMesg(CANMesg_t * RecievedMesg);




#endif