/*
    Escreva um programa que use a interrupção externa PCINT como canais de
    interrupção. O programa deverá piscar um LED no pino 5 (PD5) a cada 0,250s
    no super loop e a cada vez que acontecer um pedido de interrupção, um LED no
    pino 7 (PD7) acende por 1s quando o PCINT0 for acionado, outro LED no pino
    6 (PD6) acende por 0,5s quando o PCINT2 for acionado e outro LED no pino 15
    (PC1) acende por 2s quando o PCINT20 for acionado.
*/

#define LED0250 (1<<PD5)
#define LED1000 (1<<PD7)
#define LED0500 (1<<PD6)
#define LED2000 (1<<PB1)

#define BUTTON1000 (1<<PCINT0) // Botão que aciona o LED por 1s (PB0)
#define BUTTON0500 (1<<PCINT2) // Botão que aciona o LED por 0,5s (PB2)
#define BUTTON2000 (1<<PCINT20) // Botão que aciona o LED por 2s (PD4)
 
 
ISR(PCINT0_vect) {
    /* Pisca o LED por 1s */
    if ((PINB & BUTTON1000) == 0) {
        PORTD |= LED1000;
        _delay_ms(1000);
        PORTD &= ~LED1000;
    }

    /* Pisca o LED por 0,5s */
    if ((PINB & BUTTON0500) == 0) {
        PORTD |= LED0500;
        _delay_ms(500);
        PORTD &= ~LED0500;
    }
}
 
ISR(PCINT2_vect) {
    /* Pisca o LED por 2s */
    PORTB |= LED2000;
    _delay_ms(2000);
    PORTB &= ~LED2000;
}
 
int main(void) {
 
    // Define os pinos como saída
    DDRD |= LED0250 | LED1000 | LED0500;
    DDRB |= LED2000;

    // Pull-up nos pinos de interrupção
    PORTD |= LED0250 | LED1000 | LED0500;
    PORTB |= LED2000;
 
    // Habilitando portais de interrupção (B e D)
    PCICR |= (1<<PCIE0) | (1<<PCIE2);
 
    // Habilitando pinos de interrupção
    PCMSK0 |= BUTTON0500 | BUTTON1000;
    PCMSK2 |= BUTTON2000;
 
    sei(); // Habilita interrupções globais
 
    while (1) {
        PORTD ^= LED0250;
        _delay_ms(250);
    }
 
    return 0;
}
