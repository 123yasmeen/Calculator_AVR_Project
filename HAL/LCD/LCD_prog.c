/*
 * LCD_prog.c
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/DIO/DIO_config.h"
#include "../../MCAL/DIO/DIO_priv.h"

#include "LCD_config.h"
#include "LCD_priv.h"

#include "util/delay.h"

ES_t LCD_enuInit(void)
{
	u8 Local_u8ErrorState=ES_NOK;

	_delay_ms(30);
	//set RS-RW-EN-DB7:DB4 as output
	Local_u8ErrorState=DIO_enuSetPinDirection(RS_PORT,RS_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(RW_PORT,RW_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(EN_PORT,EN_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D7_PORT,D7_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D6_PORT,D6_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D5_PORT,D5_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D4_PORT,D4_PIN,DIO_u8OUTPUT);

#if LCD_MODE==EIGHT_BIT
	//Set DB3:DB0 as output
	Local_u8ErrorState=DIO_enuSetPinDirection(D3_PORT,D3_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D2_PORT,D2_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D1_PORT,D1_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(D0_PORT,D0_PIN,DIO_u8OUTPUT);

	//Send command to function Set
	LCD_inVoidSendCommand(0x38);
#elif LCD_MODE==FOUR_BIT
	LCD_inVoidSendCommand(0x28);
#endif
	_delay_ms(1);

	//Display ON/OFF control
	LCD_inVoidSendCommand(0x0f);
	_delay_ms(1);

	//Display clear
	LCD_inVoidSendCommand(0x01);
	_delay_ms(2);

	//Entry mode set
	LCD_inVoidSendCommand(0x06);

	return Local_u8ErrorState;
}

ES_t LCD_enuDisplayChar(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState=ES_NOK;
	//Set RS as data
	Local_u8ErrorState=DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);
	LCD_voidLatch(Copy_u8Data);

	return Local_u8ErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	u8 Local_u8ErrorState=ES_NOK;
	//Set RS as command
	Local_u8ErrorState=DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);
	LCD_voidLatch(Copy_u8Command);

	return Local_u8ErrorState;
}

static void LCD_voidLatch(u8 Copy_u8Data)
{
	//Set RW as write operation
	DIO_enuSetPinValue(RW_PORT,RW_PIN,DIO_u8LOW);
    //Set Enable to low
    DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);
    //Write The Data
   DIO_enuSetPinValue(D7_PORT,D7_PIN,((Copy_u8Data>>BIT_NSEVEN)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D6_PORT,D6_PIN,((Copy_u8Data>>BIT_NSIX)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D5_PORT,D5_PIN,((Copy_u8Data>>BIT_NFIVE)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D4_PORT,D4_PIN,((Copy_u8Data>>BIT_NFOUR)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D3_PORT,D3_PIN,((Copy_u8Data>>BIT_NTHREE)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D2_PORT,D2_PIN,((Copy_u8Data>>BIT_NTWO)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D1_PORT,D1_PIN,((Copy_u8Data>>BIT_NONE)&DIO_MASK_BIT));
   DIO_enuSetPinValue(D0_PORT,D0_PIN,((Copy_u8Data>>BIT_NZERO)&DIO_MASK_BIT));
    //Set Enable to high (Rising Edge)
    DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
    _delay_ms(10);
    //Set Enable to low
   DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);
}
static inline void LCD_inVoidSendCommand(u8 Copy_u8Command)
{
	//Set RS command
    DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);
    //Set RW as write operation
    DIO_enuSetPinValue(RW_PORT,RW_PIN,DIO_u8LOW);
    //Set Enable to low
    DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);
    //Write The Data
    DIO_enuSetPinValue(D7_PORT,D7_PIN,((Copy_u8Command>>BIT_NSEVEN)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D6_PORT,D6_PIN,((Copy_u8Command>>BIT_NSIX)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D5_PORT,D5_PIN,((Copy_u8Command>>BIT_NFIVE)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D4_PORT,D4_PIN,((Copy_u8Command>>BIT_NFOUR)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D3_PORT,D3_PIN,((Copy_u8Command>>BIT_NTHREE)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D2_PORT,D2_PIN,((Copy_u8Command>>BIT_NTWO)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D1_PORT,D1_PIN,((Copy_u8Command>>BIT_NONE)&DIO_MASK_BIT));
    DIO_enuSetPinValue(D0_PORT,D0_PIN,((Copy_u8Command>>BIT_NZERO)&DIO_MASK_BIT));
    //Set Enable to high (Rising Edge)
    DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
    _delay_ms(10);
    //Set Enable to low
    DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);
 }
