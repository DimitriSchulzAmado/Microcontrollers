#include <avr/io.h>

#define FOSC 16000000U // Define a frequência do oscilador do microcontrolador (16 MHz para Arduino Uno)
#define BAUD 9600 // Define a taxa de transmissão da UART (9600 baud)
#define MYUBRR ((FOSC / 16 / BAUD) - 1) // Calcula o valor do registrador UBRR (USART Baud Rate Register)

// Limites de luz e som alertas
#define LIGHT_THRESHOLD 300  // min luz para acionar alerta
#define SOUND_THRESHOLD 500  // máx som para acionar alerta

// LEDs de alerta
#define LED_LIGHT_ALERT (1 << PB1)  // LED luz
#define LED_SOUND_ALERT (1 << PB2)  // LED som

// Buffers para mensagens UART
char msg_tx[20];              // Buffer para armazenar mensagens antes de enviar pela UART
volatile int light_level = 0; // Nível de luz lido pelo LDR
volatile int sound_level = 0; // Nível de som lido pelo sensor

// Inicializa a comunicação UART
void UART_Init(unsigned int ubrr) {
    // Configura os registradores para ajustar a taxa de transmissão
    UBRR0H = (unsigned char)(ubrr >> 8); // Parte alta do UBRR
    UBRR0L = (unsigned char)ubrr;       // Parte baixa do UBRR
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Habilita transmissão e recepção UART
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configura formato de quadro: 8 bits de dados, 1 bit de parada
}

// Envia uma string pela UART
void UART_Transmit(const char *dados) {
    // Envia cada caractere até encontrar o caractere nulo ('\0')
    while (*dados != 0) {
        while (!(UCSR0A & (1 << UDRE0))); // Aguarda até o registrador estar disponível
        UDR0 = *dados;                   // Envia o caractere atual
        dados++;                         // Avança para o próximo caractere
    }
}

// Inicializa o ADC para leitura dos sensores
void ADC_Init() {
    ADMUX = (1 << REFS0); // Ref de tensão AVcc (5V)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Habilita o ADC com prescaler de 128
}

// Lê o valor de um canal ADC
uint16_t ADC_Read(uint8_t ch) {
    ADMUX = (ADMUX & 0xF8) | (ch & 0x07); // Seleciona o canal
    _delay_us(5);                         // Espera estabilização do canal
    ADCSRA |= (1 << ADSC);                // Inicia a conversão
    while (ADCSRA & (1 << ADSC));         // Aguarda término da conversão
    return ADC;                           // Retorna o valor lido
}

// Configura o Timer1 para gerar interrupções a cada 1s
void Timer_Init() {
    TCCR1B |= (1 << WGM12) | (1 << CS12); // Modo CTC, prescaler 256
    OCR1A = 62500;                        // Valor de comparação para 1s (16 MHz / 256 / 1 Hz)
    TIMSK1 |= (1 << OCIE1A);              // Habilita interrupção ao atingir OCR1A
}


// Interrupção executada a cada 1s
ISR(TIMER1_COMPA_vect) {
    // Lê os valores dos sensores de luz e som
    light_level = ADC_Read(0); // Lê nível de luz no canal 0
    sound_level = ADC_Read(1); // Lê nível de som no canal 1

    // Envia os valores lidos pela UART
    UART_Transmit("Luz: ");
    itoa(light_level, msg_tx, 10); // Converte para String
    UART_Transmit(msg_tx);         // Envia valor
    UART_Transmit(" | Som: ");
    itoa(sound_level, msg_tx, 10); // Converte para string
    UART_Transmit(msg_tx);         // Envia valor
    UART_Transmit("\n");

    // Verifica se a luz está abaixo do limite
    if (light_level < LIGHT_THRESHOLD) {
        PORTB |= LED_LIGHT_ALERT;
        UART_Transmit("Alerta: Luz baixa!\n");
    } else {
        PORTB &= ~LED_LIGHT_ALERT;
    }

    // Verifica se o som está acima do limite
    if (sound_level > SOUND_THRESHOLD) {
        PORTB |= LED_SOUND_ALERT;
        UART_Transmit("Alerta: Som alto!\n");
    } else {
        PORTB &= ~LED_SOUND_ALERT;
    }
}


int main() {
    DDRB |= LED_LIGHT_ALERT | LED_SOUND_ALERT;
    
    // Configuração inicial
    UART_Init(MYUBRR); // Inicializa UART com o baud rate definido
    ADC_Init();
    Timer_Init();


    sei();

    for (;;) { }
}
