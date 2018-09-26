#include <msp430.h> 

int main(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;              // Sets P1.0 in the output direction
    P1OUT &= ~BIT0;             // Clears P1.0 output register value

    P1DIR &= ~BIT1;             // Sets P1.1 in the input direction
    P1REN |= BIT1;              // P1.1 pullup/pulldown resistor enabled
    P1OUT |= BIT1;             // P1.1 pullup/pulldown configured as
                                // pull up resistor

    P1IE |= BIT1;               // P1.1 interrupt enabled
    P1IES |= BIT1;              // P1.1 interrupt flag is set with a high
                                // to low transition
    P1IFG &= ~BIT1;             // P1.1 interrupt flag is cleared

    _BIS_SR(LPM0_bits + GIE);   // Sets the processor to low processor mode
                                // and enables global interrupts
    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void button_interrupt(void){
    P1OUT ^= BIT0;              // Toggles the state of P1.0
    P1IFG &= ~BIT1;             // P1.3 interrupt flag is cleared
}

