/*
    Modifique no programa anterior para apagar o LED no pino PD3 usando a
    operação de AND com NOT (&~) se o pino PD2 estiver setado.
*/

#include <avr/io.h>

#define BUTTON (1 << PD2)
#define LED (1 << PD3)

int main(void) {
    DDRD &= ~BUTTON; // Define o pino como entrada

    while (1) {
        if (PIND & BUTTON != 0) {
            PORTD |= LED;
        } else {
            PORTD &= ~LED;
        }
    }
}
