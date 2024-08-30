/*
    Crie um programa para que o LED1 e LED2 sejam acionados alternadamente, com
    intervalo de 1s enquanto o BOTAO2 for precionado, e com intervalos de 100ms
    quando o BOTAO1 for pressionado.
*/ 

#include <avr/io.h>

#define BOTAO1 (1 << PD4) // com pull-up
#define BOTAO2 (1 << PD5) // com pull-up
#define LED1 (1 << PD6)
#define LED2 (1 << PD7)

int main(void) {
    DDRD |= LED1 | LED2; // Define PD7 como saída
    PORTD |= BOTAO1 | BOTAO2; // Habilitar PULL-UP no PD5
    PORTD &= ~(LED1 | LED2); // Desliga os LED's

    int botao1;
    int botao2;

    while(1){
        botao1 = PIND & BOTAO1; // Lê o estado do PD4
        botao2 = PIND & BOTAO2; // Lê o estado do PD5

        if (!(botao1 != 0)) {
            PORTD ^= LED2; // PD7 -> HIGH
            _delay_ms(100);
            PORTD ^= LED2; // PD7 -> LOW
            _delay_ms(100); 
            PORTD ^= LED1; // PD6 -> HIGH
            _delay_ms(100);
            PORTD ^= LED1; // PD6 -> LOW
            _delay_ms(100);
        }

        if (!(botao2 != 0)) { // Botão está pressionado?
            PORTD ^= LED2; // PD7 -> HIGH
            _delay_ms(1000);
            PORTD ^= LED2; // PD7 -> LOW
            _delay_ms(1000); 
            PORTD ^= LED1; // PD6 -> HIGH
            _delay_ms(1000);
            PORTD ^= LED1; // PD6 -> LOW	
            _delay_ms(1000);
        }
    }
}