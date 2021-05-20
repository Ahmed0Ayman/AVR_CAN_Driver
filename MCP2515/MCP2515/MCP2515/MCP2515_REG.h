/*
 * MCP2515_REG.h
 *
 * Created: 5/20/2021 10:05:34 PM
 *  Author: Ahmed_Ayman
 */ 

#ifndef __MCP2515_REG_
#define __MCP2515_REG_

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// MCP2515 pins - PDIP/SOIC Package
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define TXCAN 1 // Transmit CAN signal (To CAN transciever)
#define RXCAN 2 // Receive CAN signal (From CAN transciever)
#define CLKOUT_SOF 3 // Clock out, can be used as clock source for MCU's / SOF signal
#define TX0RTS 4 // (NEG) Request to send input for TXB0 / digital input (with 100k pullup)
#define TX1RTS 5 // (NEG) Request to send input for TXB1 / digital input (with 100k pullup)
#define TX2RTS 6 // (NEG) Request to send input for TXB2 / digital input (with 100k pullup)
#define OSC2 7 // Oscillator output
#define OSC1 8 // Oscillator input
#define VSS 9 // Ground
#define RX1BF 10 // (NEG) RXB1 full interrupt signal / digital output
#define RX0BF 11 // (NEG) RXB0 full interrupt signal / digital output
#define INT 12 // (NEG) nterrupt pin (for MCU, reduces SPI overhead)
#define SCK 13 // SPI clock
#define SI 14 // SPI slave input
#define SO 15 // SPI slave output
#define CS 16 // (NEG) SPI chip select
#define RESET 17 // (NEG) Reset pin (should be connected via RC with tau > 128 osc. ticks)
#define VDD 18 // Power supply
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// MCP2515 pins - TSSOP Package
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define TSSOP_TXCAN 1 // Transmit CAN signal (To CAN transciever)
#define TSSOP_RXCAN 2 // Receive CAN signal (From CAN transciever)
#define TSSOP_CLKOUT_SOF 3 // Clock out, can be used as clock source for MCU's / SOF signal
#define TSSOP_TX0RTS 4 // (NEG) Request to send input for TXB0 / digital input (with 100k pullup)
#define TSSOP_TX1RTS 5 // (NEG) Request to send input for TXB1 / digital input (with 100k pullup)
#define TSSOP_TX2RTS 7 // (NEG) Request to send input for TXB2 / digital input (with 100k pullup)
#define TSSOP_OSC2 8 // Oscillator output
#define TSSOP_OSC1 9 // Oscillator input
#define TSSOP_VSS 10 // Ground
#define TSSOP_RX1BF 11 // (NEG) RXB1 full interrupt signal / digital output
#define TSSOP_RX0BF 12 // (NEG) RXB0 full interrupt signal / digital output

#define TSSOP_INT 13 // (NEG) nterrupt pin (for MCU, reduces SPI overhead)
#define TSSOP_SCK 14 // SPI clock
#define TSSOP_SI 16 // SPI slave input
#define TSSOP_SO 17 // SPI slave output
#define TSSOP_CS 18 // (NEG) SPI chip select
#define TSSOP_RESET 19 // (NEG) Reset pin (should be connected via RC with tau > 128 osc. ticks)
#define TSSOP_VDD 20 // Power supply
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// MCP2515 instructions & modes & interrupt codes & buffer indexes
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define RESET_INSTRUCTION 0xC0 // Instruction for immediate reset
#define READ_INSTRUCTION 0x03 // Read register
#define WRITE_INSTRUCTION 0x02 // Write register
#define READRX_INSTRUCTION 0x90 // 10010mn0 - m,n is address of the RX buffer
#define LOADTX_INSTRUCTION 0x40 // 01000abc - a,b,c is address of the TX buffer
#define RTS_INSTRUCTION 0x80 // 10000abc - a,b,c is address of the TX buffer
#define READSTAT_INSTRUCTION 0xA0 // Read device status instructio
#define RXSTAT_INSTRUCTION 0xB0 // Read receive buffer status instruction
#define BITMODIFY_INSTRUCTION 0x05 // For specific bit modifications
// Flags in the result of READ STATE instruction
// (Can be used as bit masks for each flag)
#define STATE_RX0_FULL (0x01 << 0) // 00000001
#define STATE_RX1_FULL (0x01 << 1) // 00000010
#define STATE_TX0_TXREQ (0x01 << 2) // 00000100
#define STATE_TX0_EMPTY (0x01 << 3) // 00001000
#define STATE_TX1_TXREQ (0x01 << 4) // 00010000
#define STATE_TX1_EMPTY (0x01 << 5) // 00100000
#define STATE_TX2_TXREQ (0x01 << 6) // 01000000
#define STATE_TX2_EMPTY (0x01 << 7) // 10000000
//RX status instruction - mask bits in result state
#define RM_POS (0x03 << 6) // Received message position
#define EXT_MSG (0x01 << 4) // Is message extended?
#define REMOTE_MSG (0x01 << 3) // Is message remote?
#define AFM (0x07 << 0) // Acceptance filter match

// Masks for informations contained in the result of RX state instruction
#define RXSTATE_MSG_POSITION 0xC0 // xx000000
#define RXSTATE_MSG_TYPE 0x18 // 000xx000
#define RXSTATE_ACCEPT_FILTER 0x07 // 00000xxx
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// MCP2515 buffers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Indexes of RX and TX buffers
#define NO_FILTERS 6
#define NO_MASKS 2
#define NO_TX_BUFFERS 3
#define NO_RX_BUFFERS 2
#define TXB0 0 // Transmit buffer 0
#define TXB1 1 // Transmit buffer 1
#define TXB2 2 // Transmit buffer 2
#define RXB0 0 // Receive buffer 0
#define RXB1 1 // Receive buffer 1
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// MCP2515 buffers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define RXF0 0 // RXB0 filter 0 (or RXB1 filter 0, when rollover is active)
#define RXF1 1 // RXB0 filter 1 (or RXB1 filter 1, when rollover is active)
#define RXF2 2 // RXB1 filter 2
#define RXF3 3 // RXB1 filter 3
#define RXF4 4 // RXB1 filter 4
#define RXF5 5 // RXB1 filter 5
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// MCP2515 registers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Transmit & receive error counters
#define TEC 0x1C // Transmit error counter
#define REC 0x1D // Receive error counter

// Bit definitions for register BFPCTRL
// (RXn buffer pin control and status)
#define BFPCTRL 0x0C
#define B1BFS 5 // RW-0, RX1BF pin state bit
#define B0BFS 4 // RW-0, RX0BF pin state bit
#define B1BFE 3 // RW-0, RX1BF pin function enable bit
#define B0BFE 2 // RW-0, RX0BF pin function enable bit
#define B1BFM 1 // RW-0, RX1BF pin operation mode bit
#define B0BFM 0 // RW-0, RX0BF pin operation mode bit
// Bit definitions for register CANCTRL
// (CAN control register)
#define CANCTRL 0x0F
#define REQOP2 7 // RW-1, Request operation mode bit 2
#define REQOP1 6 // RW-0, Request operation mode bit 1
#define REQOP0 5 // RW-0, Request operation mode bit 0
#define ABAT 4 // RW-0, Abort all pending transmissions bit
#define OSM 3 // RW-0, One shot mode
#define CLKEN 2 // RW-1, CLKOUT pin enable
#define CLKPRE1 1 // RW-1, CLKOUT pin prescaler 1
#define CLKPRE0 0 // RW-1, CLKOUT pin prescaler 0
// Bit definitions for register CANSTAT
// (CAN status register)
#define CANSTAT 0x0E
#define OPMOD2 7 // R-1, Operation mode bit 2
#define OPMOD1 6 // R-0, Operation mode bit 1
#define OPMOD0 5 // R-0, Operation mode bit 0
#define ICOD2 3 // R-0, Interrupt flag code bit 2
#define ICOD1 2 // R-0, Interrupt flag code bit 1
#define ICOD0 1 // R-0, Interrupt flag code bit 0
// Bit definitions for register CNF3
// (Configuration 3 register)
#define CNF3 0x28
#define SOF 7 // RW-0, Start of frame signal bit
#define WAKFIL 6 // RW-0, Wake-up filter bit
#define PHSEG22 2 // RW-0, PS2 bit 2
#define PHSEG21 1 // RW-0, PS2 bit 1

#define PHSEG20 0 // RW-0, PS2 bit 0
// Bit definitions for register CNF2
// (Configuration 2 register)
#define CNF2 0x29
#define BTLMODE 7 // RW-0, PS bit time length bit
#define SAM 6 // RW-0, Sample point configuration bit
#define PHSEG12 5 // RW-0, PS1 length bit 2
#define PHSEG11 4 // RW-0, PS1 length bit 1
#define PHSEG10 3 // RW-0, PS1 length bit 0
#define PRSEG2 2 // RW-0, Propagation segment length bit 2
#define PRSEG1 1 // RW-0, Propagation segment length bit 1
#define PRSEG0 0 // RW-0, Propagation segment length bit 0
// Bit definitions for register CNF1
// (Configuration 1 register)
#define CNF1 0x2A
#define SJW1 7 // RW-0, Synchronization jump width length bit 1
#define SJW0 6 // RW-0, Synchronization jump width length bit 0
#define BRP5 5 // RW-0, Baud rate prescaler bit 5
#define BRP4 4 // RW-0, Baud rate prescaler bit 4
#define BRP3 3 // RW-0, Baud rate prescaler bit 3
#define BRP2 2 // RW-0, Baud rate prescaler bit 2
#define BRP1 1 // RW-0, Baud rate prescaler bit 1
#define BRP0 0 // RW-0, Baud rate prescaler bit 0
// Bit definitions for register CANINTE
// (Interrupt enable register)
#define CANINTE 0x2B
#define MERRE 7 // RW-0, Message error interrupt enable bit
#define WAKIE 6 // RW-0, Wakeup interrupt enable bit
#define ERRIE 5 // RW-0, Error interrupt enable bit
#define TX2IE 4 // RW-0, Transmit buffer 2 empty interrupt enable bit
#define TX1IE 3 // RW-0, Transmit buffer 1 empty interrupt enable bit
#define TX0IE 2 // RW-0, Transmit buffer 0 empty interrupt enable bit
#define RX1IE 1 // RW-0, Receive buffer 1 full interrupt enable bit
#define RX0IE 0 // RW-0, Receive buffer 0 full interrupt enable bit
// Bit definitions for register CANINTF

// (Interrupt flag register)
#define CANINTF 0x2C
#define MERRF 7 // RW-0, Message error interrupt flag bit
#define WAKIF 6 // RW-0, Wakeup interrupt flag bit
#define ERRIF 5 // RW-0, Error interrupt flag bit
#define TX2IF 4 // RW-0, Transmit buffer 2 empty interrupt flag bit
#define TX1IF 3 // RW-0, Transmit buffer 1 empty interrupt flag bit
#define TX0IF 2 // RW-0, Transmit buffer 0 empty interrupt flag bit
#define RX1IF 1 // RW-0, Receive buffer 1 full interrupt flag bit
#define RX0IF 0 // RW-0, Receive buffer 0 full interrupt flag bit
// Bit definitions for register EFLG
// (Error flag register)
#define EFLG 0x2D
#define RX1OVR 7 // RW-0, Receive buffer 1 overflow flag bit
#define RX0OVR 6 // RW-0, Receive buffer 0 overflow flag bit
#define TXBO 5 // R-0, Bus-off error flag bit
#define TXEP 4 // R-0, Transmit error - passive flag bit
#define RXEP 3 // R-0, Receive error - passive flag bit
#define TXWAR 2 // R-0, Transmit error warning flag bit
#define RXWAR 1 // R-0, Receive error warning flag bit
#define EWARN 0 // R-0, Error warning flag bit
// Bit definitions for registers TXBnCTRL
// (Transmit buffer n control register)
#define TXBnCTRL(n) 0x30+(n*0x10)
#define TXB0CTRL TXBnCTRL(0)
#define TXB1CTRL TXBnCTRL(1)
#define TXB2CTRL TXBnCTRL(2)
#define ABTF 6 // R-0, Message aborted flag bit
#define MLOA 5 // R-0, Message lost arbitration bit
#define TXERR 4 // R-0, Transmit error detected bit
#define TXREQ 3 // RW-0, Message transmit request bit
#define TXP1 1 // RW-0, Transmit buffer priority bit 1
#define TXP0 0 // RW-0, Transmit buffer priority bit 0
// Bit definitions for registers TXBnDLC
// (Transmit buffer data length control)
#define TXBnDLC(n) 0x35+(n*0x10)

#define TXB0DLC TXBnDLC(0)
#define TXB1DLC TXBnDLC(1)
#define TXB2DLC TXBnDLC(2)
#define RTR 6 // RW-x, Remote transfer request
#define DLC3 3 // RW-x, Data length code bit 3
#define DLC2 2 // RW-x, Data length code bit 2
#define DLC1 1 // RW-x, Data length code bit 1
#define DLC0 0 // RW-x, Data length code bit 0
// Bit definitions for register TXBnSIDH
// (Transmit buffer n - standard identifier high)
#define TXBnSIDH(n) 0x31+(n*0x10)
#define TXB0SIDH TXBnSIDH(0)
#define TXB1SIDH TXBnSIDH(1)
#define TXB2SIDH TXBnSIDH(2)
#define SID10 7 // RW-x, Standard identifier, bit 10
#define SID9 6 // RW-x, Standard identifier, bit 9
#define SID8 5 // RW-x, Standard identifier, bit 8
#define SID7 4 // RW-x, Standard identifier, bit 7
#define SID6 3 // RW-x, Standard identifier, bit 6
#define SID5 2 // RW-x, Standard identifier, bit 5
#define SID4 1 // RW-x, Standard identifier, bit 4
#define SID3 0 // RW-x, Standard identifier, bit 3
// Bit definitions for register TXBnSIDL
// (Transmit buffer n - standard identifier low)
#define TXBnSIDL(n) 0x32+(n*0x10)
#define TXB0SIDL TXBnSIDL(0)
#define TXB1SIDL TXBnSIDL(1)
#define TXB2SIDL TXBnSIDL(2)
#define SID2 7 // RW-x, Standard identifier, bit 2
#define SID1 6 // RW-x, Standard identifier, bit 1
#define SID0 5 // RW-x, Standard identifier, bit 0
#define EXIDE 3 // RW-x, Extended identifier enable bit
#define EID17 1 // RW-x, Extended identifier, bit 17
#define EID16 0 // RW-x, Extended identifier, bit 16
// Bit definitions for register TXBnEID8
// (Transmit buffer n - extended identifier high)

#define TXBnEID8(n) 0x33+(n*0x10)
#define TXB0EID8 TXBnEID8(0)
#define TXB1EID8 TXBnEID8(1)
#define TXB2EID8 TXBnEID8(2)
#define EID15 7 // RW-x, Extended identifier, bit 15
#define EID14 6 // RW-x, Extended identifier, bit 14
#define EID13 5 // RW-x, Extended identifier, bit 13
#define EID12 4 // RW-x, Extended identifier, bit 12
#define EID11 3 // RW-x, Extended identifier, bit 11
#define EID10 2 // RW-x, Extended identifier, bit 10
#define EID9 1 // RW-x, Extended identifier, bit 9
#define EID8 0 // RW-x, Extended identifier, bit 8
// Bit definitions for register TXBnEID0
// (Transmit buffer n - extended identifier high)
#define TXBnEID0(n) 0x34+(n*0x10)
#define TXB0EID0 TXBnEID0(0)
#define TXB1EID0 TXBnEID0(1)
#define TXB2EID0 TXBnEID0(2)
#define EID7 7 // RW-x, Extended identifier, bit 7
#define EID6 6 // RW-x, Extended identifier, bit 6
#define EID5 5 // RW-x, Extended identifier, bit 5
#define EID4 4 // RW-x, Extended identifier, bit 4
#define EID3 3 // RW-x, Extended identifier, bit 3
#define EID2 2 // RW-x, Extended identifier, bit 2
#define EID1 1 // RW-x, Extended identifier, bit 1
#define EID0 0 // RW-x, Extended identifier, bit 0
// Bit definitions for registers TXBnDm
// (Transmit buffer N data byte M)
#define TXBnDm(n,m) 0x36+(n*0x10)+m
#define TXBnDm7 7 // RW-x, Transmit buffer N, data byte M, bit 7
#define TXBnDm6 6 // RW-x, Transmit buffer N, data byte M, bit 6
#define TXBnDm5 5 // RW-x, Transmit buffer N, data byte M, bit 5
#define TXBnDm4 4 // RW-x, Transmit buffer N, data byte M, bit 4
#define TXBnDm3 3 // RW-x, Transmit buffer N, data byte M, bit 3
#define TXBnDm2 2 // RW-x, Transmit buffer N, data byte M, bit 2
#define TXBnDm1 1 // RW-x, Transmit buffer N, data byte M, bit 1
#define TXBnDm0 0 // RW-x, Transmit buffer N, data byte M, bit 0

// Bit definitions for register TXRTSCTRL
// (TXn buffer pin control and status)
#define TXRTSCTRL 0x0D
#define B2RTS 5 // R, TX2RTS pin state bit
#define B1RTS 4 // R, TX1RTS pin state bit
#define B0RTS 3 // R, TX0RTS pin function enable bit
#define B2RTSM 2 // RW-0, TX2RTS pin mode bit
#define B1RTSM 1 // RW-0, TX1RTS pin mode bit
#define B0RTSM 0 // RW-0, TX0RTS pin mode bit
// Bit definitions for registers RXBnCTRL
// (Receive buffer n control register)
#define RXBnCTRL(n) 0x60+(n*0x10)
#define RXB0CTRL RXBnCTRL(0)
#define RXB1CTRL RXBnCTRL(1)
#define RXM1 6 // RW-0, Receive buffer operating mode bit 1
#define RXM0 5 // RW-0, Receive buffer operating mode bit 0
#define RXRTR 3 // R-0, Receive remote transfer request bit
#define BUKT 2 // RW-0, Rollover enable bit (used only by RXB0CTRL)
#define FILHIT2 2 // R-0, Filter hit bit 2 (used only by RXB1CTRL)
#define FILHIT1 1 // R-0, Filter hit bit 1 (used only by RXB1CTRL)
#define FILHIT0 0 // R-0, Filter hit bit 0
// Bit definitions for registers RXBnSIDH
// (Receive buffer n standard identifier high)
#define RXBnSIDH(n) 0x61+(n*0x10)
#define RXB0SIDH RXBnSIDH(0)
#define RXB1SIDH RXBnSIDH(1)
#define SID10 7 // RW-x, Standard identifier, bit 10
#define SID9 6 // RW-x, Standard identifier, bit 9
#define SID8 5 // RW-x, Standard identifier, bit 8
#define SID7 4 // RW-x, Standard identifier, bit 7
#define SID6 3 // RW-x, Standard identifier, bit 6
#define SID5 2 // RW-x, Standard identifier, bit 5
#define SID4 1 // RW-x, Standard identifier, bit 4
#define SID3 0 // RW-x, Standard identifier, bit 3
// Bit definitions for register RXBnSIDL

// (Receive buffer n - standard identifier low)
#define RXBnSIDL(n) 0x62+(n*0x10)
#define RXB0SIDL RXBnSIDL(0)
#define RXB1SIDL RXBnSIDL(1)
#define SID2 7 // RW-x, Standard identifier, bit 2
#define SID1 6 // RW-x, Standard identifier, bit 1
#define SID0 5 // RW-x, Standard identifier, bit 0
#define SRR 4 // RW-x, Standard frame remote transmit request bit, bit 1
#define IDE 3 // RW-x, Extended identifier flag bit, bit 0
#define EID17 1 // RW-x, Extended identifier, bit 17
#define EID16 0 // RW-x, Extended identifier, bit 16
// Bit definitions for register RXBnEID8
// (Receive buffer n - extended identifier high)
#define RXBnEID8(n) 0x63+(n*0x10)
#define RXB0EID8 RXBnEID8(0)
#define RXB1EID8 RXBnEID8(1)
#define EID15 7 // RW-x, Extended identifier, bit 15
#define EID14 6 // RW-x, Extended identifier, bit 14
#define EID13 5 // RW-x, Extended identifier, bit 13
#define EID12 4 // RW-x, Extended identifier, bit 12
#define EID11 3 // RW-x, Extended identifier, bit 11
#define EID10 2 // RW-x, Extended identifier, bit 10
#define EID9 1 // RW-x, Extended identifier, bit 9
#define EID8 0 // RW-x, Extended identifier, bit 8
// Bit definitions for register RXBnEID0
// (Receive buffer n - extended identifier high)
#define RXBnEID0(n) 0x64+(n*0x10)
#define RXB0EID0 RXBnEID0(0)
#define RXB1EID0 RXBnEID0(1)
#define EID7 7 // RW-x, Extended identifier, bit 7
#define EID6 6 // RW-x, Extended identifier, bit 6
#define EID5 5 // RW-x, Extended identifier, bit 5
#define EID4 4 // RW-x, Extended identifier, bit 4
#define EID3 3 // RW-x, Extended identifier, bit 3
#define EID2 2 // RW-x, Extended identifier, bit 2
#define EID1 1 // RW-x, Extended identifier, bit 1

#define EID0 0 // RW-x, Extended identifier, bit 0
// Bit definitions for registers RXBnDLC
// (Receive buffer data length control)
#define RXBnDLC(n) 0x65+(n*0x10)
#define RXB0DLC RXBnDLC(0)
#define RXB1DLC RXBnDLC(1)
#define RTR 6 // RW-x, Remote transfer request
#define DLC3 3 // RW-x, Data length code bit 3
#define DLC2 2 // RW-x, Data length code bit 2
#define DLC1 1 // RW-x, Data length code bit 1
#define DLC0 0 // RW-x, Data length code bit 0
// Bit definitions for registers RXBnDm
// (Receive buffer N data byte M)
#define RXBnDm(n,m) 0x66 + (n*0x10) + m
#define RXBnDm7 7 // RW-x, Receive buffer N, data byte M, bit 7
#define RXBnDm6 6 // RW-x, Receive buffer N, data byte M, bit 6
#define RXBnDm5 5 // RW-x, Receive buffer N, data byte M, bit 5
#define RXBnDm4 4 // RW-x, Receive buffer N, data byte M, bit 4
#define RXBnDm3 3 // RW-x, Receive buffer N, data byte M, bit 3
#define RXBnDm2 2 // RW-x, Receive buffer N, data byte M, bit 2
#define RXBnDm1 1 // RW-x, Receive buffer N, data byte M, bit 1
#define RXBnDm0 0 // RW-x, Receive buffer N, data byte M, bit 0
// Bit definitions for registers RXFnSIDH
// (Filter n standard identifier high)
#define RXFnSIDH(n) 0+(n*4)+((n>2)?4:0)
#define RXF0SIDH RXFnSIDH(0)
#define RXF1SIDH RXFnSIDH(1)
#define RXF2SIDH RXFnSIDH(2)
#define RXF3SIDH RXFnSIDH(3)
#define RXF4SIDH RXFnSIDH(4)
#define RXF5SIDH RXFnSIDH(5)
// Bits are same as in TXBnSIDH
// Bit definitions for register RXFnSIDL
// (Filter n - standard identifier low)
#define RXFnSIDL(n) 1+(n*4)+((n>2)?4:0)

#define RXF0SIDL RXFnSIDL(0)
#define RXF1SIDL RXFnSIDL(1)
#define RXF2SIDL RXFnSIDL(2)
#define RXF3SIDL RXFnSIDL(3)
#define RXF4SIDL RXFnSIDL(4)
#define RXF5SIDL RXFnSIDL(5)
// Bits are same as in TXBnSIDL
// Bit definitions for register RXFnEID8
// (Filter n - extended identifier high)
#define RXFnEID8(n) 2+(n*4)+((n>2)?4:0)
#define RXF0EID8 RXFnEID8(0)
#define RXF1EID8 RXFnEID8(1)
#define RXF2EID8 RXFnEID8(2)
#define RXF3EID8 RXFnEID8(3)
#define RXF4EID8 RXFnEID8(4)
#define RXF5EID8 RXFnEID8(5)
// Bits EID15-EID8 are same as in TXBnEID8
// Bit definitions for register RXFnEID0
// (Filter buffer n - extended identifier low)
#define RXFnEID0(n) 3+(n*4)+((n>2)?4:0)
#define RXF0EID0 RXFnEID0(0)
#define RXF1EID0 RXFnEID0(1)
#define RXF2EID0 RXFnEID0(2)
#define RXF3EID0 RXFnEID0(3)
#define RXF4EID0 RXFnEID0(4)
#define RXF5EID0 RXFnEID0(5)
// Bits EID7-EID0 are same as in TXBnEID0
// Bit definitions for registers RXMnSIDH
// (Mask n standard identifier high)
#define RXMnSIDH(n) 0x20+(n*4)
#define RXM0SIDH RXMnSIDH(0)
#define RXM1SIDH RXMnSIDH(1)
// Bits are same as in TXBnSIDH
// Bit definitions for register RXMnSIDL
// (Mask n - standard identifier low)

#define RXMnSIDL(n) 0x21+(n*4)
#define RXM0SIDL RXMnSIDL(0)
#define RXM1SIDL RXMnSIDL(1)
// Bits are same as in TXBnSIDL
// Bit definitions for register RXMnEID8
// (Filter n - extended identifier high)
#define RXMnEID8(n) 0x22+(n*4)
#define RXM0EID8 RXMnEID8(0)
#define RXM1EID8 RXMnEID8(1)
// Bits EID15-EID8 are same as in TXBnEID8
// Bit definitions for register RXMnEID0
// (Filter buffer n - extended identifier high)
#define RXMnEID0(n) 0x23+(n*4)
#define RXM0EID0 RXMnEID0(0)
#define RXM1EID0 RXMnEID0(1)
// Bits EID7-EID0 are same as in TXBnEID0
/** List of registers which are accessible from BIT MODIFY instruction. You can use following code
* to declare array with all registers which are supported by "Bit modify" instruction:
* \code
* unsigned char test[] = {BIT_MODIFY_SUPPORTED_REGISTERS};
* \endcode
*/
#define BIT_MODIFY_SUPPORTED_REGISTERS BFPCTRL,TXRTSCTRL,CANCTRL,CNF3,CNF2,CNF1,CANINTE,CANINTF,EFLG,TXB0CTRL,TXB1CTRL,TXB2CTRL,RXB0CTRL,RXB1CTRL














#endif /* __MCP2515_REG_ */