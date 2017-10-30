#include "stm32f1xx_hal.h"
#include "msp.h"
#include "sysclock.h"
#include "error.h"
#include "uart.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h"
#include "infrared.h"

#define TRIM 5

static void MX_ADC1_Init(void);
void setup(void);
//void SysTick_Handler(void);

int main(void) {
    setup();
    char text_buffer[200];
    sprintf(text_buffer,"running...\n\r");
    int i=0;
    int up=1;
    int mtime=30;
    set_sense(MOTOR_R, FORWARD);
    set_sense(MOTOR_L, FORWARD);



    int32_t delta = 0;
    uint16_t before = 0;
    uint16_t after = 0;

    //while(get_button(BUTTON_START));
    int x=0;
    int speed=0;
    while (!get_button(BUTTON));
        while (1){

        set_led(LED, get_button(BUTTON));
        int i;
        int position =  -6*_adc_buf[0]
                        -4*_adc_buf[1]
                        -3*_adc_buf[2]
                        -1*_adc_buf[3]
                        +1*_adc_buf[4]
                        +2*_adc_buf[5]
                        +3*_adc_buf[6]
                        +6*_adc_buf[7];
        position += 140;
        position /=250;
        sprintf(text_buffer,"Position: %d\n\r",position);
        send_uart(text_buffer);
        /*for (i=0; i<8; i++){
            sprintf(text_buffer,"IR[%d]: %d\t",i, _adc_buf[i]);
            send_uart(text_buffer);
        }*/
        sprintf(text_buffer,"\n\r");
        send_uart(text_buffer);
        set_pwm(PWM_1, 250+position+TRIM);
        set_pwm(PWM_2, 250-position-TRIM);
        /*speed +=10;
        if(speed == 1000){
            speed = 0;
            HAL_Delay(5000);
            //set_pwm(PWM_1, speed);
            //set_pwm(PWM_2, speed);
            HAL_Delay(10000);
        }*/
        HAL_Delay(x);
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
