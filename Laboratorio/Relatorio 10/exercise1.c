/*
    Crie um programa que enquanto o botão esteja pressionado, o led verde é 
aceso com 50% de intensidade e assim que for solto o led deve apagar. Utilize 
o TIMER PWM para a elaboração do firmware.
*/

#include <avr/io.h>

#define BUTTON_PIN (1 << PD4)
#define LED (1 << PD6)

unsigned char button = 0;
unsigned char count = 0;

void timer0_init() {
    // Configuração do TIMER0
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, non-inverting mode
    TCCR0B = (1 << CS00); // No prescaler
    OCR0A = 0; // Inicializa o PWM com 0 de duty cycle
}

int main() {
    DDRD |= LED;
    PORTD |= BUTTON_PIN;

    timer0_init();

    // Configuração do botão
    button = PIND & BUTTON_PIN;

    while (1) {
        if (button == 0) {
            PORTD ^= LED;
            // Aumenta a luminosidade do LED em 50%
            count = 127;
        }
        else {
            PORTD ^= LED;
            // Reseta o contador
            count = 0;
        }
        OCR0A = count;
    }   
}
