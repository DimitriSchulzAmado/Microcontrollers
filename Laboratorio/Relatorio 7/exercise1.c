/*
    Escreva um programa que use a interrupção externa INT0 como canal de 
    interrupção acionado pela transição de subida do sinal. O programa deverá
    piscar um LED no pino 5 (PD5) a cada 0,5s no super loop e a cada vez que
    acontecer um pedido de interrupção, um LED no pino 4 (PD4) acende por 1s e
    depois apaga.
*/

#include <avr/io.h>

#define LED (1 << PD5)
#define LED_INT (1 << PD4)

int main(void) {

    DDRD = LED | LED_INT; // Define as saídas

    // Configuração da interrupção externa INT0
    EICRA = (1 << ISC01) | (1 << ISC00);
    EIMSK = (1 << INT0);

    sei(); // Habilita interrupções globais

    while (1) {
        // Piscar o LED
        PORTD ^= LED;
        _delay_ms(500);
    }

    return 0;
}

ISR(INT0_vect) {
    // Acende o LED_INT por 1s quando o botão é pressionado	
    PORTD |= LED_INT;
    _delay_ms(1000);
    PORTD &= ~LED_INT;
}