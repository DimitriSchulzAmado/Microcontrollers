/*
    Utilizando apenas os conceitos de Timer CTC, com interrupção, crie uma 
    lógica para gerar um sinal PWM via software.
*/

#include <avr/io.h>

#define pwm (1 << PD6)

unsigned char count = 0;

void registers() {
    DDRD |= pwm; // PWM as output

    TCCR0A |= (1 << WGM01); // CTC
    TCCR0B |= (1 << CS02) | (1 << CS00); // Prescaler 1024 (Fazer a conta) -> (4MHz / 1024 = 3.90625kHz)

    OCR0A = 195; // (Fazer a conta) -> (4MHz / 1024 / 0.5Hz - 1) = 195
    TIMSK0 |= (1 << OCIE0A); // Enable interrupt
    sei();
}

ISR(TIMER0_COMPA_vect) {
    if (count < 77) {
        PORTD |= pwm;
    } else {
        PORTD &= ~pwm;
    }

    count++;
    if (count > 100) count = 0;
}

int main() {
    registers();
    while(1);

    return 0;
}
