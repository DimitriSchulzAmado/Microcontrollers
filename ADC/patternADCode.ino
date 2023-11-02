#define  PINO PC3
#define  AMOSTRAS 30

unsigned int readAD = 0;
float tension = 0;

int main(){

    ADMUX = (1 << REFS0); // Configure the reference voltage's to 5V
    ADCSRA = (1 << ADEN) + (1 << ADPS2) + (1 << ADPS1) + (1 << ADPS0); // Habiliste PresCaler

    while (true){
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