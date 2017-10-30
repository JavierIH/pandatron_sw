#include "gpio.h"

void LED_Init(){
    GPIO_InitTypeDef GPIO_InitStruct;

    // GPIO Ports Clock Enable
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure GPIO pin : PB13 PB14 PB15
    GPIO_InitStruct.Pin = LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    // Configure GPIO pins : PC13
    GPIO_InitStruct.Pin = BUTTON;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
}

void set_led(uint16_t led_pin, GPIO_PinState state){
    if(led_pin == LED) {
        HAL_GPIO_WritePin(LED_PORT, led_pin, state);
    }
}

GPIO_PinState get_button(uint16_t button_pin){
    if(button_pin == BUTTON) {
        return HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON);
    }
}
