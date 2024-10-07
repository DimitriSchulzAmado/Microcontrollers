/*
    PISCA LED (LEDBLINKER) COM TIMER

    Crie um projeto que após a inicialização do ATMega328p, um LED Vermelho
    fique piscando com um tempo de 150ms. O projeto deve fazer uso do periférico
    TIMER e não pode conter linhas de delay.
*/
#include <stdio.h>
#include <stdint.h>

#define LED (1 << PD7)

unsigned int cont = 0;

int main() {
    // Configurando o LED como saída
    DDRD = LED;

    // Configurando temporizador - Modo Comparador
    TCCR0A = (1 << WGM01); // Configuração do modo de funcionamento para comparador

    // Configurando o Pre-scaler
    TCCR0B = (1 << CS01); // Pre-scaler de 8 (frequencia de 2MHz - periodo de 500ns em cada contagem)

    // Configurando o TOP
    OCR0A = 199; // 200 contagens de 500ns, o que gera interrupt a cada 100μs[micro]

    // Configurando opção de estouro
    TIMSK0 = (1 << OCIE0A); // Gerar interrupt no estouro do comparador OCR0A

    sei();
  
    while (1) {}

    return 0;
}

// o q acontece a cada 100μs ???
ISR(TIMER0_COMPA_vect) {
    cont++;

    // Quando passar 150ms
    if (cont == 1500) {
        cont = 0;
        PORTD ^= LED;
    }
}
