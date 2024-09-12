/*
    Modifique o programa anterior para que, através da outra interrupção
    externa (INT1), acionada na transição de descida, cada vez que for acionada
    esta interrupção, ela deverá desabilitar/habilitar o portal INT0 a aceitar
    interrupções.
*/

#include <avr/io.h>

#define LED (1 << PD5)
#define LED_INT (1 << PD4)

int main(void) {

    DDRD = LED | LED_INT; // Define as saídas

    // Configuração das interrupções INT0 e INT1
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC10);
    EIMSK |= (1 << INT1);

    sei(); // Habilita interrupções globais

    while (1) {
        // Piscar o LED
        PORTD ^= LED;
        _delay_ms(500);
    }

    return 0;
}

ISR(INT1_vect) {
    // Desabilita a interrupção INT0
    EIMSK = (0 << INT0);  
}

ISR(INT0_vect) {
    // Acende o LED_INT por 1s quando o botão é pressionado	
    PORTD |= LED_INT;
    _delay_ms(1000);
    PORTD &= ~LED_INT;
}