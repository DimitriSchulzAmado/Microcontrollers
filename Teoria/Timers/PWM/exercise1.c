/*
    Configure um PWM Para o ATMega328 que controle a velocidade de uma ventoinha
    por meio de 3 modos diferentes:
        1. Modo Silencioso: 30% de operação;
        2. Modo Normal: 60% de operação;
        3. Modo Turbo: 100% de operação;
    Os modos devem ser alternados por meio do clique de um botão, conectado ao INT0.
*/

#include <avr/io.h>

#define fan (1 << PD6)
#define button (1 << PD2)

unsigned char mode = 0;

void registers() {
    DDRD |= fan; // Fan as output
    PORTD |= button; // Button as input with pull-up

    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, Clear OC0A on compare match
    TCCR0B |= (1 << CS00); // No prescaler

    OCR0A = 77; // 30% de operação
    sei();
}

ISR(INT0_vect) {
    mode++;
    if (mode > 2) mode = 0;

    switch (mode) {
        case 0:
            OCR0A = 77;
            break;
        case 1:
            OCR0A = 154;
            break;
        case 2:
            OCR0A = 255;
            break;
    }
}

int main() {
    registers();

    EICRA |= (1 << ISC00); // Any logical change
    EIMSK |= (1 << INT0); // Enable interrupt

    while(1);

    return 0;
}