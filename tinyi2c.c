#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/iotnx5.h>
#include <avr/interrupt.h>
#include <stdint-gcc.h>


#include "adc.h"

  void setup()
  {
      PORTB |= 1 << PB1;              // Ensure serial output is high
      DDRB  |= (1<<PB1);              // Configure USI_DO as output.
      USICR = 0;                      // Start with USI disabled.
      sei();                          // Enable global interrupts
  }

 // float convertADC() {
//	return  U1 = (float) U1 * 0.0048828;
 // }



  int main(void){
	  setup();
	  initADC();
	  // test();
	  uartTx();

  }
