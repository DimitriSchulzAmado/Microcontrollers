#define led_green (1 << PD2)
#define led_yellow (1 << PD3)
#define led_red (1 << PD4)

int main(void) {
    // Define os pinos como saída
    DDRD |= led_green | led_yellow | led_red;

    while (1) {
        // Define o estado atual do semáforo
        uint8_t currentState = 0;

        switch (currentState)
        {
            case 0:
                // Verde
                PORTD |= led_green;
                PORTD &= ~led_yellow;
                PORTD &= ~led_red;
                _delay_ms(12000);
                currentState++;
                break;
            case 1:
                // Amarelo
                PORTD &= ~led_green;
                PORTD |= led_yellow;
                PORTD &= ~led_red;
                _delay_ms(1000);
                currentState++;
                break;
            
            case 2:
                // Vermelho
                PORTD &= ~led_green;
                PORTD &= ~led_yellow;
                PORTD |= led_red;
                _delay_ms(15000);
                currentState = 0;
                break;
        }
    }
}
