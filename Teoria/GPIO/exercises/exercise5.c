/*
    Modifique o programa anterior para usar a operação AND (&) com o complemento
    de 1 no bit correspondente ao pino desejado no registro PORT para inverter o estado do pino.
*/

#include <avr/io.h>

#define BUTTON (1 << PD5)

int main(void) {
    DDRD &= ~BUTTON; // Define o pino como entrada
    PORTD &= ~BUTTON; // Desativa o resistor de pull-up

    while (1) {
        if (!(PIND & BUTTON != 0)) {
            // Pino está em nível alto
        } else {
            // Pino está em nível baixo
        }
    }
}
