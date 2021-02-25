/**
 * rotary.h
 * Lab 7
 * Michael Primeau
 * Contains definition of rotary encoder functions
 */

#ifndef ROTARY_H_
#define ROTARY_H_

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB2ENR (volatile uint32_t*) 0x40023844

#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOA_PUPDR (volatile uint32_t*) 0x4002000C
#define GPIOA_IDR (volatile uint32_t*) 0x40020010

#define SYSCFG_EXTICR1 (volatile uint32_t*) 0x40013808
#define SYSCFG_EXTICR4 (volatile uint32_t*) 0x40013814

#define EXTI_IMR (volatile uint32_t*) 0x40013C00
#define EXTI_RTSR (volatile uint32_t*) 0x40013C08
#define EXTI_FTSR (volatile uint32_t*) 0x40013C0C
#define EXTI_PR (volatile uint32_t*) 0x40013C14

#define NVIC_ISER0 (volatile uint32_t*) 0xE000E100
#define NVIC_ISER1 (volatile uint32_t*) 0xE000E104
#define NVIC_ICPR0 (volatile uint32_t*) 0xE000E280
#define NVIC_ICPR1 (volatile uint32_t*) 0xE000E284

uint8_t ROTATE_RIGHT_FLAG;
uint8_t ROTATE_LEFT_FLAG;
uint8_t TOGGLE_ROW_FLAG;
uint8_t MODE;


/**
 * Enables GPIO pins and interrupts for rotary encoder
 */
void rotaryInit();

/**
 * Interrupt handler to detect rotation on the rotary encoder
 * Sets appropriate flag for rotation
 */
void EXTI0_IRQHandler(void)__attribute__((isr));

/**
 * Interrupt handler to detect push button input
 * Sets appropriate flag for the push button
 */
void EXTI15_10_IRQHandler(void)__attribute__((isr));


#endif
