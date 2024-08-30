/*
    Escreva um programa que configure o pino PD5 como entrada e ative o resistor
    de pull-up interno. Use a operação AND (&) para verificar o estado do pino.
*/

#include <avr/io.h>

#define BUTTON (1 << PD5)

int main(void) {
    DDRD &= ~BUTTON; // Define o pino como entrada
    PORTD |= BUTTON; // Ativa o resistor de pull-up

    while (1) {
        if (!(PIND & BUTTON != 0)) {
            // Pino está em nível alto
        } else {
            // Pino está em nível baixo
        }
    }
}
