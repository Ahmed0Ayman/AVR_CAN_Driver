/*
 * MCP2515.c
 *
 * Created: 5/20/2021 10:04:59 PM
 *  Author: Ahmed_Ayman
 */ 



#include "MCP2515.h"

/******* this function that take add of register which i want to read and return the
data which stored in this location
*************************/


PRIVATE SPI_Handler_t  MCP2515_SPIHandler ;

PRIVATE EXIT_Handler_t MCP2515_EXTIT ;



/*
 * brief : this function used read command to read data from MCP specified register 
 * param : AddREG register addr that you need to read from 
 * return : the readed data 
 */
PUBLIC uint8_t MCP2515_Read_Register(uint8_t AddREG)
{
	uint8_t Instruction[] = {READ_INSTRUCTION,AddREG,0x00} ;
	HAL_SPI_TransmitRecive(&MCP2515_SPIHandler,Instruction,Instruction,3);
	return Instruction[2] ;



}/* END_FUN MCP2515_Read_Register() */



/*
 * brief : this function used write command to write data to MCP specified register 
 * param : AddREG register addr that you need to write data to 
 * param : value the value that you need to write to the register 
 * return : void 
 */
PUBLIC void MCP2515_Write_Register(uint8_t AddREG,uint8_t value)
{
	uint8_t Instruction[] = {WRITE_INSTRUCTION,AddREG,value} ;
	HAL_SPI_Transmit(&MCP2515_SPIHandler,Instruction,3);


}/* END_FUN MCP2515_Write_Register() */



/*
 * brief : this function used make software reset 
 * param : void 
 * return : void  
 */
PUBLIC void MCP2515_Rest(void)
{
	uint8_t Instruction = RESET_INSTRUCTION ;
	HAL_SPI_Transmit(&MCP2515_SPIHandler,&Instruction,1);
	_delay_ms(20);



}/* END_FUN MCP2515_Rest() */





/*
 * brief : this function used set bit timing registers 
 * param : rCNF1 CAN interface register 1 
 * param : rCNF2 CAN interface register 2
 * param : rCNF3 CAN interface register 3
 * return : void  
 */
PUBLIC void MCP2515_SetBitTiming(uint8_t rCNF1,uint8_t rCNF2,uint8_t rCNF3)
{

	MCP2515_Write_Register(CNF1,rCNF1);
	MCP2515_Write_Register(CNF2,rCNF2);
	MCP2515_Write_Register(CNF3,rCNF3);
	
	
	
}/* END_FUN MCP2515_SetBitTiming() */



/*
 * brief : this function used set MCP mode operation 
 * param : mode 
 * return : void  
 */
PUBLIC void MCP2515_Set_OperMode(uint8_t mode)
{
	uint8_t Instruction[] = {WRITE_INSTRUCTION,CANCTRL,mode} ;
	HAL_SPI_Transmit(&MCP2515_SPIHandler,Instruction,3);



}/* END_FUN MCP2515_Set_OperMode() */





/*
 * brief : this function used set MCP mask filter
 * param : n mask number
 * param : ID Identifier number
 * param : EXT used to determine if EXT identifier or normal id 
 * return : void  
 */
PUBLIC void MCP2515_SetMask(uint8_t n , uint32_t ID ,bool EXT)
{
	

	if (EXT)  // the length of ID is 29 bit
	{
		MCP2515_Write_Register(RXMnSIDH(n),(uint8_t)(ID>>(uint8_t)3));
		MCP2515_Write_Register(RXMnSIDL(n),(uint8_t)((ID<<(uint8_t)5)|(ID>>(uint8_t)27)|(1<<EXIDE)));
		MCP2515_Write_Register(RXMnEID0(n),(uint8_t)(ID>>(uint8_t)11));
		MCP2515_Write_Register(RXMnEID8(n),(uint8_t)(ID>>(uint8_t)19));
	}
	else
	{
		MCP2515_Write_Register(RXMnSIDH(n),(uint8_t)(ID>>(uint8_t)3));
		MCP2515_Write_Register(RXMnSIDL(n),(uint8_t)(ID<<(uint8_t)5));
	}




}/* END_FUN MCP2515_SetMask() */


/*
 * brief : this function used set MCP filter
 * param : n filter number
 * param : ID Identifier number
 * param : EXT used to determine if EXT identifier or normal id 
 * return : void  
 */
PUBLIC void MCP2515_SetFilter( uint8_t n, uint32_t ID ,bool EXT )
{

	if (EXT)  // the length of ID is 29 bit
	{
		MCP2515_Write_Register(RXFnSIDH(n),(uint8_t)(ID>>(uint8_t)3));
		MCP2515_Write_Register(RXFnSIDL(n),(uint8_t)((ID<<(uint8_t)5)|(ID>>(uint8_t)27)|(1<<EXIDE)));
		MCP2515_Write_Register(RXFnEID0(n),(uint8_t)(ID>>(uint8_t)11));
		MCP2515_Write_Register(RXFnEID8(n),(uint8_t)(ID>>(uint8_t)19));
	}
	else
	{
		MCP2515_Write_Register(RXFnSIDH(n),(uint8_t)(ID>>(uint8_t)3));
		MCP2515_Write_Register(RXFnSIDL(n),(uint8_t)(ID<<(uint8_t)5));
	}



}/* END_FUN MCP2515_SetFilter() */



/*
 * brief : this function used set interrupt 
 * param : void
 * return : void  
 */
PUBLIC void MCP2515_Enable_Interrupt(uint8_t Init_Condition)
{
	uint8_t Instruction[] = {WRITE_INSTRUCTION,CANINTE,Init_Condition} ;
	HAL_SPI_Transmit(&MCP2515_SPIHandler,Instruction,3);

}/* END_FUN MCP2515_Enable_Interrupt() */

/*
 * brief : this function used set initialize the MCP  
 * param : void
 * return : void  
 */
void MCP2515_init(void)
{
	MCP2515_EXTIT.EXTI_NUM = EXTI_NUM_0 ;
	MCP2515_EXTIT.EXTI_EDGE_DETECTION = EXTI_EDGE_LOW_LENEL ;
	
	MCP2515_SPIHandler.SPI_init.Mode = SPI_MODE_MASTER ;
	MCP2515_SPIHandler.SPI_init.CLKPrescaler = SPI_CLKPrescaler_2 ;
	HAL_SPI_Init(&MCP2515_SPIHandler);
	MCP2515_Rest();
	MCP2515_Enable_Interrupt(0x03);
	MCP2515_Set_OperMode(CONFIGURATION_MODE);
	MCP2515_SetBitTiming(0x03,0xFA,0x87);
	MCP2515_SetFilter((uint8_t)0,(uint8_t)0x0,(uint8_t)0x123);
	MCP2515_SetMask((uint8_t)0,(uint8_t)0x00,(uint8_t)0xff);
	MCP2515_Write_Register(TXRTSCTRL,0x07);
	MCP2515_Set_OperMode(NORMAL_MODE);
	EXTI_Init(&MCP2515_EXTIT);
}
/* END_FUN MCP2515_init() */




/*
 * brief : this function used send message through CAN bus
 * param : TXnum buffer number
 * param : TransMesg struct hold all CAN message configuration 
 * return : void
 *  
 */
PUBLIC void MCP2515_SendCANmsg(CANMesg_t * TransMesg,uint8_t TXnum)
{
	uint8_t dataTx[9] ;
	unsigned char iteration =0;

	if(TransMesg->CANControl.EXT_Field)
	{
		MCP2515_Write_Register(TXBnSIDH(TXnum),(unsigned char)(TransMesg->ID>>3));
		MCP2515_Write_Register((TXBnSIDL(TXnum)),(unsigned char)(TransMesg->ID<<5)
		|(1<<EXIDE)|(unsigned char)(TransMesg->ID>>27));
		MCP2515_Write_Register(TXBnEID8(TXnum),(unsigned char)(TransMesg->ID>>19));
		MCP2515_Write_Register(TXBnEID0(TXnum),(unsigned char)(TransMesg->ID>>11));
	} else {
		MCP2515_Write_Register(TXBnSIDH(TXnum),(unsigned char)(TransMesg->ID>>3));
		MCP2515_Write_Register(TXBnSIDL(TXnum),(unsigned char)(TransMesg->ID<<5));
	}
	/* Setup message length and RTR bit */
	
	if(TransMesg->CANControl.RTR_Field)
	{
	MCP2515_Write_Register(TXBnDLC(TXnum),(1 << RTR));	
	}else{
		
	MCP2515_Write_Register(TXBnDLC(TXnum),(TransMesg->CANControl.LEN_Field));
	dataTx[0] =LOADTX_INSTRUCTION|0x01u;
	/* Store the message into the buffer */
	for(iteration=0; iteration< TransMesg->CANControl.LEN_Field ; iteration++)
	dataTx[iteration+1]= TransMesg->MesgData[iteration];
	HAL_SPI_Transmit(&MCP2515_SPIHandler,dataTx,9);
	}
	/* Send request to send */
	
	dataTx[0] = 0x81+TXnum;
	HAL_SPI_Transmit(&MCP2515_SPIHandler,dataTx,1);
	
	
	
}/* END_FUN MCP2515_SendCANmsg() */







/*
 * brief : this function used to read pending message from Mailbox 
 * param : RecievedMesg pointer to struct that will hold all receive message information 
 * return : bool if false means their is no pending message to read   
 */

PUBLIC bool MCP2515_receiveMesg(CANMesg_t * RecievedMesg)
{
	uint8_t CANReaddata =0,MAilBoxNum =0 ;
	
	CANReaddata=MCP2515_Read_Register(CANSTAT);
	if((CANReaddata == 0x0c))
	{
		MAilBoxNum = 0 ;
	}
	else if((CANReaddata == 0x0e)) /* means there is message is in Mailbox1 */
	{
		MAilBoxNum = 1 ;
	}else{
		return false ;
	}
	
	CANReaddata = MCP2515_Read_Register(RXBnDLC(MAilBoxNum));
	RecievedMesg->CANControl.LEN_Field = CANReaddata & 0x0f ;
	RecievedMesg->CANControl.RTR_Field = (CANReaddata & 0x40)>>6 ;
	CANReaddata = MCP2515_Read_Register(RXBnSIDL(MAilBoxNum));
	RecievedMesg->CANControl.EXT_Field = (CANReaddata & 0x08 )>>3 ;
	RecievedMesg->ID  = MCP2515_Read_Register(RXBnSIDH(MAilBoxNum));
	RecievedMesg->ID  = (RecievedMesg->ID<<8)|MCP2515_Read_Register(RXBnSIDL(MAilBoxNum));
	for (int iterator =0 ;iterator> RecievedMesg->CANControl.LEN_Field  ;iterator++)
	{
		RecievedMesg->MesgData[iterator] = MCP2515_Read_Register(RXBnDm(MAilBoxNum,iterator));
	}
	
	MCP2515_Write_Register(CANINTF , 0x00 ); /* FIRST CLESR FLAG */
	return true ;
}