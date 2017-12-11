
#include <avr/io.h>

#include "adc.h"

float U1;
float U2;
float current;


float getU() {
	return (float) U1 * 0.0048828;;
}

float getCurrent() {
	  return current;
}

void initADC() {
	 /*
	    // 10-bit resolution
	    // set ADLAR to 0 to disable left-shifting the result (bits ADC9 + ADC8 are in ADC[H/L] and
	    // bits ADC7..ADC0 are in ADC[H/L])
	    // use uint16_t variable to read ADC (intead of ADCH or ADCL)
	    */

	    ADMUX =
	  	    (0 << ADLAR) |     // do not left shift result (for 10-bit values)
	              (0 << REFS2) |     // Sets ref. voltage to VCC, bit 2
	              (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
	              (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
	              (0 << MUX3)  |     // use ADC1 for input (PB2), MUX bit 3
	              (0 << MUX2)  |     // use ADC1 for input (PB2), MUX bit 2
	              (0 << MUX1)  |     // use ADC1 for input (PB2), MUX bit 1
	              (1 << MUX0);       // use ADC1 for input (PB2), MUX bit 0

	    ADCSRA =
	              (1 << ADEN)  |     // Enable ADC
	              (1 << ADPS2) |     // set prescaler to 128, bit 2
	              (1 << ADPS1) |     // set prescaler to 128, bit 1
	              (1 << ADPS0);      // set prescaler to 128, bit 0
}

float getADC(bool adcNum) {

	  if(!adcNum) {
		ADMUX =	(0 << MUX3)  |     // use ADC1 for input (PB2), MUX bit 3
				(0 << MUX2)  |     // use ADC1 for input (PB2), MUX bit 2
		        (0 << MUX1)  |     // use ADC1 for input (PB2), MUX bit 1
		        (1 << MUX0);       // use ADC1 for input (PB2), MUX bit 0
	  }
	  else {
		ADMUX = (0 << MUX3)  |     // use ADC3 for input (PB3), MUX bit 3
				(0 << MUX2)  |     // use ADC3 for input (PB3), MUX bit 2
				(1 << MUX1)  |     // use ADC3 for input (PB3), MUX bit 1
				(1 << MUX0);       // use ADC3 for input (PB3), MUX bit 0
	  }

	      	  ADCSRA |= (1 << ADSC);        	// start ADC measurement
	      	  while (ADCSRA & (1 << ADSC) ); 	// wait till conversion complete

	  return ADCW;
}
