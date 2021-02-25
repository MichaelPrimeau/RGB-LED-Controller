/**
 * main.c
 * Lab 8
 * Michael Primeau
 * Implements the main program for rgb led control
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "rgbled.h"
#include "delay.h"
#include "rotary.h"
#include "uart_driver.h"

#define F_CPU 16000000UL
#define ARSIZE 10

int main(void)
{
	// Initialize components being used
	init_usart2(19200,F_CPU);
	rgbInit();
	rotaryInit();
	MODE = 0;

	// Display menu of options for user
	char userInput[10] = {0};
	uint8_t slot;
	while(1) {
		printf("*************************************************\n");
		printf("Home Menu - Type the keyword to execute the command\n");
		printf("save    -- Save current color on led\n");
		printf("load    -- Load a saved color from memory\n");
		printf("print   -- Print all saved colors\n");
		printf("*************************************************\n");

		// Check for user input and execute command
		scanf("%10s", userInput);
		if(strcmp(userInput, "save") == 0) {
			char name[21];
			printf("Select a save slot (0-4): ");
			scanf("%1d", &slot);
			printf("Enter a name with no spaces: ");
			scanf("%20s", name);
			saveColor(slot, &name);

		} else if(strcmp(userInput, "load") == 0) {
			printf("Select a save slot (0-4): ");
			scanf("%1d", &slot);
			loadColor(slot);

		} else if(strcmp(userInput, "print") == 0) {
			for(int i = 0; i < 5; i++) {
				printf("Slot %1d: %s\n", i, colors[i].name);
			}

		}
	}
}
