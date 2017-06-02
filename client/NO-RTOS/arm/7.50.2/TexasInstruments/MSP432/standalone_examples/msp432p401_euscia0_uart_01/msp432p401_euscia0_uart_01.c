/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP432 CODE EXAMPLE DISCLAIMER
 *
 * MSP432 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//   MSP432P401 Demo - eUSCI_A0 UART echo at 9600 baud using BRCLK = 12MHz
//
//  Description: This demo echoes back characters received via a PC serial port.
//  SMCLK/ DCO is used as a clock source and the device is put in LPM3
//  The auto-clock enable feature is used by the eUSCI and SMCLK is turned off
//  when the UART is idle and turned on when a receive edge is detected.
//  Note that level shifter hardware is needed to shift between RS232 and MSP
//  voltage levels.
//
//  The example code shows proper initialization of registers
//  and interrupts to receive and transmit data.
//  To test code in LPM3, disconnect the debugger.
//
//  
//
//                MSP432P401
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//            |     P1.3/UCA0TXD|----> PC (echo)
//            |     P1.2/UCA0RXD|<---- PC
//            |                 |
//
//   Wei Zhao
//   Texas Instruments Inc.
//   June 2014
//******************************************************************************
#include "msp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Straight from UEBA/Base.h
#ifndef byte
#define byte unsigned char
#endif

#ifndef null
#define null NULL
#endif

#define IO_LedBlue BIT2
#define IO_LedGreen BIT1
#define IO_LedRed BIT0

void UART_WriteByte(byte Data){
	while(!(UCA0IFG & UCTXIFG));
	UCA0TXBUF = Data;
}

void UART_WriteString(byte * String){
	while (*String)
		UART_WriteByte(*String++);
}

byte UART_ReadByte(){
	while(!(UCA0IFG & UCRXIFG));
		return UCA0RXBUF;
}

void itoa(long unsigned int value, char* result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36)
		*result = '\0';

	char *ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}

}

//Dirrectly from UEBA/IO.h
void UART_ReadString(byte * String,byte Count){
	byte Data;
	while(Count){
		Data = UART_ReadByte();
		*String++=Data;
		if((Data=='\0')||(Data=='\r')||(Data=='\n'))
			return;    
	}
	String--;
	*String = 0;
}

void SIM900_WriteCommand(char * Src) {
	UART_WriteString(Src);
	UART_WriteString("\r\n");
}

//(Any) respond of SIM900 module consists of "\r\n<TEXT>\r\n"
void SIM900_ReadRespond(char * Dst) {
	char Dat;
	int i = 0;

	UART_ReadByte(); //r
	UART_ReadByte(); //n
	while (1) {
		Dat = UART_ReadByte();
		if(Dat != '\r') {
			*(Dst + i) = Dat;
		} else {
		  	*(Dst + i) = 0;
			break;
		}
		i++;
	}
	UART_ReadByte(); //n
}

void SIM900_PollCommand(char * Src, char * Buff) {
  	
  	//for(int D = 0; D < 0xFF; D++);
	do {
		SIM900_WriteCommand(Src);
		SIM900_ReadRespond(Buff);
	} while (strcmp(Buff, "OK"));
}

void IO_SetLed(byte * String){
	if(!strcmp(String,"red")){
		P2OUT |= IO_LedRed;
		P2OUT &= ~IO_LedGreen;
		P2OUT &= ~IO_LedBlue;
	}else if(!strcmp(String,"green")){
		P2OUT &= ~IO_LedRed;
		P2OUT |= IO_LedGreen;
		P2OUT &= ~IO_LedBlue;
	}else if(!strcmp(String,"blue")){
		P2OUT &= ~IO_LedRed;
		P2OUT &= ~IO_LedGreen;
		P2OUT |= IO_LedBlue;
	}else if(!strcmp(String,"yellow")){
		P2OUT |= IO_LedRed;
		P2OUT |= IO_LedGreen;
		P2OUT &= ~IO_LedBlue;
	}else if(!strcmp(String,"white")){
		P2OUT |= IO_LedRed;
		P2OUT |= IO_LedGreen;
		P2OUT |= IO_LedBlue;
	}else if(!strcmp(String,"magenta")){
		P2OUT |= IO_LedRed;
		P2OUT &= ~IO_LedGreen;
		P2OUT |= IO_LedBlue;
	}else if(!strcmp(String,"cyan")){
		P2OUT &= ~IO_LedRed;
		P2OUT |= IO_LedGreen;
		P2OUT |= IO_LedBlue;
	}else if(!strcmp(String,"black")||!strcmp(String,"off")){
		P2OUT &= ~IO_LedRed;
		P2OUT &= ~IO_LedGreen;
		P2OUT &= ~IO_LedBlue;
	}else{
		UART_WriteString("Unknown color\n");
	}
}

int main(void)
{
	char Buff[128] = {0};
	char BuffOp[128] = {0};
  
	volatile uint32_t i = 0;

	WDTCTL = WDTPW | WDTHOLD;             	// Stop watchdog timer

	CSKEY = 0x695A;                       	// Unlock CS module for register access
	CSCTL0 = 0;                           	// Reset tuning parameters
	CSCTL0 = DCORSEL_3;                   	// Set DCO to 12MHz (nominal, center of 8-16MHz range)
						// Select ACLK = REFO, SMCLK = MCLK = DCO
	CSCTL1 = SELA_2 | SELS_3 | SELM_3;
	CSKEY = 0;				// Lock CS module from unintended accesses



	// Configure UART pins
	P1SEL0 |= BIT2 | BIT3;			// set 2-UART pin as second function

	// Configure UART
	UCA0CTLW0 |= UCSWRST;
	UCA0CTLW0 |= UCSSEL__SMCLK;		// Put eUSCI in reset

	// Baud Rate calculation
	// 12000000/(16*9600) = 78.125
	// Fractional portion = 0.125
	// User's Guide Table 21-4: UCBRSx = 0x10
	// UCBRFx = int ( (78.125-78)*16) = 2
	UCA0BR0 = 78;                  // 12000000/16/9600
	UCA0BR1 = 0x00;
	UCA0MCTLW = 0x1000 | UCOS16 | 0x0020;

	UCA0CTLW0 &= ~UCSWRST;			// Initialize eUSCI
	// UCA0IE |= UCRXIE;			// Enable USCI_A0 RX interrupt

	  
	P1DIR |= BIT0;				// Configure P1.0 as output
	P2DIR |= BIT0 | BIT1 | BIT2;

	IO_SetLed("white");

	SIM900_PollCommand("AT", Buff);
		
	IO_SetLed("cyan");
	
	while (1) {
	  	for(i=0xFFFF; i>1; i--);
		SIM900_WriteCommand("AT+CREG?");
		SIM900_ReadRespond(Buff);
		SIM900_ReadRespond(BuffOp); //OK
		if(!strcmp(Buff, "+CREG: 0,1"))
			break;
	}
	
	
	
	SIM900_PollCommand("AT+GSMBUSY=1", Buff);
	for(i=0xFFF; i>1; i--);
	SIM900_PollCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", Buff);
	for(i=0xFFF; i>1; i--);
	SIM900_PollCommand("AT+SAPBR=3,1,\"APN\",\"internet.mts.ru\"", Buff);
	for(i=0xFFF; i>1; i--);
	SIM900_PollCommand("AT+SAPBR=3,1,\"USER\",\"mts\"", Buff);
	for(i=0xFFF; i>1; i--);
	SIM900_PollCommand("AT+SAPBR=3,1,\"PWD\",\"mts\"", Buff);
	
	IO_SetLed("blue");
	for(i=0xFFF; i>1; i--);
	SIM900_PollCommand("AT+SAPBR=1,1", Buff); //!!!
	for(i=0xFFF; i>1; i--);
	
	IO_SetLed("yellow");
	
	SIM900_PollCommand("AT+HTTPINIT", Buff);
	for(i=0xFFF; i>1; i--);
	SIM900_PollCommand("AT+HTTPPARA=\"CID\",1", Buff);
	
	
	
	while (1) { //TODO: add break condition.
	  	char * Cmd; //Begin of the actual command.
		int Id;
		int Suc;
	  
		for(i=0xFFF; i>1; i--);
		//IO_SetLed("green");
		SIM900_PollCommand("AT+HTTPPARA=\"URL\",\"http://77.37.152.65/msp/requestget.php\"", Buff);
		for(i=0xFFF; i>1; i--);
		SIM900_PollCommand("AT+HTTPACTION=0", Buff);
		
		SIM900_ReadRespond(Buff); //+HTTPACTION:0,200,5
		
		//IO_SetLed("pink");
		
		for(i=0xFFF; i>1; i--);
		SIM900_WriteCommand("AT+HTTPREAD");
		
		SIM900_ReadRespond(Buff); //+HTTPREAD:20
		
		SIM900_ReadRespond(Buff); //<id> <command>

		SIM900_ReadRespond(BuffOp); //OK
		//IO_SetLed("cyan");
		
		Cmd = strchr(Buff, ' ');
		*Cmd = 0;
		Cmd++;
		
		Id = atoi(Buff);
		
		//IO_SetLed("red");
		
		if(!strncmp(Cmd, "set led ", sizeof("set led ") - 1)) {
			Cmd += sizeof("set led ") - 1;
			/*Suc = */IO_SetLed(Cmd); 
			Suc = 1;
						
			if(Id > 0){
				char IdStr[5];

				strcpy(BuffOp, "AT+HTTPPARA=\"URL\",\"http://77.37.152.65/msp/requestset.php?statusid=1&respond=Done.&id=");
				itoa(Id, IdStr, 10);
				strcat(BuffOp, IdStr);
				strcat(BuffOp, "\"");

				for(i=0xFFF; i>1; i--);
				SIM900_PollCommand(BuffOp, Buff);
				for(i=0xFFF; i>1; i--);
				SIM900_PollCommand("AT+HTTPACTION=0", Buff);
				
				SIM900_ReadRespond(Buff); //+HTTPACTION:0,200,5
			}
		}else if(!strncmp(Cmd, "echo ", sizeof("echo ") - 1)) {
			Cmd += sizeof("echo ") - 1;
			char IdStr[5];

			strcpy(BuffOp, "AT+HTTPPARA=\"URL\",\"http://77.37.152.65/msp/requestset.php?statusid=1&respond=");//Done.&id=");
			strcat(BuffOp, Cmd);
			strcat(BuffOp, "&id=");
			itoa(Id, IdStr, 10);
			strcat(BuffOp, IdStr);
			strcat(BuffOp, "\"");
		
			for(i=0xFFF; i>1; i--);
			SIM900_PollCommand(BuffOp, Buff);
			for(i=0xFFF; i>1; i--);
			SIM900_PollCommand("AT+HTTPACTION=0", Buff);
			
			SIM900_ReadRespond(Buff); //+HTTPACTION:0,200,5
		}
	}
	/*
	SIM900_PollCommand("AT+HTTPTERM", Buff);
	 
	SIM900_PollCommand("AT+SAPBR=0,1", Buff);
	*/
}
