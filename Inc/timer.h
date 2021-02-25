/**
 * timer.h
 * Lab 7
 * Michael Primeau
 * Contains functions to make use of a general purpose timer
 * Uses TIM4
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <inttypes.h>

#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define TIM5_BASE (volatile uint32_t*) 0x40000C00

#define SYSCFG_EXTICR1 (volatile uint32_t*) 0x40013808
#define SYSCFG_EXTICR4 (volatile uint32_t*) 0x40013814

#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define NVIC_ISER1 (volatile uint32_t*) 0xE000E104
#define NVIC_ICPR0 (volatile uint32_t*) 0xE000E280
#define NVIC_ICPR1 (volatile uint32_t*) 0xE000E284

#define NVIC_ISPR1 (volatile uint32_t*) 0xE000E204

/**
 * Struct register access for TIM5
 */
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
	uint32_t CCR1;
} TIM5;

/**
 * Initializes timer and enables interrupts on the time
 */
void timerInit();

/**
 * Starts the timer and begins counting seconds
 */
void startTimer();

/**
 * Stops the timer and returns the final time in seconds to the argument address
 * Args- finalTime - the address where the final time recorded should be stored
 */
void stopTimer(float* finalTime);

/**
 * Interrupt handler for TIM5
 * Increments the seconds count by one each on each overflow event
 */
void TIM5_IRQHandler(void)__attribute__((isr));



#endif
