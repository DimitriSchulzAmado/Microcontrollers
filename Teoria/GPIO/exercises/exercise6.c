/*
    Crie um programa que configure os pinos PD6 e PD7 como saída. Em seguida,
    use a operação de AND com NOT (&~) para apagar apenas o bit correspondente ao pino D6 do registro DDRD.
*/

#include <avr/io.h>

#define OUT1 (1 << PD6)
#define OUT2 (1 << PD7)

int main(void) {
    DDRD |= OUT1 | OUT2; // Define os pinos como saída

    DDRD &= ~OUT1; // Apaga o bit correspondente ao pino D6

    while (1) {
        // Não faz nada
    }
}
