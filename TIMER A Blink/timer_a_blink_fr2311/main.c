#include <msp430.h> 

int main(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;              // Sets P1.0 in the output direction
    P1OUT &= ~BIT0;             // Clears P1.0 output register value

    P2DIR |= BIT0;              // Sets P2.0 in the output direction
    P2OUT &= ~BIT0;             // Clears P2.0 output register value

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    //BCSCTL3 = LFXT1S_2;         // Tells MC to use internal crystal

    // Clock for first LED
    TB0CTL = TBSSEL_2 + ID_3 + MC_1 + TBCLR;
                                // Sets timer source to SMCLK, internal
                                // divider to internal clock to 8, sets
                                // clock to up mode, and clears the clock
    TB0CCR0 = 0x8000;           //
    TB0CCTL0 |= CCIE;           // Capture/compare interrupt enabled
    //PLZ
    // Clock for second LED
    TB1CTL = TBSSEL_2 + ID_3 + MC_1 + TBCLR;
                                // Sets timer source to SMCLK, internal
                                // divider to internal clock to 8, sets
                                // clock to up mode, and clears the clock
    TB1CCR0 = 0x2000;           //
    TB1CCTL0 |= CCIE;            // Capture/compare interrupt enabled

    _BIS_SR(LPM0_bits + GIE);   // Sets the processor to low processor mode
                                // and enables global interrupts
    return 0;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void timer0_a_interrupt(void){
    P1OUT ^= BIT0;              // Toggles the state of P1.0
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void timer1_a_interrupt(void){
    P2OUT ^= BIT0;              // Toggles the state of P1.6
}
