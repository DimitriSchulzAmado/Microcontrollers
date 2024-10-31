#define FOSC 16000000U // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

char msg_tx[20];             // vetor para transmissão
char msg_rx[32];             // vetor do receptor
int old_rx_hs[32];           // vetor para armazenar a mensagem antiga
int position_message_rx = 0; // auxiliar para a posição do receptor
int size_message_rx = 1;     //tamanho da mensagem que vai no receptor
int value = 0;               // valor a ser enviado

void UART_Transmit(char *data) {
    // Envia todos os caracteres do buffer dados ate chegar um final de linha
    while (*data != 0) {
        while (!(UCSR0A & (1 << UDRE0))); // Aguarda a transmissão acabar

        UDR0 = *data; // Escreve o caractere no registro de tranmissão
        data++; // Passa para o próximo caractere do buffer dados
    }
}

// Configuração do UART
void UART_Init(unsigned int ubrr) {
    // Configura o baud rate
    UBRR0H = (unsigned char)(ubrr >> 8); // para poder dividir o int de 16 bits em 8 bits 
    UBRR0L = (unsigned char)ubrr;
    // Habilita a recepcao, tranmissao e interrupcao na recepcao
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); 
    // Configura o formato da mensagem: 8 bits de dados e 1 bits de stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// funcao de leitura da serial -> RECEBE um valor
ISR(USART_RX_vect) {
    // Escreve o valor recebido pela UART na posição position_message_rx do buffer msg_rx
    msg_rx[position_message_rx++] = UDR0;
    if (position_message_rx == size_message_rx)
        position_message_rx = 0;
}

void clean_RX_buffer(void) {
    unsigned char dummy;
 
    // Enquanto houver dados no buffer
    while (UCSR0A & (1 << RXC0)) {
        dummy = UDR0;
    }

    pos_msg_rx = 0;
    for (int i = 0; i < 32; i++) {
        old_rx_hs[i] =  msg_rx[i];
        msg_rx[i] = 0;
    }
}

int main() {
    UART_Init(MYUBRR);

    for(;;){ 
        UART_Init(MYUBRR);
        UART_transmit (msg_tx);

        /*value*(msg[0]*48)*100
        *  *10 --- dezena 
        *  *1 --unidade /*
        */
    }
}