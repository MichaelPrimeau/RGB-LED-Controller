/*
 * delay.c
 * Lab 2
 * Michael Primeau
 */

#include <inttypes.h>
#include "delay.h"  //include declaration header file

/**
 * Method to delay by specified amount of milliseconds
 * Args- n, Number of milliseconds to delay
 */
void delay_ms(uint32_t n){

	// Loop that runs the timer n times
	for (uint32_t i = 0; i < n; i++) {

		// Initialize SysTick Timer
		*STK_LOAD = 16000;
		*STK_CTRL |= (1<<CLKSOURCE);
		*STK_CTRL |= (1<<EN);

		while ((*STK_CTRL & (1<<COUNTFLAG)) == 0) {
			// Busy loop to check Count Flag
		}
	}





}
