
/*
 * HAL_SPI.c
 *
 * Created: 4/19/2021 1:38:09 AM
 *  Author: Ahmed_Ayman
 */ 


#include "HAL_SPI.h"

 SPI_Handler_t  SPI_Handler ;    
 
static SPI_STATUS SPI_State  ;  /* static variable used by the driver to indicate the status of the SPI driver */



/*
 * brief  : this function used to initialize the SPI peripheral 
 * param. : handler this var hold all initialization required by the application   
 * return :void 
*/
 void HAL_SPI_Init(SPI_Handler_t * Handler)
{
	GPIO_InitTypeDef SPI_GpioPin;  // used by  this function to initialize the gpio peripheral to work as spi 
	/* ONLY ONE REGISTER CONTROL SPI OPREATION AND ONE STRUCT HOLD ALL CONFIG.*/
	if((Handler->SPI_init.CLKPrescaler) & 0x80)    /* set the selected prescaler so first check if it is required to set the SPI2X bit  */
	{
	 SPI_PREPH->SPI_SPCR |=((Handler->SPI_init.CLKPrescaler)&0x3u);
	 SPI_PREPH->SPI_SPSR |= SPI_SPSR_SPR2;
	}else{
	 SPI_PREPH->SPI_SPCR |=((Handler->SPI_init.CLKPrescaler)&0x3u);		
	}
	if(Handler->SPI_init.Mode & SPI_SPCR_MSTR)  /* master mode GPIO configuration */ 
	{
		SPI_GpioPin.mode = GPIO_MODE_OUTPUT ;
		SPI_GpioPin.pinS  = SPI_PIN_MOSI | SPI_PIN_SS | SPI_PIN_SCK;
		HAL_GPIO_INIT_PIN(GPIOB,&SPI_GpioPin);

		SPI_GpioPin.mode = GPIO_MODE_INPUT ;
		SPI_GpioPin.pinS  = SPI_PIN_MISO ;
		HAL_GPIO_INIT_PIN(GPIOB,&SPI_GpioPin);		
		
		
	}else{           /* slave mode GPIO configuration */
		SPI_GpioPin.mode = GPIO_MODE_INPUT ;
		SPI_GpioPin.pinS  = SPI_PIN_SCK | SPI_PIN_MOSI | SPI_PIN_SS;
		HAL_GPIO_INIT_PIN(GPIOB,&SPI_GpioPin);

		SPI_GpioPin.mode = GPIO_MODE_OUTPUT ;
		SPI_GpioPin.pinS  = SPI_PIN_MISO ;
		HAL_GPIO_INIT_PIN(GPIOB,&SPI_GpioPin);
	}
	/* set the select attribute of the SPI peripheral */
	 SPI_PREPH->SPI_SPCR  = Handler->SPI_init.CLKPhase | Handler->SPI_init.CLKPolarity |Handler->SPI_init.FirstBit |Handler->SPI_init.INI_EN |Handler->SPI_init.Mode ;
	 SPI_PREPH->SPI_SPCR |= SPI_SPCR_SPE ; 	
	if(Handler->SPI_init.INI_EN == SPI_INT_MODE_ENABLE)   /* if SPI interrupt enable then enable the global interrupt */
		sei();
			
			
	
}/* END_FUN HAL_SPI_Init()*/




/*
 * brief  : this function used to transmit data using block mode  
 * param. :Handler : this handler of SPI peripheral 
 * param. :pTxData : pointer to the tx buffer  
 * param. :size the required number of bytes to transmit 
*/
 void HAL_SPI_Transmit(SPI_Handler_t * Handler,uint8_t * pTxData,uint16_t size )
{

    /* set the SPI Handler data trans and buffer size */
	Handler->RxBuffer = NULL ;
	Handler->RxBufferSize = 0;

	Handler->TxBuffer = pTxData  ;
	Handler->TxBufferSize = size;
	HAL_GPIO_WRITEPIN(GPIOB,SPI_PIN_SS,GPIO_PIN_RESET);
	while(Handler->TxBufferSize-- > 0)   /* block mode so this function will block till the size of buffer is equal to zero */
	{
		SPI_PREPH->SPI_SPDR = *(Handler->TxBuffer);
		while(!(SPI_PREPH->SPI_SPSR & SPI_SPSR_SPIF)); /* wait till the SPI send byte and set SPIIF bit */
		++(Handler->TxBuffer);
	}
	HAL_GPIO_WRITEPIN(GPIOB,SPI_PIN_SS,GPIO_PIN_SET);
	
	
}/* END_FUN HAL_SPI_Transmit()*/




/* 
 * brief  : this function used to receive data using block mode  
 * param. :Handler --> this handler of SPI peripheral 
 * param. :pRxData --> pointer to the rx buffer  
 * param. :size    -->the required number of bytes to received 
*/
 void HAL_SPI_Recieve(SPI_Handler_t * Handler,uint8_t * pRxData,uint16_t size )
{
	Handler->RxBuffer = pRxData ;
	Handler->TxBuffer = NULL  ;
	Handler->RxBufferSize = size ;
	Handler->TxBufferSize = 0;

	HAL_GPIO_WRITEPIN(GPIOB,SPI_PIN_SS,GPIO_PIN_RESET);
	while(Handler->RxBufferSize >0)  /* block until end */
	{ 
		 *(Handler->TxBuffer) = SPI_PREPH->SPI_SPDR ;
		while(!(SPI_PREPH->SPI_SPSR & SPI_SPSR_SPIF));  /* wait till the spi send byte and set SPIIF bit */
		++(Handler->RxBuffer);
		--(Handler->RxBufferSize);
	}	
	HAL_GPIO_WRITEPIN(GPIOB,SPI_PIN_SS,GPIO_PIN_SET);	
}/* END_FUN HAL_SPI_Recieve()*/




/*
 * brief  : this function used to transmit and receive data using block mode  
 * param. : Handler --> this handler of SPI peripheral 
 * param. : pTxData --> pointer to the Tx buffer 
 * param. : pRxData --> pointer to the rx buffer
 * param. : size : the required number of bytes to received and transmit 
*/
 void HAL_SPI_TransmitRecive(SPI_Handler_t * Handler,uint8_t * pTxData,uint8_t * pRxData,uint16_t size )
{
	Handler->RxBuffer = pRxData ;
	Handler->TxBuffer = pTxData  ;
	Handler->RxBufferSize = size ;
	Handler->TxBufferSize = size;

	HAL_GPIO_WRITEPIN(GPIOB,SPI_PIN_SS,GPIO_PIN_RESET);

	while(Handler->RxBufferSize-- > 0)  /* block till end operation */
	{

		SPI_PREPH->SPI_SPDR = *(Handler->TxBuffer);
		while(!(SPI_PREPH->SPI_SPSR & SPI_SPSR_SPIF));  /* wait till the SPI send byte and set SPIIF bit */
		*(Handler->RxBuffer) = SPI_PREPH->SPI_SPDR ;
		++(Handler->RxBuffer);
		++(Handler->TxBuffer);
		
	}	
	HAL_GPIO_WRITEPIN(GPIOB,SPI_PIN_SS,GPIO_PIN_SET);
	
}/* END_FUN HAL_TransmitRecive()*/




/*
 * brief  : this function used to transmit data using non block mode  
 * param. :Handler --> this handler of spi peripheral 
 * param. :pTxData --> pointer to the Tx buffer 
 * param. :size    --> the required number of bytes to transmit 
 */
 void HAL_SPI_Transmit_IT(SPI_Handler_t * Handler,uint8_t * pTxData,uint16_t size )
 {
	 	if(SPI_State == SPI_READY)
	 	{
	 	Handler->RxBuffer = NULL ;
	 	Handler->TxBuffer = pTxData+1 ;
	 	Handler->RxBufferSize = 0;
	 	Handler->TxBufferSize = size;
        SPI_PREPH->SPI_SPDR = *(Handler->TxBuffer-1);
		SPI_State = SPI_BUSY;       /* set SPI as busy state to wait till the operation of non block mode is end end set as ready */
		}

 }/* END_FUN HAL_SPI_Transmit_IT()*/
 
 
 
 
 
 /* 
 * brief : this function used to  receive data using non block mode  
 * param. : Handler --> this handler of spi peripheral 
 * param. : pRxData --> pointer to the Rx buffer 
 * param. : size    --> the required number of bytes to Receive 
 */
 void HAL_SPI_Receive_IT(SPI_Handler_t * Handler,uint8_t * pRxData,uint16_t size )
  {
	  if(SPI_State == SPI_READY)
	  {
		  Handler->RxBuffer =  pRxData ;
		  Handler->TxBuffer =  pRxData;
		  Handler->RxBufferSize = size;
		  Handler->TxBufferSize = size;
		  SPI_PREPH->SPI_SPDR = *(Handler->TxBuffer-1);
		  SPI_State = SPI_BUSY;       /* set SPI as busy state to wait till the operation of non block mode is end end set as ready */
	  }

  }/* END_FUN HAL_SPI_Receive_IT()*/
 
 
 
 
/*
 * brief  :this function used to transmit and receive data using non block mode  
 * param. :Handler --> this handler of SPI peripheral 
 * param. :pTxData --> pointer to the Tx buffer 
 * param. :pRxData --> pointer to the rx buffer
 * param. :size    --> the required number of bytes to received and transmit 
 */
  void HAL_TransmitRecive_IT(SPI_Handler_t * Handler,uint8_t * pTxData,uint8_t * pRxData,uint16_t size )
  {
	  if(SPI_State == SPI_READY)
	  {
	  Handler->TxBuffer = pTxData  ;
	  Handler->RxBufferSize = size ;
	  Handler->RxBuffer = pRxData+1 ;
	  Handler->TxBufferSize = size-1;
	  SPI_PREPH->SPI_SPDR = *(Handler->TxBuffer-1);  // set the first byte to switch to interrupt function 
	  SPI_State = SPI_BUSY;       // set spi as busy state to wait till the operation of non block mode is end end set as ready
	  }
	  
  }/* END_FUN HAL_TransmitRecive_IT()*/
 
 
 
 
 
 /* 
  * brief   : this function used to handle the operation in interrupt mode 
  * param.  : Handler : Handler of SPI peripheral 
  * return  : void 
 */
 void SPI_Handler_Process(SPI_Handler_t * Handler)
 {
	 
		if(Handler->RxBuffer != NULL)  // check if receive enable 
		{
			*(Handler->RxBuffer) = SPI_PREPH->SPI_SPDR ;   // read received byte 
	 		--(Handler->RxBufferSize);
	 		++(Handler->RxBuffer ) ;
		}
		
		
		if((Handler->TxBufferSize != 0))  // check if buffer size reach to zero
		{
			 SPI_State = SPI_BUSY;
		 
			if(Handler->TxBuffer != NULL)
			{
				--(Handler->TxBufferSize);
				++(Handler->TxBuffer ) ;
				SPI_PREPH->SPI_SPDR = *(Handler->TxBuffer);
			}
		}
		else
		SPI_State = SPI_READY; //  set as ready to enable a new operation on SPI Peripheral
		 

 }/* END_FUN SPI_Handler_Process()*/
 
