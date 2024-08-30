/*
    Crie um programa que configure os pinos PD4, PD5 e PD6 como saída. Use a
    operação de OR (|) para definir esses pinos como saídas de forma simultânea.
*/

#include <avr/io.h>

#define LED1 (1 << PD4)
#define LED2 (1 << PD5)
#define LED3 (1 << PD6)

int main(void) {
    DDRD |= LED1 | LED2 | LED3;

    while (1) { }
}