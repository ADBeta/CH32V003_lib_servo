/******************************************************************************
* Basic Example of using lib_i2c on the CH32V003 Microcontroller
*
* Demo Version 1.0.0    25 Aug 2024
* See GitHub Repo for more information: 
* https://github.com/ADBeta/CH32V000x-lib_i2c
*
* Released under the MIT Licence
* Copyright ADBeta (c) 2024
******************************************************************************/
#include "ch32v003fun.h"
#include "lib_servo.h"

#include <stdio.h>


int main() 
{
	SystemInit();
	
	servo_init(&servo_pc0);

	// Loop forever
	uint8_t duty = 0;
	while(1)
	{
		TIM2->CH3CVR = duty++;
		Delay_Ms(1);
	}

	return 0;
}
