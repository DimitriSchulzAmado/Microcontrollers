#define LED_PIN PD7
#define BUTTON_ON_PIN PB0
#define BUTTON_OFF_PIN PB1
#define ADC_PIN PC4
#define BAUD_RATE 9600

volatile int temperature;
volatile float frequency;

ISR(ADC_vect) {
  // Conversão do valor lido do ADC para temperatura
  temperature = ADCW;
  float voltage = temperature * (5.0 / 1024.0);
  temperature = voltage / 0.01; // Considerando que o LM35 tem uma saída de 10mV/°C

  // Ajusta a frequência do LED de acordo com a temperatura
  if (temperature < 30) {
    frequency = 2; // 2 Hz
  } else if (temperature >= 30 && temperature <= 45) {
    frequency = 0.5; // 0.5 Hz
  } else if (temperature > 45) {
    frequency = 1; // 1 Hz
  }
  
  // Atualiza o registro OCR1A para a frequência correspondente
  OCR1A = (int)(F_CPU / (1024 * frequency) - 1);
  
  // Envia os dados pela UART
  char buffer[50];
  sprintf(buffer, "Temperatura: %d°C, Frequência: %.2fHz\n", temperature, frequency);
  uart_send_string(buffer);
}

// Função para enviar strings pela UART
void uart_send_string(char* str) {
  while (*str != '\0') {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = *str++;
  }
}

ISR(TIMER1_COMPA_vect) {
  // Troca o estado do LED
  PIND |= (1 << LED_PIN); // Isso irá inverter o estado do LED
}

ISR(INT0_vect) {
  // Botão LIGA/NA foi pressionado
  // Inicia a leitura do ADC
  ADCSRA |= (1 << ADSC) | (1 << ADIE);
}

ISR(INT1_vect) {
  // Botão DESLIGA/NF foi pressionado
  // Desliga o LED e interrompe a leitura do ADC
  PORTD &= ~(1 << LED_PIN);
  ADCSRA &= ~(1 << ADSC) & ~(1 << ADIE);
}

int main() {
  // Configuração dos pinos do LED e botões
  DDRD |= (1 << LED_PIN); // LED como saída
  PORTB |= (1 << BUTTON_ON_PIN) | (1 << BUTTON_OFF_PIN); // Habilita pull-up para os botões

  // Configuração ADC
  ADMUX |= (1 << REFS0) | (1 << MUX2); // Referência de AVcc e entrada ADC4
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Habilita ADC e prescaler de 128
  
  // Configuração do TIMER1 para interrupção
  TCCR1B |= (1 << WGM12); // Modo CTC
  TIMSK1 |= (1 << OCIE1A); // Habilita interrupção por comparação de match A

  // Configuração da interrupção externa
  EICRA |= (1 << ISC01); // Interrupção na borda de descida
  EIMSK |= (1 << INT0) | (1 << INT1); // Habilita interrupção externa para INT0 e INT1
  
  // Configuração UART
  uint16_t ubrr = F_CPU/16/BAUD_RATE-1;
  UBRR0H = (uint8_t)(ubrr>>8);
  UBRR0L = (uint8_t)ubrr;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // Configuração para 8 bits de dados, 1 stop bit

  sei(); // Habilita interrupções globais

  while (1) {}
}