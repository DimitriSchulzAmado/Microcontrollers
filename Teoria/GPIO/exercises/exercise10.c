/*
    Escreva um programa que configure os pinos PD0, PD1 e PD2 como entradas. Use
    a operação de AND (&) para verificar se todos esses pinos estão definidos
    como entradas no registro DDRD.
*/

#include <avr/io.h>

#define BUTTON1 (1 << PD0)
#define BUTTON2 (1 << PD1)
#define BUTTON3 (1 << PD2)

int main(void) {
    DDRD &= BUTTON1 & BUTTON2 & BUTTON3;

    while (1) { }
}
