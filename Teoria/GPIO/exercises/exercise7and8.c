/*
    Escreva um programa que configure o pino PD2 como entrada. Use a operação 
    de AND (&) para verificar se o bit correspondente a esse pino está setado no
    registro PIN e, caso positivo, acenda o LED no pino PD3 usando a operação de OR (|).

    8 - Modifique no programa anterior para apagar o LED no pino PD3 usando a operação de AND com NOT (&~) se o pino PD2 estiver setado.
*/

#include <avr/io.h>

#define BUTTON (1 << PD2)
#define LED (1 << PD3)

int main(void) {
    DDRD &= ~BUTTON; // Define o pino como entrada

    while (1) {
        if (!(PIND & BUTTON != 0)) {
            PORTD |= LED;
        } else {
            PORTD &= ~LED;
        }
    }
}
