/*
    Crie um programa em C que funcione como uma fechadura eletrônica. O programa
    deve possuir 4 botões de entrada, com resistor de pull-up interno. Os 4
    botões devem ser conectados aos pinos PB1, PB2, PB3 e PB4. O comando que
    libera a trava do sistema deve ser conectado ao pino PD3.

    O sistema só será liberado se os botões forem pressionados em uma 
    determinada ordem: PB2 -> PB3 -> PB4 -> PB1. Sendo que nenhum pino pode ser
    pressionado e solto, ou seja, ao final da sequência todos os pinos devem
    estar pressionados para validar o acionamento, que será indicado pelo nível
    lógico alto do pino PD3.
*/

#include <avr/io.h>

#define BUTTON1 (1 << PB1)
#define BUTTON2 (1 << PB2)
#define BUTTON3 (1 << PB3)
#define BUTTON4 (1 << PB4)
#define LOCK (1 << PD3)

int main(void) {
    // Define o pino como saída
    DDRD |= LOCK;

    // Habilita o resistor de pull-up
    PORTB |= BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4;

    while (1) {
        // Lê o valor de todos os pinos de entrada
        uint8_t input = PINB & (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4);

        // Verifica se a sequência foi pressionada
        if (input == (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4)) {
            PORTD |= LOCK; // Aciona a fechadura
        } else {
            PORTD &= ~LOCK; // Desliga a fechadura
        }
    }
}
