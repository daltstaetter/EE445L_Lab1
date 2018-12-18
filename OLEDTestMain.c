// OLEDTestMain.c
// Runs on LM3S1968
// Test Output.c by sending various characters and strings to
// the OLED display and verifying that the output is correct.
// Daniel Valvano
// July 28, 2011

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to the Arm Cortex M3",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2011
   Section 3.4.5

 Copyright 2011 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

#include <stdio.h>
#include "Output.h"
#include "fixed.h"
#include <string.h>

// delay function for testing from sysctl.c
// which delays 3*ulCount cycles
#ifdef __TI_COMPILER_VERSION__
	//Code Composer Studio Code
	void Delay(unsigned long ulCount){
	__asm (	"    subs    r0, #1\n"
			"    bne     Delay\n"
			"    bx      lr\n");
}

#else
	//Keil uVision Code
	__asm void
	Delay(unsigned long ulCount)
	{
    subs    r0, #1
    bne     Delay
    bx      lr
	}

#endif


	void myFunction(char* string)
	{
		printf("%s",string);
		printf("%c",NEWLINE);
		
	}




int main(void)
{
	
	char string[10];
	
  Output_Init();
  Output_Color(8);
	
	Fixed_uDecOut2(12345);
	Fixed_uDecOut2(22100);
	Fixed_uDecOut2(102);
	Fixed_uDecOut2(31);
	Fixed_uDecOut2(99999);
	Fixed_uDecOut2(100000);
	Delay(6000000);
	printf("%c",NEWLINE);
	
	Fixed_sDecOut3(2345);
	Fixed_sDecOut3(-2345);
	Fixed_sDecOut3(8100);
	Fixed_sDecOut3(-8100);
	Fixed_sDecOut3(102);
	Fixed_sDecOut3(-102);
	Fixed_sDecOut3(31);
	Fixed_sDecOut3(-31);
	Delay(6000000);
	printf("%c",NEWLINE);
	
	Fixed_uBinOut8(0);
	Fixed_uBinOut8(2);
	Fixed_uBinOut8(64);
	Fixed_uBinOut8(100);
	Fixed_uBinOut8(500);
	Fixed_uBinOut8(512);
	Fixed_uBinOut8(5000);
	Fixed_uBinOut8(30000);
	Fixed_uBinOut8(255997);
	Fixed_uBinOut8(256000);
	Delay(6000000);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	
//  printf("Hello, world.");
//  printf("%c", NEWLINE);
//  Delay(2000000);           // delay ~1 sec at 12 MHz
//	
//	Output_Color(4);
//	Fixed_uDecOut2s(12345,  &string[0]);
//	  printf("%s%c", string);
//	
//	Delay(3000000);
//	
//	
//Output_Color(13);
//	Fixed_uDecOut2(12345);
//Delay(3000000);
  Output_Clear();
  //printf("Hello, world.\n",NEWLINE);

	
//	 
//  Fixed_uDecOut2(12345);
//	printf("%c", NEWLINE);
//	Delay(4000000);           // delay ~1 sec at 12 MHz
//	
//	
//	Fixed_uDecOut2(22100);
//	printf("%c", NEWLINE);
//	Delay(4000000);		
//		
//		
//	Fixed_uDecOut2(102);
//	printf("%c", NEWLINE);
//	Delay(4000000);
//				
//		
//	Fixed_uDecOut2(31);
//	printf("%c", NEWLINE);
//	Delay(4000000);
//		
//	Fixed_uDecOut2(99999);
//	printf("%c", NEWLINE);
//	Delay(4000000);
//	
	
	
  //Output_Clear();
  while(1){};
}
