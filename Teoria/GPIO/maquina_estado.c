#include <avr/io.h>

#define PORTAO_ABERTO 0
#define PORTAO_FECHADO 1
#define PORTAO_FECHANDO 2
#define PORTAO_ABRINDO 3

#define MF (1 << PD2) // 0b00000100 - Motor Fechando
#define MA (1 << PD3) // 0b00001000 - Motor Abrindo
#define SF (1 << PD4) // 0b00010000 - Sensor Fechado
#define SA (1 << PD5) // 0b00100000 - Sensor Aberto
#define CF (1 << PD6) // 0b01000000 - Controle Fechando
#define CA (1 << PD7) // 0b10000000 - Controle Abrindo

int main(void)
{
    DDRD |= MF | MA; // Define o pino como saída
    PORTD |= SF | SA | CF | CA; // Habilita o resistor de pull-up nos pinos

    char estado = 0;

    while (1) {
        switch (estado) {
            case PORTAO_ABERTO:
                PORTD |= SF | SA | CF | CA;
                if (!(PIND & CONTROLE == 0)) {
                    estado = PORTAO_FECHANDO;
                }
                break;
            case PORTAO_FECHADO:
                PORTD |= SF | SA | CF | CA;
                if (!(PIND & CONTROLE == 0)) {
                    estado = PORTAO_ABRINDO;
                }
                break;
            case PORTAO_FECHANDO:
                PORTD ^= MF; // Muda o estado do motor
                if (!(PIND & SENSOR == 0)) {
                    estado = PORTAO_FECHADO;
                }
                break;
            case PORTAO_ABRINDO:
                PORTD ^= MA; // Muda o estado do motor
                if (!PIND & SENSOR == 0) {
                    estado = PORTAO_ABERTO;
                }
                break;
            default:
                break;
        }
    }
}
