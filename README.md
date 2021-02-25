# RGB-LED-Controller
Controller for RGB LED using a rotary encoder with a STM32 microcontroller

This project was completed on a STM32 microcontroller and used a 3-pin RGB LED and a rotary encoder. The rotary encoder was used to select the channels of the RGB LED and change their intensities to change the color of the LED. This application also makes use of a terminal to print a menu out to the user. This menu describes how the user can save colors as well as load previously saved colors.

The three channels of the LED were controlled by using three timers on the STM32. The timers were set to PWM mode, this allowed for the intensity of each channel to be changed by increasing or decreasing the amount of time that the PWM signal was active.

The channels of the LED were changed by using the rotary encoder. The encoder used interrupts to detect when the user turned the rotary encoder. The application then changed the intensity of the selected channel depending on which way the rotary encoder was rotated. The user could select which channel they are adjusting by pressing down on the rotary encoder, each time the user pushed down on the encoder the application cycled to the next channel of the LED.
