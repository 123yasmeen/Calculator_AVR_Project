/*
 * main.c
 *
 *  Created on: Feb 20, 2023
 *      Author: user
 */
#include "LIB/errorStates.h"
#include "LIB/stdTypes.h"

#include "app/app_int.h"

int main()
{

	APP_enuAppInit();
	while(1)
	{
		 APP_enuStart();
	}

	return 0;
}
