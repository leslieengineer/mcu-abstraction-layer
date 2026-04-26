/**
 * @file blink_example_stm32.cpp
 * @brief Example of using the GPIO abstraction layer on STM32 to blink an LED.
 * 
 * This example demonstrates:
 * - Creating a GPIO pin object for STM32
 * - Configuring it as an output
 * - Toggling the pin in a loop
 * - RAII automatic cleanup
 * 
 * Note: This example assumes you have already set up:
 * - HAL initialization
 * - System clock configuration  
 * - GPIO port clock enable
 */

#include "stm32l4xx_hal.h"  // Or appropriate HAL for your STM32 family
#include "common_gpio.hpp"
#include "gpio_pin_stm32.hpp"

using namespace gpio;

// LED pin (PA5 is commonly used on Nucleo boards)
#define LED_PORT GPIOA
#define LED_PIN  GPIO_PIN_5

// Function prototypes
void SystemClock_Config(void);

int main(void) {
    // HAL initialization
    HAL_Init();
    SystemClock_Config();
    
    // Enable GPIO clock
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // Create a GPIO pin object for the LED
    GpioPinSTM32 led(LED_PORT, LED_PIN);
    
    // Build configuration using the builder pattern
    auto config = PinConfigBuilder()
        .as_output(Level::LOW)  // Start with LED off
        .build();
    
    // Initialize the pin
    ErrorCode err = led.init(config);
    if (err != ErrorCode::OK) {
        // Error: halt
        while (1) {}
    }
    
    // Blink loop
    while (1) {
        led.toggle();
        HAL_Delay(1000);  // 1 second delay
    }
    
    // Note: In an embedded system, we typically never reach this point,
    // but if we did, the led object would be automatically deinitialized
}

/**
 * @brief System Clock Configuration
 * 
 * Configure the system clock for your specific board.
 * This is a placeholder - replace with your actual clock config.
 */
void SystemClock_Config(void) {
    // TODO: Add your clock configuration here
    // This depends on your specific STM32 chip and board
}
