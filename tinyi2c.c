#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/iotnx5.h>
#include <avr/interrupt.h>
#include <stdint-gcc.h>

#include "usiserialsend.h"
#include "adc.h"



char string[16];

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

  void helloWorld()
  {
	  // char message[] = "Test \r\n";
	  //  uint8_t len = sizeof(message)-1;
      usiserial_send_byte(!111);
      while (1)
      {
    	  ADCSRA |= (1 << ADSC);        	// start ADC measurement
    	  while (ADCSRA & (1 << ADSC) ); 	// wait till conversion complete

    	  //uint16_t adc = ADCW; 			//??? может тут ???

    	  //adc = ADCW;

    	  //U1 = (float) U1 * 0.0048828;
    	  //itoa(adc, string, 16);

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
          usiserial_send_byte(13);
                        usiserial_send_byte(10);
          _delay_ms(500);

    	  //usiserial_send_byte(ADCH);


/*
    	  ADCSRA |= (1 << ADSC);         // start ADC measurement
    	 	      while (ADCSRA & (1 << ADSC) ); // wait till conversion complete

    	 	      uint8_t len = sizeof(ADCH)-1;
    	 	      itoa(ADCH, message[len] ,10);
    	 	     usiserial_send_byte(!111);
    	 	               for (uint8_t i = 0; i<len; i++)
    	 	               {
    	 	                   while (!usiserial_send_available())
    	 	                   {
    	 	                       // Wait for last send to complete
    	 	                   }
    	 	                   usiserial_send_byte(message[i]);

    	 	               }
    	 	               _delay_ms(1000);
*/
      }
  }

  int main(void){
	  setup();
	  initADC();
	  // test();
	  helloWorld();

  }
