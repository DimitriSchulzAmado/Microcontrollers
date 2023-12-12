#define FOSC 16000000U
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define botao (1 << PD4)
#define ledvermelho (1 << PD2)
#define ledverde (1 << PD3)
#define ledazul (1 << PD6)
char msg_tx[20];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 9;
unsigned int x = 0, valor = 0, y = 0;
// int brightness = 0;
void UART_Init(unsigned int ubrr);

void UART_Transmit(char *dados);

int main(void)
{
    sei();
    // Definindo pinos de entrada e saída
    DDRD |= ledverde | ledvermelho | ledazul;
    PORTD &= ~(ledverde | ledvermelho | ledazul);
    PORTD |= botao;
  
    /*
    // Definindo pinos do PWM
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
    TCCR0B |= (1 << CS02) | (1 << CS00); // prescaler de 1024
    OCR0A = 0; // duty cicle inicial
    */
  
    // Iniciando e tratando a UART
    UART_Init(MYUBRR);  
    UART_Transmit("Digite 'ola mundo':\n");
    x = 0;
    while (x == 0)
    {
        if ((msg_rx[0] == 'o') &&
            (msg_rx[1] == 'l') &&
            (msg_rx[2] == 'a') &&
            (msg_rx[3] == ' ') &&
            (msg_rx[4] == 'm') &&
            (msg_rx[5] == 'u') &&
            (msg_rx[6] == 'n') &&
            (msg_rx[7] == 'd') &&
            (msg_rx[8] == 'o'))
        {
            x = 1;
        }
    }
    pos_msg_rx = 0;
    UART_Transmit("Aperte o botao:\n");
 //   UART_Transmit("Digite o valor do DC:\n");
    UART_Transmit("Digite 8 para acender o LED verde e 9 para o vermelho\n");
    while (1)
    {
        /*
        OCR0A = brightness;
        // Ajustando o duty cycle (brightness)
        if (msg_rx[0] >= '0' && msg_rx[0] <= '9') {
            brightness = (msg_rx[0] - '0') * 10; // numero x10 pra representar os decimais
            if (msg_rx[1] >= '0' && msg_rx[1] <= '9') {
                brightness += (msg_rx[1] - '0'); // numero final
            }
        }
        // exemplo, o numero 53 = 50 + 3, então entra com 5, faz *10 pra dar 50 e depois soma 3.
        */
        if ((PIND & botao) != 0) // se o botão estiver apertado
        {
            UART_Transmit("Hello World!\n");
            y++;
            UART_Transmit("num vezes botao press: ");
            itoa(y, msg_tx, 10);
            UART_Transmit(msg_tx);
            UART_Transmit("\n");
            _delay_ms(500);
            UART_Transmit("Digite 'zerar' pra zerar o contador:\n");
        }
        if ((msg_rx[0] == 'z') &&
            (msg_rx[1] == 'e') &&
            (msg_rx[2] == 'r') &&
            (msg_rx[3] == 'a') &&
            (msg_rx[4] == 'r'))
        {
            y = 0;
            msg_rx[0] = '\0'; // limpa o buffer na posição 0
            UART_Transmit("Contador zerado.\n");
            pos_msg_rx = 0;
        }
        if ((msg_rx[0] == '9'))
        {
            PORTD |= ledvermelho;
            PORTD &= ~ledverde;
            msg_rx[0] = '\0'; // limpa o buffer do contador
            UART_Transmit("LED vermelho acesso e verde apagado \n");
            pos_msg_rx = 0;
        }
        if ((msg_rx[0] == '8'))
        {
            PORTD |= ledverde;
            PORTD &= ~ledvermelho;
            msg_rx[0] = '\0'; // limpa o buffer do contador
            UART_Transmit("LED verde acesso e vermelho apagado \n");
            pos_msg_rx = 0;
        }       
    }
}
ISR(USART_RX_vect)
{
    msg_rx[pos_msg_rx++] = UDR0;
    if (pos_msg_rx >= tamanho_msg_rx)
        pos_msg_rx = 0;
}
void UART_Transmit(char *dados)
{
    while (*dados != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *dados;
        dados++;
    }
}
void UART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}