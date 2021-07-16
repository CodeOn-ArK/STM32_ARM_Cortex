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

int main(void)
{
	initialise_monitor_handles();
    /* Loop forever */
	printf("hello\n\r");

	__asm volatile("LDR R1,=#0x20001000");
	__asm volatile("LDR R2,=#0x20001004");
	__asm volatile("LDR R0,[R1]");
	__asm volatile("LDR R1,[R2]");
	__asm volatile("ADD R0,R0,R1");
	__asm volatile("STR R0,[R2]");

	int val = 50;
	__asm volatile("MOV R0,%0": :"r"(val));
	for(;;);
}

/*
 * General Form of an inline assembly statement
 *
 * 	Instructs the compiler 								Clobber list is used to tell
 * 	not to optimize the code							the compiler about modifications
 * 			|											done by the assembler code
 * 			|													|
 * __asm volatile(code:output operand list:input operand list:clobber list);
 * 					|			|					|
 * assembly mnemonic defined	|					|
 * as a siingle string			|					|
 * 				A list of o/ps operands,	A list of input operands,
 * 				separated by commas.			separated by commas.
 */
