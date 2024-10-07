/*
    CRONOMETRO COM TIMER

    Desenvolva um programa que faça com que um LED Vermelho indique cada segundo
    (fique aceso por 100ms e apaga) e um LED Verde indique os minutos (acende 
    por 100ms e apaga). Use o temporizador
*/
#include <stdio.h>
#include <stdint.h>

#define LED1 (1 << PD7)
#define LED2 (1 << PB0)

unsigned int cont1 = 0;
unsigned int cont2 = 0;

int main() {
    // Configurando o LED como saída
    DDRD = LED1;
    DDRB = LED2;

    // Configurando temporizador - Modo Comparador
    TCCR0A = (1 << WGM01); // Configuração do modo de funcionamento para comparador

    // Configurando o Pre-scaler
    TCCR0B = (1 << CS01); // Pre-scaler de 8 (frequencia de 2MHz - periodo de 500ns em cada contagem)

    // Configurando o TOP
    OCR0A = 199; // 200 contagens de 500ns, o que gera interrupt a cada 100μs

    // Configurando opção de estouro
    TIMSK0 = (1 << OCIE0A); // Gerar interrupt no estouro do comparador OCR0A

    sei();

    while (1) {}
}

// o q acontece a cada 100μs ???
ISR(TIMER0_COMPA_vect) {
    cont1++;
    cont2++;

    // Quando passar 100ms
    if (cont1 == 10000) {
        PORTD ^= LED1;
    }

    else if (cont1 == 11000) {
        cont1 = 0;
        PORTD ^= LED1;
    }

    if (cont2 == 600000) {
        PORTB ^= LED2;
    }

    else if (cont2 == 601000) {
        cont2 = 0;
        PORTB ^= LED2;
    }
}