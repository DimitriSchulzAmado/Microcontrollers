/*
    Modifique o programa anterior para apagar o bit correspondente ao pino PD2
    usando a operação de AND (&) com o complemento de 1 (~) no bit desejado.
*/

#include <avr/io.h>

#define PIN (1 << PD2)

int main(void)
{
    DDRD |= PIN; // Define o pino como saída
    PORTD |= PIN; // Acende o bit correspondente ao pino 2
    PORTD &= ~PIN; // Apaga o bit correspondente ao pino 2

    while (1) { }
}