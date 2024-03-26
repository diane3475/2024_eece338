#include <stdio.h>
#include <time.h>
#include <pigpio.h>
#include "helper.h"

#define PIN_BTN 14
#define PIN_LEDR 16
#define PIN_LEDG 20
#define PIN_LEDB 21
#define PIN_SERVO 12

// NEVER change SERVO_POS_MIN and SERVO_POS_MAX.
// Changing the two values may break your servo motor.
#define SERVO_POS_MIN 1000
#define SERVO_POS_MAX 2000

#define LOOP_PERIOD_MS 1000

/* [P1] Write your function FROM here, if needed */
void switch_led_color(int led_state)
{
    switch(led_state) {
        case 1:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_LOW);
            break; 
        case 2:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_LOW);
            break;   
        case 3:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_LOW);
            break;
        case 4:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        case 5:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        case 6:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        case 7:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        default:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_LOW);
            break;
    }
}
/* [P1] Write your function UP TO here, if needed */

int main()
{
    unsigned long t_start_ms, t_elapsed_ms;

    /* [P1] Write your variables FROM here */
    int servo_angle;
    int led_state =0;
    int button =0;
    /* [P1] Write your variables UP TO here */

    srand((unsigned int)time(NULL));

    // GPIO settings
    if(gpioInitialise()<0) {
        printf("Cannot initialize GPIOs\r\n");
        return 1;
    }

    gpioSetMode(PIN_LEDR, PI_OUTPUT);
    gpioSetMode(PIN_LEDG, PI_OUTPUT);
    gpioSetMode(PIN_LEDB, PI_OUTPUT);
    gpioSetMode(PIN_BTN, PI_INPUT);

    gpioSetPullUpDown(PIN_BTN, PI_PUD_UP);
    gpioWrite(PIN_LEDR, PI_LOW);
    gpioWrite(PIN_LEDG, PI_LOW);
    gpioWrite(PIN_LEDB, PI_LOW);

    // Infinite loop
    while(1) {
        t_start_ms = millis();

        /* [P1] Write your codes FROM here */
            gpioSetMode(PIN_SERVO, PI_OUTPUT);
            servo_angle = rand()%(SERVO_POS_MAX-SERVO_POS_MIN) + SERVO_POS_MIN;
            gpioServo(PIN_SERVO, servo_angle);
            
        // Set the servo angle to a random position.
            button = gpioRead(PIN_BTN);
        // Read the button pin state
            if(button == PI_LOW)
            {
              led_state = (led_state + 2) % 7 + 1;
              switch_led_color(led_state);
            }
        // If the button is pushed, change the color of the LED. Be
        // sure the LED color switches between five or more colors.

        /* [P1] Write your codes UP TO here */

        t_elapsed_ms = millis() - t_start_ms;
        sleep_ms(LOOP_PERIOD_MS - t_elapsed_ms);
    }

    return 1;
}
