#include <avr/io.h>

int main(void) {
    DDRB |= (1 << PB1); // PB0 como saída

    // Configura a interrupção para borda de descida
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00); 

    // Habilita a interrupção externa INT0
    EIMSK |= (1 << INT0); 

    sei(); // Habilita interrupções globais
}

ISR(INT0_vect) {
    PORTB ^= (1 << PB1); // Inverte o estado do pino PB1
}