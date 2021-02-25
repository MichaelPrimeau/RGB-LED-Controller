/*
 *led.c
 *Lab 2
 *Michael Primeau
 */

#include "led.h"
#include "delay.h"
#include <inttypes.h>
#include <stdio.h>


//One solution for the current speed to have a local static variable in this file;
static uint8_t SPEED = 0;

/**
 * Method to initialize GPIO B for use with leds
 */
void led_init(){

	//1. ORR AHB1ENR with GPIOBEN, enables GPIOB
	*RCC_AHB1ENR |= (1<<GPIOBEN);

	*GPIOB_MODER &= ~(0x3FFF<<10);
	*GPIOB_MODER |= (0x555<<10);

	*GPIOB_MODER &= ~(0xFF<<24);
	*GPIOB_MODER |= (0x55<<24);

}

/**
 * Method to turn on all leds
 */
void led_allOn(){
	*GPIOB_ODR |= ((0b111111<<5) | (0b11111<<12));
}

/**
 * Method to turn off all leds
 */
void led_allOff(){
	*GPIOB_ODR &= ~((0b111111<<5) | (0b11111<<12));

}

/**
 * Method to turn on led at specified index
 * Args- ledIndex, Index of led to turn on (0-9)
 */
void led_on(uint8_t ledIndex){
	if (ledIndex < 6) {
		*GPIOB_ODR |= ((0b1<<5)<<ledIndex);
	} else if (ledIndex < 10) {
		*GPIOB_ODR |= ((0b1<<6)<<ledIndex);
	} else {
		printf("LED range is 0-9\n");
	}

}

/**
 * Method to turn off led at specified index
 * Args- ledIndex, Index of led to turn off (0-9)
 */
void led_off(uint8_t ledIndex){
	if (ledIndex < 6) {
			*GPIOB_ODR &= ~((0b1<<5)<<ledIndex);
		} else if (ledIndex < 10) {
			*GPIOB_ODR &= ~((0b1<<6)<<ledIndex);
		} else {
			printf("LED range is 0-9\n");
		}
}

/**
 * Method to scan across leds at the current SPEED
 * Scans back and forth 1 time
 */
void led_scan(){
	uint16_t speedFactor = 100*(10-SPEED);
	for(int i = 0; i < 10; i++) {
		led_on(i);
		delay_ms(speedFactor);
		led_off(i);
	}

	for(int i = 9; i >= 0; i--) {
		led_on(i);
		delay_ms(speedFactor);
		led_off(i);
	}

}

/**
 * Method to flash leds 10 times at the current SPEED
 */
void led_flash(){
	for (uint8_t i = 0; i < 10; i++) {
		uint16_t speedFactor = 100*(10-SPEED);
		led_allOn();
		delay_ms(speedFactor);
		led_allOff();
		delay_ms(speedFactor);
	}
}

/**
 * Method to set SPEED variable
 * Args- speed, Value to set SPEED variable to (0-9)
 */
void led_setSpeed(uint8_t speed){
	if (speed < 10 && speed >= 0) {
		SPEED = speed;
	}
}

/**
 * Method to increment SPEED variable by 1
 * Will not increment greater than 9
 */
void led_incSpeed(){
	if (SPEED < 9) {
		SPEED += 1;
	}
}

/**
 * Method to decrement SPEED variable by 1
 * Will not decrement less than 0
 */
void led_decSpeed(){
	if (SPEED > 0) {
		SPEED -= 1;
	}
}

/**
 * Return the current SPEED
 */
uint8_t getCurrentSpeed()
{
	return SPEED;
}


