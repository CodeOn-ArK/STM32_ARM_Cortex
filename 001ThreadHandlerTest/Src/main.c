/**
 ******************************************************************************
 * @file           : main.c
 * @author         : CodeOn-ArK
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);
void generate_interrupt();

int main(void)
{
	initialise_monitor_handles();
    /* Loop forever */
	printf("Inside main\n\r");

	//trigger the interrupt in thread mode
	generate_interrupt();

	printf("After interrupt\n\r");

	for(;;);
}

void generate_interrupt(){

	uint32_t *pSTIR		= (uint32_t *)0xE000EF00;
	uint32_t *pISER0	= (uint32_t *)0xE000E100;

	//Enable IRQ interrupt
	*pISER0 |= (0x1 << 3);

	//Generate an interrupt from software for IRQ
	*pSTIR = (0x3 & 0x1FF);

	printf("Interrupted\n\r");
}

void RTC_WKUP_IRQHandler(){

	printf("In handler mode\n\r");
}

void WWDG_IRQHandler(){

}

void PVD_IRQHandler(){

}

void TAMP_STAMP_IRQHandler(){

}
