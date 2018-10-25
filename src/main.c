#include "stm32f1xx_hal.h"
#include "msp.h"
#include "sysclock.h"
#include "error.h"
#include "uart.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h"
#include "infrared.h"


#define TRIM        140
#define KP          0.03 //0.015
#define KI          0
#define KD          10
#define BASE_SPEED  500 //330
#define MAX_SPEED   800

static void MX_ADC1_Init(void);
void setup(void);

int main(void) {
    setup();
    set_sense(MOTOR_R, FORWARD);
    set_sense(MOTOR_L, FORWARD);
    set_led(LED, LED_ON);

    int p = 0;
    int p_ref = 0;
    int i = 0;
    int d = 0;
    int speed_L = 0;
    int speed_R = 0;

    while (!get_button(BUTTON));
    set_led(LED, LED_OFF);
    HAL_Delay(5000);

    while (1){
        /*for (i=0; i<8; i++){
            sprintf(text_buffer,"IR[%d]: %d\t",i, _adc_buf[i]);
            send_uart(text_buffer);
        }
        sprintf(text_buffer,"Position: %d\n\r",position);
        send_uart(text_buffer);
        */

        p = -4*_adc_buf[0]
            -3*_adc_buf[1]
            -2*_adc_buf[2]
            -1*_adc_buf[3]
            +1*_adc_buf[4]
            +2*_adc_buf[5]
            +3*_adc_buf[6]
            +4*_adc_buf[7];
        p += TRIM;
        i = i+p;
        d = p-p_ref;
        p_ref = p;

        speed_L = BASE_SPEED + (p*KP + i*KI + d*KD);
        speed_R = BASE_SPEED - (p*KP + i*KI + d*KD);

        if (speed_L > MAX_SPEED) speed_L = MAX_SPEED;
        else if (speed_L < 0) speed_L = 0;
        if (speed_R > MAX_SPEED) speed_R = MAX_SPEED;
        else if (speed_R < 0) speed_R = 0;

        set_pwm(PWM_1, speed_L);
        set_pwm(PWM_2, speed_R);

    }
}

void setup(void){
    HAL_Init();
    SystemClock_Config();

    // Peripheral setup
    LED_Init();
    UART_Init();
    PWM_Init();
    MOTOR_Init();
    IR_Init();
}

void SysTick_Handler(void){ // function executed each 1ms
    static uint16_t task_tick = 0;

    switch (task_tick++) { // each case is executed each 20ms
        case 0:
            break;
        case 1:
            break;
        //case 2:
            //update turn pid
        //    break;
        case 20:
            task_tick = 0;
            break;
    }
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
