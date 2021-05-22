
/*
 * HAL_SPI.h
 *
 * Created: 4/19/2021 1:38:23 AM
 *  Author: Ahmed_Ayman
 */ 

#ifndef __HAL_SPI__
#define __HAL_SPI__
#include <stdbool.h>
#include "HAL_GPIO.h"
#include <string.h>
#include <avr/interrupt.h>
#include "HAL_EXIT.h"

typedef struct 
{
uint8_t SPI_SPCR;
uint8_t SPI_SPSR;
uint8_t SPI_SPDR;	
}SPITypedef_t;

typedef struct 
{
	uint8_t Mode ;			 /* must be one of SPI_MODE_ */
	uint8_t CLKPolarity ;	 /* must be one of SPI_CLKPolarity_ */
	uint8_t CLKPhase ;      /* must be one of SPI_CLK_ */
	uint8_t CLKPrescaler ;  /* must be one of SPI_CLKPrescaler_ */
	uint8_t FirstBit;      /* must be one of SPI_FirstBit_ */
	uint8_t INI_EN ;      /* must be one of SPI_INT_MODE_ */
}SPI_InitTypedef_t;    /* typedef struct used to define a struct hold all spi configurations */


typedef struct 
{
SPI_InitTypedef_t SPI_init ;    /* struct contain the SPI configuration */
uint8_t * TxBuffer ;        /* pointer to Tx buffer */
uint8_t * RxBuffer ;        /* pointer to Rx buffer */
uint16_t TxBufferSize ;    /* tx buffer size */
uint16_t RxBufferSize;     /* rx buffer size */

}SPI_Handler_t;

typedef enum  
{
	SPI_BUSY =0,
	SPI_READY ,
	
}SPI_STATUS;


//SPCR REGISTER BITS
#define SPI_SPCR_SPR0                 0X01U    // prescaler bit 0
#define SPI_SPCR_SPR1                 0X02U    // prescaler bit 1
#define SPI_SPCR_CPHA                 0X04U    // clock phase select
#define SPI_SPCR_CPOL                 0X08U    // clock polarity select
#define SPI_SPCR_MSTR                 0X10U    // master slave mode select 
#define SPI_SPCR_DORD                 0X20U    // LSB first
#define SPI_SPCR_SPE                  0X40U    // SPI Enable
#define SPI_SPCR_SPIE                 0X80U    // SPI interrupt enable

// SPSR REGISTER BITS
#define SPI_SPSR_SPR2                 0X01U    // precsaler bit 3
#define SPI_SPSR_WCOL                 0X40U    // collision flag 
#define SPI_SPSR_SPIF                 0X80U    // SPI interrupt flag

// SPI GPIO PINS 
#define SPI_PIN_MOSI                  GPIO_PIN_5     
#define SPI_PIN_MISO                  GPIO_PIN_6
#define SPI_PIN_SCK                   GPIO_PIN_7
#define SPI_PIN_SS                    GPIO_PIN_4

#define SPI_BASE                      0x2DU     // base address of  SPI peripheral 
#define SPI_PREPH         ((SPITypedef_t volatile *)SPI_BASE)      
 
 
// @select_SPI_OPERATION_MODE
#define SPI_MODE_SLAVE                0X00U    
#define SPI_MODE_MASTER               0X10U

// @select_SPI_POLARITY
#define SPI_CLKPolarity_IDLE_HIGH     0X08U
#define SPI_CLKPolarity_IDLE_LOW      0X00U

// @select_SPI_MSB
#define SPI_CLK_SAMPLE_FIRST_EDGE     0X00U
#define SPI_CLK_SAMPLE_LAST_EDGE      0X40U

//@select_SPI_CLK_PRESCALER
#define SPI_CLKPrescaler_2            0X14U
#define SPI_CLKPrescaler_4            0X10U
#define SPI_CLKPrescaler_8            0X15U
#define SPI_CLKPrescaler_16           0X01U
#define SPI_CLKPrescaler_32           0X16U
#define SPI_CLKPrescaler_64           0X12U
#define SPI_CLKPrescaler_128          0X03U

// @select_SPI_LSB 
#define SPI_FirstBit_LSB              0X20U
#define SPI_FirstBit_MSB              0X00U

// @SPI_ENABLE
#define SPI_INT_MODE_ENABLE           0X80U
#define SPI_INT_MODE_DISABLE          0X00U  




/*
 * brief : initialization for SPI 
 * param Handler pointer to struct hold all configuration parameter 
 */ 
 void HAL_SPI_Init(SPI_Handler_t * Handler);

/* brief transmit data  
 * param Handler control pointer to struct hold all configuration parameter 
 * param pTxData pointer to transmit buffer 
 * param size size of transmitted buffer 
 */
 void  HAL_SPI_Transmit(SPI_Handler_t * Handler,uint8_t * pTxData,uint16_t size );

/* brief transmit data  
 * param Handler pointer to control struct hold all configuration parameter 
 * param pRxData pointer to receive buffer 
 * param size size of transmitted buffer 
 */  
 void  HAL_SPI_Recieve(SPI_Handler_t * Handler,uint8_t * pRxData,uint16_t size );


/* brief transmit and receive data  
 * param Handler pointer to control struct hold all configuration parameter 
 * param pTxData pointer to transmit buffer
 * param pRxData pointer to receive buffer 
 * param size size of transmitted buffer 
 */ 
 void  HAL_SPI_TransmitRecive(SPI_Handler_t * Handler,uint8_t * pTxData,uint8_t * pRxData,uint16_t size );
 
 /* 
  * brief   : this function used to handle the operation in interrupt mode 
  * param.  : Handler : Handler of SPI peripheral 
  * return  : void 
 */
 void SPI_Handler_Process(SPI_Handler_t * Handler);

/*
 * brief  : this function used to transmit data using non block mode  
 * param. :Handler --> this handler of spi peripheral 
 * param. :pTxData --> pointer to the Tx buffer 
 * param. :size    --> the required number of bytes to transmit 
 */
 void HAL_SPI_Transmit_IT(SPI_Handler_t * Handler,uint8_t * pTxData,uint16_t size );
  
 /* 
 * brief : this function used to  receive data using non block mode  
 * param. : Handler --> this handler of spi peripheral 
 * param. : pRxData --> pointer to the Rx buffer 
 * param. : size    --> the required number of bytes to Receive 
 */
 void HAL_SPI_Receive_IT(SPI_Handler_t * Handler,uint8_t * pRxData,uint16_t size );
 
 
/*
 * brief  :this function used to transmit and receive data using non block mode  
 * param. :Handler --> this handler of SPI peripheral 
 * param. :pTxData --> pointer to the Tx buffer 
 * param. :pRxData --> pointer to the rx buffer
 * param. :size    --> the required number of bytes to received and transmit 
 */
  void HAL_TransmitRecive_IT(SPI_Handler_t * Handler,uint8_t * pTxData,uint8_t * pRxData,uint16_t size );




#endif