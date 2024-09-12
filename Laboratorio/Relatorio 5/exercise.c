/*
    Em uma esteira de transporte, foi instalado um sistema de verificação de
    peças posicionadas de forma errada. Elabore um firmware para controlar o
    sistema, seguindo os passos apresentados abaixo.

    a. Ao pressionar o botão LIGA (NA), a esteira entra em movimento (MOTOR = HIGH)
    b. Ao pressionar o botão DESLIGA (NF), a esteira para (MOTOR = LOW)
    c. Caso aconteça o amontoamento de peças (S1 = HIGH), a esteira deverá parar
    imediatamente e o ALARME deverá ser acionado (ALARM = HIGH);
    d. Para desligar o ALARME, as peças deverão estar desamontoadas (S1 = LOW) e
    o botão LIGA deve ser pressionado.
*/

# include <avr/io.h>

#define MOTOR1 (1<<PD7)
#define MOTOR2 (1 << PD6)
#define MOTOR3 (1 << PD2)
#define BUTTON_A (1 << PD5) 
#define BUTTON_B (1 << PD4) 
#define BUTTON_C (1 << PD3) 
 
int main() {

	DDRD |= MOTOR1 + MOTOR2 + MOTOR3;
	
	// Desliga os motores
	PORTD &= ~MOTOR1;
	PORTD &= ~MOTOR2;
	PORTD &= ~MOTOR3;
	
	while(1) {
		// Testando os botões
		short int botaoA;
		short int botaoB;
		short int botaoC;
		
		botaoA = PIND & BUTTON_A;
		botaoB = PIND & BUTTON_B;
		botaoC = PIND & BUTTON_C;

		if (botaoA == 0 && (botaoB != 0) && (botaoC != 0)) { 
			PORTD |= MOTOR1;
			PORTD &= ~MOTOR2;
			PORTD &= ~MOTOR3;
		}
		
		if (botaoA != 0 && (botaoB == 0) && (botaoC != 0)) { 
			PORTD |= MOTOR2;
			PORTD &= ~MOTOR1;
			PORTD &= ~MOTOR3;
		}
		
		if (botaoA != 0 && (botaoB != 0) && (botaoC == 0)){ 
			PORTD |= MOTOR3;
			PORTD &= ~MOTOR2;
			PORTD &= ~MOTOR1;
		}

		//Todos ligados problema - todos os leds (ok)
		if ((botaoA == 0) && (botaoB == 0) && (botaoC == 0)) {
			PORTD |= MOTOR2;
			PORTD |= MOTOR3;
			PORTD &= ~MOTOR1;
		}
		//cores led - cor diferente, vermelho (ok)
		else if (botaoA == 0 && botaoB == 0) {
			PORTD |= MOTOR1;
			PORTD |= MOTOR2;
			PORTD &= ~MOTOR3;
		}

		//cores led - cor amarela (ok)
			else if (botaoA == 0 && botaoC == 0) {
			PORTD |= MOTOR3;
			PORTD &= ~MOTOR1;
			PORTD &= ~MOTOR2;
		}
		//cores led - cor amarela (ok)
		if ( botaoB == 0 && botaoC == 0) {
			PORTD |= MOTOR3;
			PORTD &= ~MOTOR2;
			PORTD &= ~MOTOR1;
		}
	}
}