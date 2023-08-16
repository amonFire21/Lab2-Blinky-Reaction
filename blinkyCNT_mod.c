/* C programs for Engs 28, Embedded Systems
 * 
 * Name: Andy Monsalve
 * Assignment: ENGS 028 - Lab 2 - blinky count with pause button
 *
 * Program name: BlinkyCNT_mod
 * Date created: 01/12/2023
 * Description: count 0 to 7 in binary by turning on LEDS and pause the counter
 * whenever the button is pressed
 *
 * Dependencies: none
 *
 * I/O pins:  (what ports are used, and what are they wired to?)
 	- I used port B in pins 0,1,2 for the LEDS on the breadboard
 	- I used port D, pin 7, for the button
 * 
 * Revisions: (use this to track the evolution of your program)
 *	- in the beginning tried using variables with an if statement to 
 *		get the counter to count and stop whenever a certain action was reached
 *		which would set the on/off the variable associated with the game
 *	- i then looked at using a switch statement which allowed me to have better control
 *		over which state I was in and how to exit out of the counting loops which was \
 *		what I struggled with when running the counter
 *	- in the unpressed state, I have used an if statement to account for when the 
 *		counter has reached 8 and how to reset the counter back to zero
 */
 
/* INCLUDE FILES */
#include <avr/io.h>			// All the port definitions are here (DDRB, PORTB)
#include <util/delay.h>

typedef enum {UNPRESSED, PRESSED}  state_t ; //define state and declare variable type
state_t state = UNPRESSED; 					 //declare variable state with type

/*  FUNCTIONS */
/* No user defined functions */

/* CONSTANTS */
#define LED_ON_TIME   1000		/* milliseconds */
#define LED_OFF_TIME  1000
#define LED_PAUSE 200

const uint8_t PIN_MASK = (1 << PIND7); // store button press as a variable

/* CODE */
int main(void)
{
  	DDRB |= (1 << DDB0);	// configure bit 0 as output
	DDRB |= (1 << DDB1);	// configure bit 1 as output
	DDRB |= (1 << DDB2);	// configure bit 2 as output
	
	DDRD  &= ~(1 << DDD7);			// configure bit 0 as input, explicitly
  									// Inputs default to floating (no internal pullup)
  	PORTD |= (1 << PORTD7);	// Turn pullup on for the input pin 
  							// (see Sec 18.2.6, "Unconnected Pins")
	
	uint8_t cntr = 8; 		// declare counter variable to counter at 8
  	uint8_t storeState = 0;	// variable to store current state of LEDs
  	uint8_t i = 0;			// variable to count through the states and turn on LEDs
	
	// Main code (runs repeatedly) goes here
	while(1) {
		switch(state){
			case UNPRESSED:
				if (i > 7){ 	//if statement checks if counter is at 7 and resets
	  					i = 0;
	  					PORTB &= ~(1 << PORTB0); // turn off LEDS and reset to 0
	  					PORTB &= ~(1 << PORTB1);
	  					PORTB &= ~(1 << PORTB2);
				}
				else{
					i = storeState; // store state of counter if not greater than 8
				}	
	  			while((i < cntr) && (state != PRESSED)){ //while unpressed, do count
					if (i < cntr){
						PORTB |= (i << PORTB0);		// set bit 1 to turn LED on
						_delay_ms(LED_ON_TIME);		// kill some time
					}
	  				if ( ((PIND & PIN_MASK) == 0 )) {	// button input is low-true &	
	  						state = PRESSED;			// so the game state changes and
	  						storeState = i;				// and stores current count
	  				} else {							
							PORTB &= ~(i << PORTB0);	// turn off if button not pressed
	  						_delay_ms(LED_OFF_TIME);	// kill some time
					}	
	  				_delay_ms(LED_PAUSE);
	  				i++; 							// continue count for while loop
	  			}
	  			break;
			case PRESSED:
				if ( (PIND & PIN_MASK) == 0 ) {	// button input is low-true, return to
	  				state = UNPRESSED;
	  			}
	  			if (i > 7){				// check to see if i count is greater than 8
	  				storeState = 0;		// and reset store state if so
	  			}
	  			break;
	  	} 			
	}
	return 0;		/* never reached */
}