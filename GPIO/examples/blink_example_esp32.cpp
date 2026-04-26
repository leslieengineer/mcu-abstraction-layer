/**
 * @file blink_example_esp32.cpp
 * @brief Example of using the GPIO abstraction layer on ESP32 to blink an LED.
 * 
 * This example demonstrates:
 * - Creating a GPIO pin object
 * - Configuring it as an output using the builder pattern
 * - Toggling the pin in a loop
 * - RAII automatic cleanup
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common_gpio.hpp"
#include "gpio_pin_esp32.hpp"

using namespace gpio;

// LED pin (commonly GPIO2 on ESP32 dev boards)
#define LED_GPIO GPIO_NUM_2

extern "C" void app_main(void) {
    printf("GPIO Abstraction Layer - Blink Example\n");
    
    // Create a GPIO pin object for the LED
    GpioPinESP32 led(LED_GPIO);
    
    // Build configuration using the builder pattern
    auto config = PinConfigBuilder()
        .as_output(Level::LOW)  // Start with LED off
        .build();
    
    // Initialize the pin
    ErrorCode err = led.init(config);
    if (err != ErrorCode::OK) {
        printf("Failed to initialize LED pin: %d\n", static_cast<int>(err));
        return;
    }
    
    printf("LED pin initialized successfully on GPIO%d\n", led.get_pin_number());
    
    // Blink loop
    while (true) {
        printf("LED ON\n");
        led.set_level(Level::HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        printf("LED OFF\n");
        led.set_level(Level::LOW);
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        // Alternative: use toggle()
        // led.toggle();
        // vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    // Note: The led object will be automatically deinitialized
    // when it goes out of scope (RAII)
}
