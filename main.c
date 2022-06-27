/*
 * File:   main.c
 * Author: Jamshed
 *
 * Created on June 5, 2022, 6:22 PM
 */

#include <xc.h>
#include "config.h"

#define _XTAL_FREQ     2e6

static char PORTB0_PRESSED;

void __interrupt() ISR( void ) {
    PORTDbits.RD0 = 1;
    PORTB0_PRESSED = 1;
    
    INTF = 0;
}

void main() {
    PORTB0_PRESSED = 0;
    
    OPTION_REG = 0;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INTE = 1;
    
    TRISBbits.TRISB0 = 1;
    TRISDbits.TRISD0 = 0;
     
    PORTDbits.RD0 = 0;
    
    while (1) {
        if ( PORTB0_PRESSED == 1 ) {
            __delay_ms(500);
            PORTDbits.RD0 = 0;
            
            PORTB0_PRESSED = 0;
        }
    }
}