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
void thread_mode();

int main(void)
{
	initialise_monitor_handles();
    /* Loop forever */
	printf("Inside main\n\r");

	thread_mode();

	//trigger the interrupt in thread mode
	generate_interrupt();

	printf("After interrupt\n\r");

	for(;;);
}

void thread_mode(){
	/*
	 * This code changes processor mode to whatever it was to thread mode
	 * useful to change processor from handler to thread mode
	 */

	//Read the contents of CONTROL reg
	__asm volatile("MRS R0,CONTROL");

	//OR the LSB with 1 to change the mode to thread mode
	__asm volatile("ORR R0,R0,#0x01");

	//Write back the value to CONTROL reg
	__asm volatile("MSR CONTROL,R0");
}
void generate_interrupt(){

	/*
	 * These areas are protected by the processor and are only to be used for system specific purpose
	 * These areas cannot be accessed when the code is in thread mode
	 * The processor needs to be in handler mode to write into these areas
	 */
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
	//u can make the pro go into thread mode inside IRQ handler
	//thread_mode();
	//printf("In handler mode\n\r");
}

void WWDG_IRQHandler(){

}

void PVD_IRQHandler(){

}

void TAMP_STAMP_IRQHandler(){

}

void HardFault_Handler(){
	printf("Hard Fault");
	while(1){};
}
