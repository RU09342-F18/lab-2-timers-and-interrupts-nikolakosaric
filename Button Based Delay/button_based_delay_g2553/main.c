#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

        P1SEL &= ~(BIT0 + BIT3);    //
        P1SEL2 &= ~(BIT0 + BIT3);   //

        P1DIR |= BIT0;              // Sets P1.0 in the output direction
        P1OUT &= ~BIT0;             // Clears P1.0 output register value

        P1DIR |= BIT6;              // Sets P1.6 in the output direction
        P1OUT &= ~BIT6;             // Clears P1.6 output register value

        P1DIR &= ~BIT3;             // Sets P1.3 in the input direction
        P1REN |= BIT3;              // P1.3 pullup/pulldown resistor enabled
        P1OUT |= BIT3;              // P1.3 pullup/pulldown configured as
                                    // pull up resistor

        P1IE |= BIT3;               // P1.3 interrupt enabled
        P1IES |= BIT3;              // P1.3 interrupt flag is set with a high
                                    // to low transition
        P1IFG &= ~BIT3;             // P1.3 interrupt flag is cleared

        BCSCTL3 = LFXT1S_2;         // Tells MC to use internal crystal

        // Clock for first LED
        TA0CTL = TASSEL_1 + ID_3 + MC_1 + TACLR;
                                    // Sets timer source to ACLK, internal
                                    // divider to internal clock to 8, sets
                                    // clock to up mode, and clears the clock
        CCR0 = 250;                 //
        TA0CCTL0 |= CCIE;           // Capture/compare interrupt enabled

        _BIS_SR(LPM0_bits + GIE);   // Sets the processor to low processor mode
                                    // and enables global interrupts
        return 0;
}

#pragma vector = PORT1_VECTOR;
__interrupt void button(void){
    if (P1IES & BIT3){               // Detects the falling edge of the button
        P1IES &= ~BIT3;             //
        TA0CTL = TASSEL_1 + ID_3 + MC_2 + TACLR;
                                    // Sets timer source to ACLK, internal
                                    // divider to internal clock to 8, sets
                                    // clock to continuous mode, and clears the
                                    // clock
        P1OUT |= BIT6;              // Turns on P1.6 to show when button is
                                    // pressed
    }
    else{
        P1OUT &= ~BIT6;             //
        TA0CTL = MC_0;              // Turns off the clock
        CCR0 = TA0R;                // Sets the capture compare register equal
                                    // to the clock register
        TACTL = TASSEL_1 + ID_3 + MC_1 + TACLR;
                                    // Sets timer source to ACLK, internal
                                    // divider to internal clock to 8, sets
                                    // clock to up mode, and clears the clock
        P1IES |= BIT3;              //
    }
    P1IFG &= ~BIT3;                 // Clear flags
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0_a_interrupt(void){
    P1OUT ^= BIT0;                  // Toggles the state of P1.0
    P1IFG &= ~BIT3;                 // Clear flags
}
