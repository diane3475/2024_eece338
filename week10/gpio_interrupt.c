#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pigpio.h>
#include "helper.h"

#define PIN_BTN 14
#define PIN_LEDR 16
#define PIN_LEDG 20
#define PIN_LEDB 21
#define PIN_SERVO 12

#define SERVO_POS_MIN 1000
#define SERVO_POS_MAX 2000
#define LOOP_PERIOD_MS 1000

/* [P2] Write your global variables FROM here*/
volatile int btn_state;
volatile int btn_on;
volatile int led_color;
/* [P2] Write your global variables UP TO here*/

void myISR()
{
    btn_state = gpioReadDebounce(PIN_BTN);
    if(btn_state < 0) // If the input is noise, do nothing
        return;

    printf("Interrupt! Button state: %d\r\n", btn_state);

    /*** [P2] Write your code FROM here ***/
    if(btn_state==PI_LOW)
    {
     led_color = (led_color+2) %7 +1;
     gpioWrite(PIN_LEDR, (led_color & 0x01) && 1);
     gpioWrite(PIN_LEDG, (led_color & 0x02) && 1);
     gpioWrite(PIN_LEDB, (led_color & 0x04) && 1);
    }
    // If the button is pushed, change the color of the LED. Be
    // sure the LED color switches between five or more colors.

    /*** [P2] Write your code UP TO here ***/
}

int main()
{
    unsigned long t_start_ms, t_elapsed_ms;

    /* [P2] Write your variables FROM here, if needed */
    int servo_angle;
    int led_color =0;
    /* [P2] Write your variables UP TO here, if needed */

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

    // Interrupt settings
    gpioSetISRFunc(PIN_BTN, EITHER_EDGE, 0, myISR);
    
    // Infinite loop
    while(1) {
        t_start_ms = millis();

        /*** [P2] Delete all codes in between and write your code FROM here ***/
        gpioSetMode(PIN_SERVO, PI_OUTPUT);
        servo_angle = rand()%(SERVO_POS_MAX-SERVO_POS_MIN) + SERVO_POS_MIN;
        gpioServo(PIN_SERVO, servo_angle);
        /*** [P2] Write your code UP TO here ***/

        t_elapsed_ms = millis() - t_start_ms;
        sleep_ms(LOOP_PERIOD_MS - t_elapsed_ms);
    }

    return 1;
}
