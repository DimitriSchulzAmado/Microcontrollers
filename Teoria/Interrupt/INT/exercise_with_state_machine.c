/*
    *** COM MAQUINA DE ESTADOS ***

    Desenvolva em linguagem C um sistema de parada de emergência para uma 
    esteira industrial. A esteira é acionada intermitentemente a cada 5 segundos
    por meio de um motor comandado pelo microcontrolador. Deve ser projetado um
    botão de emergência que fornece um pulso que interrompe o motor da esteira e
    aciona um LED na saída, o qual deve permanecer aceso até que o sistema seja
    reiniciado.
*/

#include <avr/io.h>

#define motor (1 << PD3)
#define LED (1 << PD4)
#define emergenceButton (1 << PD5)

// Definição dos estados da máquina de estados
#define EMERGENCE 0
#define NORMAL 1

unsigned char interruptFlag = NORMAL;

int main(void) {

    DDRD |= motor | LED; // PD3 e PD4 como saída

    PORTD |= emergenceButton; // Habilita o pull-up interno do pino PD5
    PORTD &= ~LED;

    // Configura a interrupção para transição de descida
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Habilita a interrupção externa INT0
    EIMSK |= (1 << INT0);

    sei(); // Habilita interrupções globais

    while (1) {
        switch(interruptFlag) {
            case NORMAL:
                PORTD ^= motor;
                _delay_ms(5000);
                break;
            case EMERGENCE:
                while(1) {
                    PORTD &= ~motor;
                    PORTD |= LED;
                }
                break;
        }
    }
}

ISR(INT0_vect) {
    PORTD &= ~motor; // Inverte o estado do pino PD3
    PORTD ^= LED; // Inverte o estado do pino PD4
    interruptFlag = EMERGENCE;
}