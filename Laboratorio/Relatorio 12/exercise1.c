/* 
    Crie um programa que quando o botão for pressionado (interrupção externa) envie o número de vezes que o botão foi pressionado (incluindo o atual) para o PC via UART. E, toda vez que o computador enviar o comando "zerar" devemos zerar a contagem.
*/

#include <stdio.h>
#include <stdint.h>

#define FOSC 16000000U
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1 
#define button (1 << PD3)

// Declarando variáveis globais
char msg_tx[20];               // vetor para transmissão
char msg_rx[32];               // vetor do receptor
int old_rx_hs[32];             // vetor para armazenar a mensagem antiga
int position_message_rx = 0;   // auxiliar para a posição do receptor
int size_message_rx = 5;       // tamanho da mensagem que vai no receptor
unsigned int x = 0, valor = 0; // auxiliares

// Prototipos das funcoes
void UART_Init(unsigned int ubrr);
void UART_Transmit(char *data);

// Função main
int main(void)
{
    PORTD |= button;

    sei();
    UART_Init(MYUBRR);
    UART_Transmit("Aperte o botao:\n");

    while (1) {
        if ((PIND & button) == 0) {
            x++;
            UART_Transmit("n° de vezes botao clicado: ");
            itoa(x, msg_tx, 10); // converte um numero inteiro para uma string
            // x = numero, msg_tx = guardar o numero em forma de string, 10 = base de conversão, no caso é decimal
            UART_Transmit(msg_tx);
            UART_Transmit("\n");
            _delay_ms(500); // Aguarda um tempo para evitar o bounce

            if ((msg_rx[0] == 'z') &&
                (msg_rx[1] == 'e') &&
                (msg_rx[2] == 'r') &&
                (msg_rx[3] == 'a') &&
                (msg_rx[4] == 'r')) {
                clean_RX_buffer();
                x = 0;
                position_message_rx = 0;
            }
        }
    }
}

// Interrupt do USART
ISR(USART_RX_vect) {
    // Escreve o valor recebido pela UART na posição position_message_rx do buffer msg_rx
    msg_rx[position_message_rx++] = UDR0;
    if (position_message_rx == size_message_rx)
        position_message_rx = 0;
}

// Transmissão UART
void UART_Transmit(char *data) {
    // Envia todos os caracteres do buffer dados ate chegar um final de linha
    while (*data != 0) {
        while (!(UCSR0A & (1 << UDRE0))); // Aguarda a transmissão acabar
        UDR0 = *data; // Escreve o caractere no registro de tranmissão
        data++; // Passa para o próximo caractere do buffer dados
    }
}

// Iniciando o UART
void UART_Init(unsigned int ubrr) {
    // Configura a baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Habilita a recepcao, tranmissao e interrupcao na recepcao
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Configura o formato da mensagem: 8 bits de dados e 1 bits de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void clean_RX_buffer(void) {
    unsigned char dummy;
 
    // Enquanto houver dados no buffer
    while (UCSR0A & (1 << RXC0)) {
        dummy = UDR0;
    }
 
    // Reseta o índice
    position_message_rx = 0;
 
    // Limpa todos os dados do buffer
    for (int i = 0; i < 32; i++) {
        old_rx_hs[i] =  msg_rx[i];
         msg_rx[i] = 0;
    }
}