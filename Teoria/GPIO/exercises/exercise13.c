/*
    Crie um programa que possua 5 pinos de entrada no Portal B, 1 LED1 como
    saída no Portal D, e um LED2 como saída no Portal C. O programa deve
    funcionar como um indentificador de padrões , onde o LED1 deve permanecer 
    aceso e o LED2 apagado, enquanto as entradas possuírem bits intercalados. Se
    todas as entradas estiverem com nivel lógico alto, o LED2 deve permanecer
    aceso, e o LED1 apagado.
*/

#include <avr/io.h>

#define BUTTON1 (1 << PB0)
#define BUTTON2 (1 << PB1) 
#define BUTTON3 (1 << PB2)
#define BUTTON4 (1 << PB3)
#define BUTTON2 (1 << PB4)
#define LED1 (1 << PD3)
#define LED2 (1 << PC3)

int main(void) {
    // Define os pinos como saída
    DDRD |= LED1; 
    DDRC |= LED2; 

    // Apaga ambos os LEDs
    PORTC &= ~(LED1 | LED2); 

    while (1) {
        // Lê o valor de todos os pinos de entrada
        uint8_t input = PINB & (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4 | BUTTON5)

        // Verifica se todas as entradas são HIGH
        if (input == (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4 | BUTTON5)) {
            PORTD &= ~LED1; // Apaga LED1
            PORTC |= LED2; // Acende LED2 
        }
        // Verifica se os bits estão intercalados
        else if ((input == 0b01010) || (input == 0b10101)) {
            PORTD |= LED1; // Acende LED1
            PORTC &= ~LED2; // Apaga LED2
        }
        // Caso contrário, apaga ambos os LEDs
        else {
            PORTD &= ~LED1; // Apaga LED1
            PORTC &= ~LED2; // Apaga LED2
        }
    }
}