/*
    Em uma esteira de transporte, foi instalado um sistema de verificação de
    peças posicionadas de forma errada. Elabore um firmware para controlar o
    sistema seguindo os passos abaixo:
    a. Ao pressionar o botão LIGA (NA) a esteira entra em movimento (MOTOR = HIGH);
    b. Ao pressionar o botão DESLIGA (NF) a esteira para (MOTOR = LOW);
    c. Caso aconteça o amontoamento de peças (S1 = HIGH), a esteira para e o
    alarme deverá ser ligado (ALARM = HIGH);
    d. Para desligar o ALARME, as peças deverão estar desamontoadas (S1 = LOW)
    e o botão DESLIGA deve ser pressionado;
*/

# include <avr/io.h>

#define MOTOR (1 << PD5)
#define ALARM (1 << PD6)
#define BTN_ (1 << PD2)
#define BTN_NF (1 << PD3)
#define S1 (1 << PD4)

int main(void) {
    // Configuração dos pinos de saída
    DDRD |= MOTOR | ALARM;

    // Verifica o estado dos botões e sensor
    unsigned char btnLiga = PIND & BTN_NA;
    unsigned char btnDesliga = PIND & BTN_NF;
    unsigned char sensor = PIND & S1;

    while (1) {
        // Botão LIGA acionado -> esteira liga
        if (!(btnLiga == 0)) {
            PORTD |= MOTOR;
        }

        // Botão DESLIGA ativado -> esteira desliga
        if (!(btnDesliga == 0)) {
            PORTD &= ~MOTOR;
        }

        // Caso aconteça o amontoamento de peças, a esteira para e o alarme é ligado
        if (!(sensor == 0)) {
            PORTD &= ~MOTOR;
            PORTD |= ALARM;
        }

        // Para desligar o ALARME, as peças deverão estar desamontoadas e o botão DESLIGA deve ser pressionado
        if (!(sensor == 0) && !(btnLiga == 0)) {
            PORTD &= ~ALARM;
            PORTD |= MOTOR;
        }
    }
}