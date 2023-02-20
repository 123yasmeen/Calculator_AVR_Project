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

#include "LCD_config.h"
#include "LCD_priv.h"

ES_t LCD_enuInit(void)
{
	u8 Local_u8ErrorState=ES_NOK;

	return Local_u8ErrorState;
}

ES_t LCD_enuDisplayChar(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState=ES_NOK;

	return Local_u8ErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	u8 Local_u8ErrorState=ES_NOK;

	return Local_u8ErrorState;
}
