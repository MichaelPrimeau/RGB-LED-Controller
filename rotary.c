/**
 * rotary.c
 * Lab 7
 * Michael Primeau
 * Contains implementation for rotary encoder functions
 */

#include "rotary.h"

// PA0 is A
// PA1 is B

// Enable interrupt on A
// A needs to be pull up

void rotaryInit() {
	// Enable clock to GPIOA
	*RCC_AHB1ENR |= 1;

	// Enable clock to SYSCFG
	*RCC_APB2ENR |= 1<<14;

	// Rotary pins by default should be input
	// Set PA0,1,12 to Pull Up
	*GPIOA_PUPDR |= 0x1000005;

	// Connect PA0 to EXTI0
	*SYSCFG_EXTICR1 &= ~(0xFF);
	// Connect PA12 to EXTI12
	*SYSCFG_EXTICR4 &= ~(0xF);

	// Unmask pin 0 in IMR
	*EXTI_IMR |= 0b01;
	*EXTI_IMR |= 0b1<<12;

	// Set falling edge trigger for pin 0 and pin 12
	*EXTI_FTSR |= 0b01;
	*EXTI_FTSR |= 0b1<<12;
	// Set rising edge trigger for pin 0
	*EXTI_RTSR |= 0b01;

	// Enable EXTI0 and EXTI12 in NVIC
	*NVIC_ISER0 |= 0b1<<6;
	*NVIC_ISER1 |= 0b1<<8;
}

void EXTI0_IRQHandler(void) {
	uint8_t inputRegister = (*GPIOA_IDR&0b11);

	// First two statements check for CW rotation
	// Second two statements check for CCW rotation
	if(inputRegister == 0b10) {
		ROTATE_RIGHT_FLAG = 1;
		switch(MODE) {
		case(0): incrementRedChannel(); break;
		case(1): incrementGreenChannel(); break;
		case(2): incrementBlueChannel(); break;
		}
	} else if(inputRegister == 0b01) {
		ROTATE_RIGHT_FLAG = 1;
		switch(MODE) {
		case(0): incrementRedChannel(); break;
		case(1): incrementGreenChannel(); break;
		case(2): incrementBlueChannel(); break;
		}
	} else if(inputRegister == 0b00) {
		ROTATE_LEFT_FLAG = 1;
		switch(MODE) {
		case(0): decrementRedChannel(); break;
		case(1): decrementGreenChannel(); break;
		case(2): decrementBlueChannel(); break;
		}
	} else if(inputRegister == 0b11) {
		ROTATE_LEFT_FLAG = 1;
		switch(MODE) {
		case(0): decrementRedChannel(); break;
		case(1): decrementGreenChannel(); break;
		case(2): decrementBlueChannel(); break;
		}
	}
	// Delay to allow second edge trigger to pass
	delay_ms(150);

	// Clear pending registers
	*NVIC_ICPR0 |= 0b1<<6;
	*EXTI_PR |= 1;
	return 0;
}

void EXTI15_10_IRQHandler(void) {
	TOGGLE_ROW_FLAG = 1;
	if(MODE < 2) {
		MODE++;
	} else {
		MODE = 0;
	}

	// Delay to account for contact bounce
	delay_ms(200);

	// Clear pending registers
	*NVIC_ICPR1 |= 0b1<<8;
	*EXTI_PR |= 1<<12;
	return 0;
}

