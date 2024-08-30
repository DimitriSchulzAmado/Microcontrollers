/*
    Escreva um programa que configure o pino 2como saída e, em seguida, use a 
    operação de OR (|) para acender apenas o bit correspondente a esse pino no
    registro PORTD, mantendo os outros bits inalterados.
*/

#include <avr/io.h>

#define PIN (1 << PD2)

int main(void)
{
    DDRD |= PIN; // Define o pino como saída
    PORTD |= PIN; // Acende o bit correspondente ao pino 2

    while (1) { }
}