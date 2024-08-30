/*
    Utilizando a estrutura dos programas para ATMega328 crie um programa que
    alterne o estado de um pino de saída (de sua escolha) sempre que um botão em
    um pino de entrada (de sua escolha) for pressionado.
*/

#include <avr/io.h>

#define BUTTON (1 << PD2)
#define LED (1 << PD3)

int main(void) {
    DDRD |= LED; // Define o LED como saída

    while (1) {
        if (PIND & BUTTON != 0) {
            PORTD ^= LED;
        }
    }
}
