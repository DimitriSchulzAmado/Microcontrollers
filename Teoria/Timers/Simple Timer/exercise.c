/*
    Utilizando os conceitos de temporizador, crie um programa para o ATMega328
    que controle o sistema de nivel de uma caixa d'água. A caixa possui dois
    sensores de nivel (ALTO e BAIXO) que indicam quando uma bomba precisa ser
    ligada. Quando em funcionamento, a bomba deve acionar/desacionar em uma 
    frequência de 0,5Hz até que o nivel esteja normalizado (sensor ALTO ativado).

    Os sensores devem funcionar por meio de interrupção externa e a bomba, quando
    ativada, controlada por meio de um temporizador.
    
    Considere f = 4MHz.
*/

#include <avr/io.h>

#define high_sensor (1 << PD2)
#define low_sensor (1 << PD3)
#define pump (1 << PD4)

unsigned char count = 0;

void registers() {
    DDRD |= pump; // Bomba como saída
    PORTD |= high_sensor | low_sensor; // Sensores como entrada com pull-up

    TCCR0A |= (1 << WGM01); // CTC
    TCCR0B |= (1 << CS02) | (1 << CS00); // Prescaler 1024 (Fazer a conta) -> (4MHz / 1024 = 3.90625kHz)

    OCR0A = 195; // (Fazer a conta) -> (4MHz / 1024 / 0.5Hz - 1) = 195
    TIMSK0 |= (1 << OCIE0A); // Enable interrupt
    sei();
}

ISR(TIMER0_COMPA_vect) {
    if (PIND & low_sensor) {
        PORTD |= pump;
    } else {
        PORTD &= ~pump;
    }
}

int main() {
    registers();
    while(1);

    return 0;
}