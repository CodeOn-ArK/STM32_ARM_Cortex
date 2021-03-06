/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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
void set_interrupt();

#define ADC_IRQ_POSITION 18

int main(void)
{
	initialise_monitor_handles();
    /* Loop forever */
	printf("hello\n\r");

	set_interrupt();

	//Clear the pending bit in NVIC's ICER
	uint32_t *ADC_NVIC_ICER = (uint32_t *)(0XE000E180);
	*ADC_NVIC_ICER |= (0x1 << ADC_IRQ_POSITION);

	for(;;);
}


void set_interrupt(){
	uint32_t *ADC_NVIC_ISER = (uint32_t *)(0xE000E100);
	uint32_t *ADC_NVIC_ISPR = (uint32_t *)(0XE000E200);

	//Set the interrupt's ISER in NVIC
	*ADC_NVIC_ISER = (0x1 << ADC_IRQ_POSITION);
	//Pend the interrupt
	*ADC_NVIC_ISPR = (0x1 << ADC_IRQ_POSITION);

}

void ADC_IRQHandler(){
	printf("In ADC");
}
