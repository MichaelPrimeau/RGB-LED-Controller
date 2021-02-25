/**
 * rgbled.h
 * Lab 8
 * Michael Primeau
 * Header file for rgbled control
 */

#ifndef RGBLED_H_
#define RGBLED_H_

#include <inttypes.h>

#define RCC_APB2ENR (volatile uint32_t*) 0x40023844
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830

#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOA_AFRL (volatile uint32_t*) 0x40020020
#define GPIOA_AFRH (volatile uint32_t*) 0x40020024

#define TIM1_BASE (volatile uint32_t*) 0x40010000

typedef struct {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t RCR;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t BDTR;
	uint32_t DCR;
	uint32_t DMAR;
} TIM1;

typedef struct {
	char name[21];
	uint32_t redChannel;
	uint32_t greenChannel;
	uint32_t blueChannel;
} Color;

Color colors[5];

/**
 * void incrementRedChannel()
 * 		Increases the brightness of the red channel
 */
void incrementRedChannel();

/**
 * void incrementGreenChannel()
 * 		Increases the brightness of the green channel
 */
void incrementGreenChannel();

/**
 * void incrementBlueChannel()
 * 		Increases the brightness of the blue channel
 */
void incrementBlueChannel();

/**
 * void decrementRedChannel()
 * 		Decreases the brightness of the red channel
 */
void decrementRedChannel();

/**
 * void decrementGreenChannel()
 * 		Decreases the brightness of the green channel
 */
void decrementGreenChannel();

/**
 * void decrementBlueChannel()
 * 		Decreases the brightness of the blue channel
 */
void decrementBlueChannel();

/**
 * void saveColor(uint8_t slot, char *name)
 * 		Saves the current color on the led into the color array
 * 		Args- slot, slot to store the color in(0-4);
 * 		      *name, a pointer to the character array to name the color
 */
void saveColor(uint8_t slot, char *name);

/**
 * void loadColor(uint8_t slot)
 * 		Loads color from the array and displays it on the led
 * 		Args- slot, slot to load stored color from(0-4)
 */
void loadColor(uint8_t slot);

#endif
