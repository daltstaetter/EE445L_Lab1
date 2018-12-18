#include <stdio.h>
#include "fixed.h"
#include <string.h>

/****************Fixed_uDecOut2s***************
 converts fixed point number to ASCII string
 format unsigned 32-bit with resolution 0.01
 range 0 to 999.99
 Input: unsigned 32-bit integer part of fixed point number
         greater than 99999 means invalid fixed-point number
 Output: null-terminated string exactly 6 characters plus null
 Examples
 12345 to "123.45"  
 22100 to "221.00"
   102 to "  1.02" 
    31 to "  0.31" 
100000 to "***.**"    */ 
void Fixed_uDecOut2s(unsigned long n,  char *string)
{
	int hundreds;
	int tens;
	int ones;
	int tenths;
	int one_hundredths;
	int temp_num;
	
	if (n > 99999)
	{
		// return invalid fixed-point number as ***.**
		string[0] = '*';
		string[1] = '*';
		string[2] = '*';
		string[3] = '.';
		string[4] = '*';
		string[5] = '*';
		string[6] = 0;

		return;
	}

	else
	{
		temp_num = n;

		hundreds = n/10000;    					// capture fix-point hundreds place
		temp_num %= 10000;     					// temp_num is now between 0-9999
	
		tens = temp_num/1000;   				// capture fix-point tens place
		temp_num %= 1000;     					// temp_num is now between 0-999
	
		ones = temp_num/100;   					// capture fix-point ones place
		temp_num %= 100;       					// temp_num is now between 0-99
	
		tenths = temp_num/10;   				// capture fix-point tenths place
		temp_num %= 10;                         // temp_num is now between 0-9
	
		one_hundredths = temp_num;   		    // capture fix-point one_hundredths place
	
		string[0] = hundreds + '0';
		string[1] = tens + '0';
		string[2] = ones + '0';
		string[3] = '.';
		string[4] = tenths + '0';
		string[5] = one_hundredths + '0';
		string[6] = 0;

		if (string[0] == '0')
		{
			string[0] = ' ';

			if(string[1] == '0')
			{
				string[1] = ' ';
			}
		}

		return;
	}
}


 /****************Fixed_uDecOut2***************
 outputs the fixed-point value on the OLED
 format unsigned 32-bit with resolution 0.01
 range 0 to 999.99
 Input: unsigned 32-bit integer part of fixed point number
         greater than 99999 means invalid fixed-point number
 Output: none
 Examples
 12345 to "123.45"  
 22100 to "221.00"
   102 to "  1.02" 
    31 to "  0.31" 
100000 to "***.**"    */ 
void Fixed_uDecOut2(unsigned long n) 
{
	char string[10];
	Fixed_uDecOut2s(n,&string[0]);
	printf("%s\n", &string[0]);
	return;
}

/****************Fixed_sDecOut3s***************
 converts fixed point number to ASCII string
 format signed 32-bit with resolution 0.001
 range -9.999 to +9.999
 Input: signed 32-bit integer part of fixed point number
 Output: null-terminated string exactly 6 characters plus null
 Examples
  2345 to " 2.345"  
 -8100 to "-8.100"
  -102 to "-0.102" 
    31 to " 0.031" 
   
 */ 
void Fixed_sDecOut3s(long n, char *string) 
{
	
	int temp_num;
	int ones;
	int tenths;
	int one_hundredths;
	int one_thousandths;
	
	if (n > 9999 || n < -9999)
	{
		// return invalid fixed-point number as *.***
		string[0] = ' ';
		string[1] = '*';
		string[2] = '.';
		string[3] = '*';
		string[4] = '*';
		string[5] = '*';
		string[6] = 0;
	}
	else {
		
		
		//checks if negative
		if(n < 0) {
			string[0] = '-';
			n = -1*n;
		}
		else {
			string[0] = ' ';
		}
		
		temp_num = n;

		ones = n/1000;    					// capture fix-point hundreds place
		temp_num %= 1000;     					// temp_num is now between 0-9999
		string[1] = ones + 0x30;
		
		string[2] = 0x2E;						// '.' = 0x2E
		
		tenths = temp_num/100;   				// capture fix-point tens place
		temp_num %= 100;     					// temp_num is now between 0-999
		string[3] = tenths + 0x30;
		
		one_hundredths = temp_num/10;   				// capture fix-point tenths place
		temp_num %= 10;  								// temp_num is now between 0-9
		string[4] = one_hundredths + 0x30;
		
		
		one_thousandths = temp_num;   		// capture fix-point one_hundredths place
		string[5] = one_thousandths + 0x30;
		
		string[6] = 0;									//adds null
	}
	
	return;
}



/****************Fixed_sDecOut3***************
 converts fixed point number to OLED
 format signed 32-bit with resolution 0.001
 range -9.999 to +9.999
 Input: signed 32-bit integer part of fixed point number
 Output: none
 OLED has exactly 6 characters
 Examples
  2345 to " 2.345"  
 -8100 to "-8.100"
  -102 to "-0.102" 
    31 to " 0.031" 
 */ 
void Fixed_sDecOut3(long n) 
{
	char string[10];
	Fixed_sDecOut3s(n, &string[0]);
	printf("%s\n", &string[0]);
	return;
}


/**************Fixed_uBinOut8s***************
 unsigned 32-bit binary fixed-point with a resolution of 1/256. 
 The full-scale range is from 0 to 999.99. 
 If the integer part is larger than 256000, it signifies an error. 
 The Fixed_uBinOut8 function takes an unsigned 32-bit integer part 
 of the binary fixed-point number and outputs the fixed-point value on the OLED. 
 Input: unsigned 32-bit integer part of fixed point number
 Output: null-terminated string
Parameter output string
     0     "  0.00"
     2     "  0.01"
    64     "  0.25"
   100     "  0.39"
   500     "  1.95"
   512     "  2.00"
  5000     " 19.53"
 30000     "117.19"
255997     "999.99"
256000     "***.**"
*/
void Fixed_uBinOut8s(unsigned long n,  char *string)
{
	// put into fixed-point format then call snprintf
	
    int remainder;
	int fraction;
	int integer;

	char a[6] = {0};
	char c[6] = {0};

	fraction = 0;
	integer = 0;


	if ( n > 255999)
	{
		string[0] = '*';
		string[1] = '*';
		string[2] = '*';
		string[3] = '.';
		string[4] = '*';
		string[5] = '*';
		string[6] = 0;
		return;
	}

	remainder = n & 0x000000FF; // isolates the decimal digits, bits 0-7

	integer = n/256;

	if ( remainder == 255)
		remainder = 254; // prevents rollover from the next eqn
	fraction = (remainder*25)/64;  // eqn is reduced from (1/256)*(remainder*99+32)

	_snprintf(&string[0],3,"%3d",integer);      // this is a microsoft function & isn't the...
	string[3] = '.';                            // ...standard snprintf, it doesn't null terminate
	_snprintf(&string[4],2,"%02d",fraction);
	string[6] = 0; // not really necessary but just to be safe

	return;
}

/**************Fixed_uBinOut8***************
 unsigned 32-bit binary fixed-point with a resolution of 1/256. 
 The full-scale range is from 0 to 999.99. 
 If the integer part is larger than 256000, it signifies an error. 
 The Fixed_uBinOut8 function takes an unsigned 32-bit integer part 
 of the binary fixed-point number and outputs the fixed-point value on the OLED. 
 Input: unsigned 32-bit integer part of fixed point number
 Output: none
Parameter OLED display
     0	  0.00
     2	  0.01
    64	  0.25
   100	  0.39
   500	  1.95
   512	  2.00
  5000	 19.53
 30000	117.19
255997	999.99
256000	***.**
*/
void Fixed_uBinOut8(unsigned long n)
{
	char string[10];
	Fixed_uBinOut8s(n, &string[0]);
	printf("%s\n", &string[0]);
	return;
}