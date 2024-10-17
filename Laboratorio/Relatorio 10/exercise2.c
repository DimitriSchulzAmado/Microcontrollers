/*
    Modifique o programa anterior para que cada vez que o botão for pressionado o 
led receba +10% de luminosidade. O led deve começar apagado e quando chegar a 
100%, após apertar o botão mais uma vez ele desliga. Utilize interrupção externa 
e o TIMER configurado com PWM.
*/

#include <avr/io.h>

#define BUTTON_PIN (1 << PD2)
#define LED (1 << PD6)

unsigned char bright = 0;
unsigned char button = 0;

void timer0_init() {
    // Configuração do TIMER0
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, non-inverting mode
    TCCR0B = (1 << CS00); // No prescaler
    OCR0A = 0; // Inicializa o PWM com 0 de duty cycle
}

void int0_init() {
    EICRA = (1 << ISC00); // Configuração da interrupção externa
    EIMSK = (1 << INT0); // Habilita a interrupção em INT0
}

ISR(INT0_vect) {
    // Aumenta a luminosidade do LED em 10%
    bright += 25;
    OCR0A = bright;

    if (bright > 255) {
        bright = 0;
    }
    _delay_ms(500);
}

int main() {
    DDRD |= LED;
    PORTD |= BUTTON_PIN;

    timer0_init();
    int0_init();

    sei();

    while (1) { }   
}

