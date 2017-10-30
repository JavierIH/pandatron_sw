#ifndef LED_H
#define LED_H

#include "stm32f1xx_hal.h"

#define LED                     GPIO_PIN_12
#define BUTTON                  GPIO_PIN_12

#define LED_PORT                GPIOB
#define BUTTON_PORT             GPIOA

#define LED_ON                  GPIO_PIN_SET
#define LED_OFF                 GPIO_PIN_RESET

void GPIO_Init();
void set_led(uint16_t led_pin, GPIO_PinState state);
GPIO_PinState get_button(uint16_t button_pin);


#endif // LED_H
