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
#include "lib_servo.h"

#include <stddef.h>
#include <stdbool.h>

servo_config_t servo_pc0 = {
	.port_reg = GPIOC,
	.port_rcc = RCC_APB2Periph_GPIOC,
	.port_pin = 0
};


void servo_init(const servo_config_t *servo)
{
	// Initialise the timer, only if it has not been set up already
	static bool timer_init = false;
	if(!timer_init) 
	{
		// Enable TIM2 Clock
		RCC->APB1PCENR |= RCC_APB1Periph_TIM2;

		// Reset TIM2, Inits all registers
		RCC->APB1PRSTR |= RCC_APB1Periph_TIM2;
		RCC->APB1PRSTR &= ~RCC_APB1Periph_TIM2;

		// Set Prescaler (46kHz)
		TIM2->PSC = 0x0003;
		// Set PWM Max Value (Autoreload Value)
		TIM2->ATRLR = 254;

		// Set the Compare Capture Register for Channel 3
		// TIM2_OC3M = 0b111 - PWM Mode 2 - Enable Preload
		TIM2->CHCTLR2 |= TIM_OC3M_2 | TIM_OC3M_1 | TIM_OC3M_0 | TIM_OC3PE;

		// Enable auto-reload
		TIM2->CTLR1 |= TIM_ARPE;

		// Enable channel output, set polarity ACTIVE_LOW
		TIM2->CCER |= TIM_CC3E | TIM_CC3P;

		// Initialise Counter
		TIM2->SWEVGR |= TIM_UG;

		// Enable TIM2
		TIM2->CTLR1 |= TIM_CEN;

		timer_init = true;
	}

	// Set up the selected Servo Pin
	RCC->APB2PCENR |= servo->port_rcc;

	servo->port_reg->CFGLR &= ~(0x0F << (4 * servo->port_pin));
	servo->port_reg->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP_AF) << (4 * servo->port_pin);

	
}
