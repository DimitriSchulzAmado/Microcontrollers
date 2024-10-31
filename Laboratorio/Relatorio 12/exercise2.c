/*
    Crie um programa para controlar dois leds, um vermelho e um verde. Toda vez que o computador enviar o comando "8" o verde liga e o vermelho desliga e toda vez que o "9" for enviado o vermelho liga e o verde desliga.
*/

#include <stdio.h>
#include <stdint.h>

#define FOSC 16000000U
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define red_led (1 << PD2)
#define green_led (1 << PD3)

char msg_tx[20];
char msg_rx[32];
int position_message_rx = 0;
int size_message_rx = 1;
unsigned int x = 0, valor = 0, y = 0;

void UART_Init(unsigned int ubrr);

void UART_Transmit(char *dados);

ISR(USART_RX_vect) {
    msg_rx[position_message_rx++] = UDR0;
    if (position_message_rx >= size_message_rx)
        position_message_rx = 0;
}

void UART_Transmit(char *dados) {
    while (*dados != 0) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *dados;
        dados++;
    }
}
void UART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int main(void) {
    // Definindo pinos de saída
    DDRD |= green_led | red_led;

    sei();
    UART_Init(MYUBRR);
    UART_Transmit("Digite 8 para acender o LED verde ou 9 para o vermelho\n");

    while (1) {
        if ((msg_rx[0] == '8')) {
            PORTD |= green_led;
            PORTD &= ~red_led;
            msg_rx[0] = '\0'; // limpa o buffer do contador
            UART_Transmit("LED verde acesso e LED vermelho apagado \n");
            position_message_rx = 0;
        }

        if ((msg_rx[0] == '9')) {
            PORTD |= red_led;
            PORTD &= ~green_led;
            msg_rx[0] = '\0'; // limpa o buffer do contador
            UART_Transmit("LED vermelho acesso e LED verde apagado \n");
            position_message_rx = 0;
        }
    }
}