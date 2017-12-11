
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "adc.h"
#include "usiserialsend.h"

float U1;
float U2;
float current;


char string[16];



static float getU() {
	return (float) getADC(0) * 0.0048828;
}

static float getCurrent() {
	  return getADC(1);;
}

void uartTx()
  {
		usiserial_send_byte(!111);
		while (1)
		{
			ADCSRA |= (1 << ADSC);        	// start ADC measurement
			while (ADCSRA & (1 << ADSC) ); 	// wait till conversion complete

			itoa(getU(), string, 16);
			uint8_t len = sizeof(string)-1;

			usiserial_send_byte(!111);
			for (uint8_t i = 0; i<len; i++)
			{
				while (!usiserial_send_available())
              {
                  // Wait for last send to complete
              }
				  usiserial_send_byte(string[i]);
				  // usiserial_send_byte(13);
				  // usiserial_send_byte(10);
			}
            _delay_ms(500);
      }
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

void newLine() {
	usiserial_send_byte(13);
	usiserial_send_byte(10);
}
