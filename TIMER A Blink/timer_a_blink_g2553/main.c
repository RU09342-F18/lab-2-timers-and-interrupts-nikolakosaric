#include <msp430.h> 

int main(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;              // Sets P1.0 in the output direction
    P1OUT &= ~BIT0;             // Clears P1.0 output register value

    P1DIR |= BIT6;              // Sets P1.6 in the output direction
    P1OUT &= ~BIT6;             // Clears P1.6 output register value

    BCSCTL3 = LFXT1S_2;         // Tells MC to use internal crystal

    // Clock for first LED
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
                                // Sets timer source to SMCLK, internal
                                // divider to internal clock to 8, sets
                                // clock to up mode, and clears the clock
    TA0CCR0 = 0x8000;           //
    TA0CCTL0 |= CCIE;           // Capture/compare interrupt enabled

    // Clock for second LED
    TA1CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
                                // Sets timer source to SMCLK, internal
                                // divider to internal clock to 8, sets
                                // clock to up mode, and clears the clock
    TA1CCR0 = 0x2000;           //
    TA1CCTL0 |= CCIE;            // Capture/compare interrupt enabled

    _BIS_SR(LPM0_bits + GIE);   // Sets the processor to low processor mode
                                // and enables global interrupts
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0_a_interrupt(void){
    P1OUT ^= BIT0;              // Toggles the state of P1.0
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer1_a_interrupt(void){
    P1OUT ^= BIT6;              // Toggles the state of P1.6
}
