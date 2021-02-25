/**
 * rgbled.c
 * Lab 8
 * Michael Primeau
 * Contains implementation to control the rgb led
 */

#include "rgbled.h"

// Set timer to correct mode
// Set PA8,PA9,PA10

void rgbInit() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	// Enable clock to timer 1 and GPIO A
	*RCC_AHB1ENR |= 1;
	*RCC_APB2ENR |= 1;


	// Set PWM mode 1 '110' to OC1M, OC2M, OC3M
	// CCMRX registers
	timer->CCMR1 &= ~(0b111<<4);
	timer->CCMR1 &= ~(0b111<<12);
	timer->CCMR2 &= ~(0b111<<4);

	timer->CCMR1 |= (0b110<<4);
	timer->CCMR1 |= (0b110<<12);
	timer->CCMR2 |= (0b110<<4);

	// Set Prescaler to 1384
	// This creates a duty cycle of 255
	timer->PSC = 246;
	timer->ARR = 255;

	// Set GPIO mode to alternate function
	*GPIOA_MODER &= ~(0b111111<<16);
	*GPIOA_MODER |= (0b101010<<16);

	// Set alternate function to correct TIM1 channel
	*GPIOA_AFRH &= ~(0xFFF);
	*GPIOA_AFRH |= 0x111;

	timer->CCER |= 1;
	timer->CCER |= (1<<4);
	timer->CCER |= (1<<8);

	timer->BDTR |= (1<<15);

	timer->CCR1 = 0;
	timer->CCR2 = 0;
	timer->CCR3 = 0;

	timer->CR1 |= 1;
}

void incrementRedChannel() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(timer->CCR2 < 236) {
		timer->CCR2 += 20;
	}
}

void incrementGreenChannel() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(timer->CCR3 < 236) {
		timer->CCR3 += 20;
	}
}

void incrementBlueChannel() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(timer->CCR1 < 236) {
		timer->CCR1 += 20;
	}
}

void decrementRedChannel() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(timer->CCR2 > 19) {
		timer->CCR2 -= 20;
	}
}

void decrementGreenChannel() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(timer->CCR3 > 19) {
		timer->CCR3 -= 20;
	}
}

void decrementBlueChannel() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(timer->CCR1 > 19) {
		timer->CCR1 -= 20;
	}
}

void clearLed() {
	TIM1* timer = (TIM1*) TIM1_BASE;
	timer->CCR1 = 0;
	timer->CCR2 = 0;
	timer->CCR3 = 0;
}

void saveColor(uint8_t slot, char *name) {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(slot >= 0 && slot < 5) {
		colors[slot].redChannel = timer->CCR2;
		colors[slot].greenChannel = timer->CCR3;
		colors[slot].blueChannel = timer->CCR1;

		for(int i = 0; i < 20; i++) {
			colors[slot].name[i] = name[i];
		}
		colors[slot].name[21] = '\0';
	}
}

void loadColor(uint8_t slot) {
	TIM1* timer = (TIM1*) TIM1_BASE;
	if(slot >= 0 && slot < 5) {
		timer->CCR2 = colors[slot].redChannel;
		timer->CCR3 = colors[slot].greenChannel;
		timer->CCR1 = colors[slot].blueChannel;
	}
}
