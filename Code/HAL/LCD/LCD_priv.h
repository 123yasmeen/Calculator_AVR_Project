/*
 * LCD_priv.h
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */

#ifndef HAL_LCD_LCD_PRIV_H_
#define HAL_LCD_LCD_PRIV_H_

//Initialization mode
#define EIGHT_BIT         8
#define FOUR_BIT          4

#define BIT_NSEVEN        7
#define BIT_NSIX          6
#define BIT_NFIVE         5
#define BIT_NFOUR         4
#define BIT_NTHREE        3
#define BIT_NTWO          2
#define BIT_NONE          1
#define BIT_NZERO         0
static inline void LCD_inVoidSendCommand(u8 Copy_u8Command);

static void LCD_voidLatch(u8 Copy_u8Data);
#endif /* HAL_LCD_LCD_PRIV_H_ */
