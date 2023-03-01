/*
 * app.c

 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */
#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "app_int.h"
#include "app_priv.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../HAL/KeyPad/KeyPad_int.h"
#include "../HAL/KeyPad/KeyPad_config.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"

u8 APP_Arru8StringResult[7];
u8 APP_Arru8Number1[7],APP_Arru8Number2[7],APP_u8State;
u8 APP_u8Operator,APP_u8Operand1,APP_u8Operand2;
u8 APP_u8LineCounter,APP_u8Iterator;
u8 APP_u8Res;
ES_t APP_enuAppInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	//Initialize DIO
	Local_enuErrorState=DIO_enuInit();

	//Initialize peripherals
	Local_enuErrorState=KeyPad_enuInit();
	Local_enuErrorState=LCD_enuInit();

	return Local_enuErrorState;
}

ES_t APP_enuStart(void)
{

	ES_t Local_enuErrorState=ES_NOK;
	while(APP_u8LineCounter<7)
	{
		do
		{
			//get the first number and the operator
			Local_enuErrorState=KeyPad_enuKeyPressed(&APP_Arru8Number1[APP_u8LineCounter]);
		}
		while(APP_Arru8Number1[APP_u8LineCounter] == KEY_NOT_PRESSED);
		Local_enuErrorState=LCD_enuDisplayChar(APP_Arru8Number1[APP_u8LineCounter]);

	//check which operator is pressed
	if(APP_Arru8Number1[APP_u8LineCounter]=='+')
	{
		APP_u8Operator='+';
		//set the operator index to null character to indicate the end of the first number
		APP_Arru8Number1[APP_u8LineCounter]='\0';
		break;
	}

	else if(APP_Arru8Number1[APP_u8LineCounter]=='-')
	{
		APP_u8Operator='-';
		APP_Arru8Number1[APP_u8LineCounter]='\0';
		//LCD_enuDisplayChar(APP_Arru8Number1[APP_u8LineCounter]);
		break;
	}

	else if(APP_Arru8Number1[APP_u8LineCounter]=='*')
	{
		APP_u8Operator='*';
		//LCD_enuDisplayChar(APP_u8Operator);
		APP_Arru8Number1[APP_u8LineCounter]='\0';
		break;
	}

	else if(APP_Arru8Number1[APP_u8LineCounter]=='/')
	{
		APP_u8Operator='/';
		APP_Arru8Number1[APP_u8LineCounter]='\0';
		break;
	}
	APP_u8LineCounter++;
	}

	APP_u8LineCounter=0;

while(APP_u8LineCounter<7)
{
	do
	{
		//get the second number and =
		Local_enuErrorState=KeyPad_enuKeyPressed(&APP_Arru8Number2[APP_u8LineCounter]);
	}
	while(APP_Arru8Number2[APP_u8LineCounter] == KEY_NOT_PRESSED);
    LCD_enuDisplayChar(APP_Arru8Number2[APP_u8LineCounter]);

    //check if the equal is pressed
	if(APP_Arru8Number2[APP_u8LineCounter]=='=')
	{
		//set the equal index to null character to indicate the end of the second number
		APP_Arru8Number2[APP_u8LineCounter]='\0';
		break;
	}

	APP_u8LineCounter++;
}

APP_u8LineCounter=0;
//convert the two number to integers
APP_u8Operand1=APP_inu8ConvertToInt(APP_Arru8Number1);
APP_u8Operand2=APP_inu8ConvertToInt(APP_Arru8Number2);
//switch cases to do the operations
switch(APP_u8Operator)
{
case'+':
	APP_u8Res=APP_u8Operand1 + APP_u8Operand2;
	APP_inVoidConvertToString(APP_Arru8StringResult,APP_u8Res);
		while(APP_Arru8StringResult[APP_u8Iterator]!='\0')
	{
		//display the characters of the string
		LCD_enuDisplayChar(APP_Arru8StringResult[APP_u8Iterator]);
		APP_u8Iterator++;
	}
	break;

case'-':
	APP_u8Res=APP_u8Operand1 - APP_u8Operand2;
	APP_inVoidConvertToString(APP_Arru8StringResult,APP_u8Res);
	while(APP_Arru8StringResult[APP_u8Iterator]!='\0')
	{
		//display the characters of the string
		LCD_enuDisplayChar(APP_Arru8StringResult[APP_u8Iterator]);
		APP_u8Iterator++;
	}
	break;
case'*':
	APP_u8Res=APP_u8Operand1 * APP_u8Operand2;
	APP_inVoidConvertToString(APP_Arru8StringResult,APP_u8Res);
		while(APP_Arru8StringResult[APP_u8Iterator]!='\0')
		{
			//display the characters of the string
			LCD_enuDisplayChar(APP_Arru8StringResult[APP_u8Iterator]);
			APP_u8Iterator++;
		}
	break;
case'/':
	APP_u8Res=APP_u8Operand1 / APP_u8Operand2;
	APP_inVoidConvertToString(APP_Arru8StringResult,APP_u8Res);
		while(APP_Arru8StringResult[APP_u8Iterator]!='\0')
		{
			//display the characters of the string
			LCD_enuDisplayChar(APP_Arru8StringResult[APP_u8Iterator]);
			APP_u8Iterator++;
		}
	break;
}
APP_u8Iterator=0;
//check if the user want to start new operation
do
		{
			//get the first number and the operator
			Local_enuErrorState=KeyPad_enuKeyPressed(&APP_u8State);
		}
		while(APP_u8State == KEY_NOT_PRESSED);
if(APP_u8State=='c')
{
	//Reset the LCD
	LCD_enuInit();
}
	return Local_enuErrorState;

}


static inline u8 APP_inu8ConvertToInt(u8 Copy_u8String[])
{
	u8 Local_u8Number=0;
	u8 Local_u8Iterator=0;
	while(Copy_u8String[Local_u8Iterator]!='\0')
	{
		Local_u8Number=Local_u8Number*10 + (Copy_u8String[Local_u8Iterator]-'0');
		Local_u8Iterator++;
	}

	return Local_u8Number;
}

static inline void APP_inVoidConvertToString(u8 Copy_Arru8String[],u8 Copy_u8Number)
{

	 u8 Local_u8Iterator,Local_u8Reminder;
	 u8 Local_u8Number=Copy_u8Number;
	 u8 Local_u8ArrayLength = 0;

	 while(Local_u8Number!=0)
	 {
		 Local_u8ArrayLength++;
		 Local_u8Number/=10;
	 }
	 for(Local_u8Iterator=0;Local_u8Iterator<Local_u8ArrayLength;Local_u8Iterator++)
	 {
		 Local_u8Reminder=Copy_u8Number%10;
		 Copy_u8Number=Copy_u8Number/10;
		 Copy_Arru8String[Local_u8ArrayLength-(Local_u8Iterator+1)]=Local_u8Reminder+'0';
	 }
	 Copy_Arru8String[Local_u8ArrayLength]='\0';
}
