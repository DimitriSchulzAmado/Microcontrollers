/*
    Modifique o programa anterior para que sejam utilizados dois LEDs em 2 pinos
    de saída, e os mesmos devem alternar a cada clique do botão no pino de 
    entrada.
*/

#include <avr/io.h>

#define BUTTON (1 << PD2)
#define LED1 (1 << PD3)
#define LED2 (1 << PD4)

int main(void) {
    DDRD |= LED1 | LED2; // Define os LEDs como saída

    while (1) {
        if (PIND & BUTTON != 0) {
            PORTD ^= LED1;
            PORTD ^= LED2;
        }
    }
}
