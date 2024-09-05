/******************************************************************************
* Multiple Servo Motor control Library for the CH32V003 Series of MCUs
* Only uses TIM2, Non-Alternate Pins to control up to 4 Servo Motors at once.
*
* Notes:
* TIM2CH1    PD4
* TIM2CH2    PD3
* TIM2CH3    PC0
* TIM2CH4    PD7 (Disables NRST)
*
*
* 05 Sep 2024	Version 0.1
*
* Released under the MIT Licence
* Copyright ADBeta (c) 2024
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the 
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
* sell copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING BUT N00: default mapping (SCL/PC2, SDA/PC1).
01: Remapping (SCL/ PD1, SDA/ PD0).
1X: Remapping (SCL/PC5, SDA/PC6)OT LIMITED TO THE WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
* USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/
#ifndef CH32_LIB_SERVO_H
#define CH32_LIB_SERVO_H

#include "ch32v003fun.h"

/*** Structs and types *******************************************************/
typedef struct {
	GPIO_TypeDef *port_reg;
	uint32_t      port_rcc;
	uint8_t       port_pin;
} servo_config_t;

extern servo_config_t servo_pc0;


/*** API Functions ***********************************************************/
void servo_init(const servo_config_t *servo);
// servo_init
// servo_write
// servo_stop


#endif
