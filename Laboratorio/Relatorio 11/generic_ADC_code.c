#include <stdio.h>
#include <stdint.h>

#define PINO PC3
#define AMOSTRAS 30

unsigned int readAD = 0;
float tension = 0;

void ADC_init(void) {
    // Configurando Vref para VCC = 5V
    ADMUX = (1 << REFS0);
    /*
        ADC ativado e preescaler de 128
        16MHz / 128 = 125kHz
        ADEN = ADC Enable, ativa o ADC
        ADPSx = ADC Prescaler Select Bits
        1 1 1 = clock / 128
    */
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int ADC_read(u8 ch) {
    char i;
    int ADC_temp = 0; // ADC temporário, para manipular leitura
    int ADC_read = 0; // ADC_read
    ch &= 0x07;       // 0b00000111
    // Zerar os 3 primeiros bits e manter o resto
    ADMUX = (ADMUX & 0xF8) | ch; // 0b11111000
    // ADSC (ADC Start Conversion)
    ADCSRA |= (1 << ADSC); // Faça uma conversão
    // ADIF (ADC Interrupt Flag) é setada quando o ADC pede interrupção
    // e resetada quando o vetor de interrupção
    // é tratado.
    while (!(ADCSRA & (1 << ADIF))); // Aguarde a conversão do sinal
    for (i = 0; i < 8; i++) { // Fazendo a conversão 8 vezes para maior precisão
        ADCSRA |= (1 << ADSC); // Faça uma conversão
        while (!(ADCSRA & (1 << ADIF))); // Aguarde a conversão do sinal
        ADC_temp = ADCL;         // lê o registro ADCL
        ADC_temp += (ADCH << 8); // lê o registro ADCH
        ADC_read += ADC_temp;    // Acumula o resultado (8 amostras) para média
    }
    ADC_read = (ADC_read / 8); // média das 8 amostras ( >> 3 é o mesmo que /8)
    return ADC_read;
}

int main()
{
    Serial.begin(9600);
    ADC_init(); // Inicializa ADC

    while (1) {
        // Configure the reading PINO
        ADMUX = (ADMUX & 0xF8) + PINO; // Hold on the first 5 left pins and just change 3 da direita

        // Start conversion
        ADCSRA |= (1 << ADSC);

        // Wait finished conversion
        while ((ADCSRA & (1 << ADSC)) == (1 << ADSC));

        readAD = ADC; // Read ADC values and storage (0 -> 1023 present a 0 - 5v signal)

        tension = (readAD * 5.0) / 1023.0; // Convert the ADC reading to the voltage
    }
}
