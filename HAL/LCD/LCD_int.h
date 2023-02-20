/*
 * LCD_int.h
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

ES_t LCD_enuInit(void);

ES_t LCD_enuDisplayChar(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);
#endif /* HAL_LCD_LCD_INT_H_ */
