#define OP_NORMAL 0
#define EMERGENCY_STOP 1

#define BELT (1<<PD6) // MOTOR
#define LED (1<<PB0)
#define BUTTON (1<<PD2)
#define BELT_INTERVAL 5000

//Global state variable
unsigned char state = OP_NORMAL;

int main () {
    DDRB |= LED;
    DDRD |= BELT;
    PORTB &= ~ LED
    PORTD &= ~ BELT;
	
    // Habilita interrupção no Portal D no pino 2
    PCICR |= (1<<PCIE2);
    PCMSK2 |= BUTTON;
  
    // Habilita interrupções globais
    sei();
    
    while(1) {
        switch(state) {
            case OP_NORMAL:
                PORTD ^= BELT;
                _delay_ms(BELT_INTERVAL);
                break;
            
            case EMERGENCY_STOP:
                PORTB |= LED;
                PORTD |= BELT;
                break;
        }
    }
}

ISR(PCINT2_vect) {
    PORTB |= LED;
    PORTD |= BELT;
    state = EMERGENCY_STOP;
}
