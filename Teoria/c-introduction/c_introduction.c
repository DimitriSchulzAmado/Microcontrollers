#include <stdio.h>
#include <stdint.h>

// question 1 ----------------------------------------------------------------
#define QUADRADO(x) (x * x)

int main()
{
    unsigned char number;
    scanf("%d", &number);
    printf("%d", QUADRADO(number));
}

// question 2 ----------------------------------------------------------------
#define MOTOR_1 0b00000001
#define MOTOR_2 0b00000010
#define MOTOR_3 0b00000100
#define MOTOR_4 0b00001000
#define MOTOR_5 0b00010000

void changeIo(uint8_t *currentState, uint8_t motorThatWillChange)
{
    *currentState = *currentState | motorThatWillChange;
}

int main()
{
    uint8_t currentMotorState;
    uint8_t motorsThatWillChange;

    // input values
    printf("Enter the motors state");
    scanf("%c", motorsThatWillChange);

    changeIo(&currentMotorState, motorsThatWillChange);
}