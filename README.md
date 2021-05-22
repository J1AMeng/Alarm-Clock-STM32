# Alarm-Clock STM32
Final project of STM32 course.

* Lecturer: Arseniy Poyda
* Length of course: 1 semester
* When was passed: 2 semester
* Language: Russian

## Connection
Seven-segment display can be connected in the following way: 
 * Pins from PC0 to PC6 are segments a, b, c, ..., g respectively.
 * Pins from PC7 to PC10 are numbers 1-4.
 * Pin PC11 is a dot (separates minutes and hours).

Now let's connect two addition buttons to manage the tuning:
 * It is enough to use 3V or 5V and pins PC13 and PC14 respectively.

OK. Piezo speaker is left. Use GND and PA5.
Now the alarm is in a workable state.

## Usage
Everything is simple. In default state alarm-clock shows the counting time from scratch. You are to set the alarm time. Algorithm is as follows: clamp USER button, now you are in tune regime. Using buttons you can increase or decrease set time in minutes. To begin manipulate with hours clamp the left button (PC13). To arrive (to manipulate with minutes again) clamp the right button (PC14). So, when you are ready to continue, clamp USER button again. Now alarm time is set.

When a wonderful music begins to play, you have 3 veriants: to turn off the music (USER button), to delay the time for 5 minutes (the left button) or for 10 minutes (the right button). Here was the concise description of simple alarm-clock.

Thank you for attention.

