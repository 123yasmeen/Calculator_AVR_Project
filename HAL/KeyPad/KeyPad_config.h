/*
 * KeyPad_config.h
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */

#ifndef HAL_KEYPAD_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_CONFIG_H_

#define C1_PORT       DIO_u8PORTC
#define C1_PIN        DIO_u8PIN0

#define C2_PORT       DIO_u8PORTC
#define C2_PIN        DIO_u8PIN1

#define C3_PORT       DIO_u8PORTC
#define C3_PIN        DIO_u8PIN2

#define C4_PORT       DIO_u8PORTC
#define C4_PIN        DIO_u8PIN3

#define R1_PORT       DIO_u8PORTC
#define R1_PIN        DIO_u8PIN4

#define R2_PORT       DIO_u8PORTC
#define R2_PIN        DIO_u8PIN5

#define R3_PORT       DIO_u8PORTC
#define R3_PIN        DIO_u8PIN6

#define R4_PORT       DIO_u8PORTC
#define R4_PIN        DIO_u8PIN7

#define KEY_NOT_PRESSED 0xff

#define ROWS_NUM       4
#define COLUMNS_NUM    4
#define KEY_VALUES {\
	{'7','8','9','/'},\
	{'4','5','6','*'},\
	{'1','2','3','-'},\
	{'c','0','=','+'},\
}


#endif /* HAL_KEYPAD_KEYPAD_CONFIG_H_ */
