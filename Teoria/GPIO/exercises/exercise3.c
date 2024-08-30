/*
    Crie um programa que configure os pinos PD3 e PB4 como saídas. Em seguida,
    use a operação XOR (^) para inverter o estado dos pinos simultaneamente.
*/

#include <avr/io.h>

#define PIN1 (1 << PD3)
#define PIN2 (1 << PB4)

int main(void)
{
    DDRD |= PIN1 | PIN2; // Define os pinos como saída

    while (1) {
        // Inverte o estado dos pinos
        PORTD ^= PIN1;
        PORTB ^= PIN2;
    }
}
