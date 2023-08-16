/* C programs for Engs 28, Embedded Systems
 * 
 * Name: Andy Monsalve
 * Assignment: ENGS 028 - Lab 2 - Reaction-time Game
 *
 * Program name: Reaction Game
 * Date created: 01/08/2023
 * Description: 
 * begin the game when the user presses the button and the first person
 * to press the button wins the game and the game resets 
 *
 * Dependencies: none
 *
 * I/O pins:  (what ports are used, and what are they wired to?)
 * 
 * Revisions: (use this to track the evolution of your program)
 *
 */
 
/* INCLUDE FILES */
#include <avr/io.h>			// All the port definitions are here (DDRB, PORTB)
#include <util/delay.h>

typedef enum {GAME_OFF, GAME_ON}  game_t ;
game_t game = GAME_OFF;

/*  FUNCTIONS */
/* No user defined functions */

/* CONSTANTS */
#define LED_ON_TIME   1000		/* milliseconds */
#define LED_OFF_TIME  1000
#define LED_PAUSE 500
#define GAME_NOT_ON 100
#define GAME_COUNTDOWN 100



const uint8_t PIN_MASK2 = (1 << PIND7);
const uint8_t PIN_MASK1 = (1 << PIND6);

/* CODE */
int main(void)
{
  	DDRB |= (1 << DDB0);	// configure bit 0 as output
	DDRB |= (1 << DDB1);	// configure bit 1 as output
	DDRB |= (1 << DDB2);	// configure bit 2 as output
	
	DDRD &= ~(1 << DDD7);	
	DDRD &= ~(1 << DDD6);		// configure bit 0 as input, explicitly
  	// Inputs default to floating (no internal pullup)
  	// Turn pullup on for the input pin (see Sec 18.2.6, "Unconnected Pins")
  	PORTD |= (1 << PORTD7);	
  	PORTD |= (1 << PORTD6);
	
	//uint8_t cntr = 8; // declare counter variable 
  	//uint8_t storeState = 0;
  	uint8_t i = 0;
  	uint8_t n = 0;
  	//uint8_t button = 0;
	
	// Main code (runs repeatedly) goes here
	while(1) {
		
		
		switch(game) {
			case(GAME_OFF):
				while (  game != GAME_ON  ){
					PORTB |= (1 << PORTB1);		// set bit 1 to turn LED on
					_delay_ms(GAME_NOT_ON);		// kill some time
			
					PORTB &= ~(1 << PORTB1);		// set bit 1 to turn LED on
					_delay_ms(GAME_NOT_ON);
					
					if ((PIND & PIN_MASK1) == 0 || (PIND & PIN_MASK2) == 0 )
						game = GAME_ON;
				}
				break;
			case(GAME_ON):
					
					PORTB |= (1 << PORTB1);		// set bit 1 to turn LED on
					_delay_ms(3* LED_ON_TIME);		// kill some time
				
					PORTB &= ~(1 << PORTB1);		// set bit 1 to turn LED on
					_delay_ms(LED_PAUSE);	
					
					for (i = 0; i < 3; i++){
						PORTB |= (1 << PORTB1);		// set bit 1 to turn LED on
						_delay_ms(LED_ON_TIME);		// kill some time
				
						PORTB &= ~(1 << PORTB1);		// set bit 1 to turn LED on
						_delay_ms(LED_OFF_TIME);	
					}
					
					if ( (PIND & PIN_MASK1) == 0) {
				
						for (n = 0;n<4;n++ ){
						
							PORTB |= (1 << PORTB0);		// set bit 1 to turn LED on
							_delay_ms(LED_OFF_TIME);		// kill some time
						
							PORTB &= ~(1 << PORTB0);
							_delay_ms(LED_OFF_TIME);
						}
						game = GAME_OFF;
						
					}
					if ( (PIND & PIN_MASK2) == 0){
				
						for (n = 0;n<3;n++ ){
						
							PORTB |= (1 << PORTB2);		// set bit 1 to turn LED on
							_delay_ms(LED_OFF_TIME);		// kill some time
					
							PORTB &= ~(1 << PORTB2);
							_delay_ms(LED_OFF_TIME);
						}
						game = GAME_OFF;
					}
		
					_delay_ms(LED_ON_TIME);
				break;	
		}
	  			
	}
	  
	return 0;		/* never reached */
}