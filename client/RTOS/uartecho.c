/*
 * Copyright (c) 2015, Texas Instruments Incorporated
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
 */

/*
 *  ======== uartecho.c ========
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Example/Board Header files */
#include "Board.h"

#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <string.h>

#define TASKSTACKSIZE     768

#ifndef null
#define null NULL
#endif

#ifndef byte
#define byte unsigned char
#endif

//Without this IAR cant normaly make solution for stand-alone application. DO NOT REMOVE.
void __write(){
	//DO NOT REMOVE ME.
}

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];
/*
 *  ======== echoFxn ========
 *  Task for this function is created statically. See the project's .cfg file.
 */

byte IO_SetLed(byte * String){
	if(!strcmp(String,"red")){
		GPIO_write(Board_LED1,Board_LED_ON);
		GPIO_write(Board_LED2,Board_LED_OFF);
		GPIO_write(Board_LED3,Board_LED_OFF);
		return 0;
	}else if(!strcmp(String,"green")){
		GPIO_write(Board_LED1,Board_LED_OFF);
		GPIO_write(Board_LED2,Board_LED_ON);
		GPIO_write(Board_LED3,Board_LED_OFF);
		return 0;
	}else if(!strcmp(String,"blue")){
		GPIO_write(Board_LED1,Board_LED_OFF);
		GPIO_write(Board_LED2,Board_LED_OFF);
		GPIO_write(Board_LED3,Board_LED_ON);
		return 0;
	}else if(!strcmp(String,"yellow")){
		GPIO_write(Board_LED1,Board_LED_ON);
		GPIO_write(Board_LED2,Board_LED_ON);
		GPIO_write(Board_LED3,Board_LED_OFF);
		return 0;
	}else if(!strcmp(String,"white")){
		GPIO_write(Board_LED1,Board_LED_ON);
		GPIO_write(Board_LED2,Board_LED_ON);
		GPIO_write(Board_LED3,Board_LED_ON);
		return 0;
	}else if(!strcmp(String,"pink")){
		GPIO_write(Board_LED1,Board_LED_ON);
		GPIO_write(Board_LED2,Board_LED_OFF);
		GPIO_write(Board_LED3,Board_LED_ON);
		return 0;
	}else if(!strcmp(String,"cyan")){
		GPIO_write(Board_LED1,Board_LED_OFF);
		GPIO_write(Board_LED2,Board_LED_ON);
		GPIO_write(Board_LED3,Board_LED_ON);
		return 0;
	}else if(!strcmp(String,"black")||!strcmp(String,"off")){
		GPIO_write(Board_LED1,Board_LED_OFF);
		GPIO_write(Board_LED2,Board_LED_OFF);
		GPIO_write(Board_LED3,Board_LED_OFF);
		return 0;
	}else{
		return 1;
	}
}

void SIM900_WriteCommand(UART_Handle Uart, char * Src) {
	UART_writePolling(Uart, Src, strlen(Src));
	UART_writePolling(Uart, "\r\n", 2);
}

//(Any) respond of SIM900 module consists of "\r\n<TEXT>\r\n"
void SIM900_ReadRespond(UART_Handle Uart, char * Dst) {
	char Dat;
	int i = 0;

	UART_readPolling(Uart, &Dat, 1); //r
	UART_readPolling(Uart, &Dat, 1); //n
	while (1) {
		UART_readPolling(Uart, &Dat, 1);
		if(Dat != '\r') {
			*(Dst + i) = Dat;
		} else {
		  	*(Dst + i) = 0;
			break;
		}
		i++;
	}
	UART_readPolling(Uart, &Dat, 1); //n
}

void SIM900_PollCommand(UART_Handle Uart, char * Src, char * Buff) {
  	
  	//for(int D = 0; D < 0xFF; D++);
	do {
		SIM900_WriteCommand(Uart, Src);
		SIM900_ReadRespond(Uart, Buff);
	} while (strcmp(Buff, "OK"));
}

Void echoFxn(UArg arg0, UArg arg1)
{
	unsigned int D = 0;
	char Buff[128] = {0};
	char BuffOp[128] = {0};
	UART_Handle uart;
	UART_Params uartParams;
	//const char echoPrompt[] = "\fEchoing characters:\r\n";

	/* Create a UART with data processing off. */
	UART_Params_init(&uartParams);
	uartParams.writeDataMode = UART_DATA_BINARY;
	uartParams.readDataMode = UART_DATA_BINARY;
	uartParams.readReturnMode = UART_RETURN_FULL;
	uartParams.readEcho = UART_ECHO_OFF;
	uartParams.baudRate = 9600;
	uart = UART_open(Board_UART0, &uartParams);

	if (uart == NULL) {
		System_abort("Error opening the UART");
	}
	
	for(D = 0; D < 0xFFFF; D++); //TODO: move delay into PollCommand() function.
	SIM900_PollCommand(uart, "AT", Buff);
	
	IO_SetLed("cyan");
	
	while (1) {
	  	for(D = 0; D < 0xFFFF; D++);
		SIM900_WriteCommand(uart, "AT+CREG?");
		SIM900_ReadRespond(uart, Buff);
		if(!strcmp(Buff, "+CREG: 0,1"))
			break;
		for(D = 0; D < 0xFFFF; D++);
		SIM900_ReadRespond(uart, Buff); //OK
	}
	
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+GSMBUSY=1", Buff);
	
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", Buff);
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+SAPBR=3,1,\"APN\",\"internet.mts.ru\"", Buff);
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+SAPBR=3,1,\"USER\",\"mts\"", Buff);
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+SAPBR=3,1,\"PWD\",\"mts\"", Buff);
	
	//IO_SetLed("blue");
	
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+SAPBR=1,1", Buff); //!!!
	
	//IO_SetLed("yellow");
	
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+HTTPINIT", Buff);
	for(D = 0; D < 0xFFFF; D++);
	SIM900_PollCommand(uart, "AT+HTTPPARA=\"CID\",1", Buff);
	
	//IO_SetLed("green");
	
	while (1) { //TODO: add break condition.
	  	char * Cmd; //Begin of the actual command.
		int Id;
		int Suc;
	  
		for(D = 0; D < 0xFFFF; D++);
		SIM900_PollCommand(uart, "AT+HTTPPARA=\"URL\",\"http://77.37.152.65/msp/requestget.php\"", Buff);
		for(D = 0; D < 0xFFFF; D++);
		SIM900_PollCommand(uart, "AT+HTTPACTION=0", Buff);
		
		SIM900_ReadRespond(uart, Buff); //+HTTPACTION:0,200,5
		
		//IO_SetLed("pink");
		
		for(D = 0; D < 0xFFFF; D++);
		SIM900_WriteCommand(uart, "AT+HTTPREAD");
		
		SIM900_ReadRespond(uart, Buff); //+HTTPREAD:20
		
		SIM900_ReadRespond(uart, Buff); //<id> <command>

		SIM900_ReadRespond(uart, BuffOp); //OK
		//IO_SetLed("cyan");
		
		Cmd = strchr(Buff, ' ');
		*Cmd = 0;
		Cmd++;
		
		Id = atoi(Buff);
		
		//IO_SetLed("red");
		
		if(strncpy(Cmd, "set led ", sizeof("set led ") - 1)) {
			Cmd += sizeof("set led ") - 1;
			Suc = IO_SetLed(Cmd);
		} //else???
		
		
		sprintf(Buff, "AT+HTTPPARA=\"URL\",\"http://77.37.152.65/msp/requestset.php?statusid=%d&respond=Done.&id=%d\"", Suc+1, Id);
		for(D = 0; D < 0xFFFF; D++);
		SIM900_PollCommand(uart, "AT+HTTPACTION=0", Buff);
		
		SIM900_ReadRespond(uart, Buff); //+HTTPACTION:0,200,5
	}
	/*
	SIM900_PollCommand(uart, "AT+HTTPTERM", Buff);
	 
	SIM900_PollCommand(uart, "AT+SAPBR=0,1", Buff);
	*/
	
}

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */ 
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();

    /* Construct BIOS objects */
    Task_Params taskParams;

    Task_Params_init(&taskParams);
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    taskParams.instance->name = "echo";
    //taskParams.priority = 15; //?
    Task_construct(&task0Struct, (Task_FuncPtr)echoFxn, &taskParams, NULL);

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);
    
    GPIO_write(Board_LED1, Board_LED_ON);
    GPIO_write(Board_LED2, Board_LED_ON);
    GPIO_write(Board_LED3, Board_LED_ON);

    /* This example has logging and many other debug capabilities enabled */
    System_printf("This example does not attempt to minimize code or data "
                  "footprint\n");
    System_flush();

    System_printf("Starting the UART Echo example\nSystem provider is set to "
                  "SysMin. Halt the target to view any SysMin contents in "
                  "ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
