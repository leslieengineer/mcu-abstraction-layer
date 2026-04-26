/**
 * @file button_interrupt_example_esp32.cpp
 * @brief Example of using GPIO interrupts with the abstraction layer on ESP32.
 * 
 * This example demonstrates:
 * - Configuring a GPIO as input with pull-up
 * - Setting up an interrupt callback
 * - Handling button presses via interrupt
 * - LED control in response to button events
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common_gpio.hpp"
#include "gpio_pin_esp32.hpp"

using namespace gpio;

// GPIO pin definitions
#define BUTTON_GPIO GPIO_NUM_0   // Boot button on most ESP32 boards
#define LED_GPIO    GPIO_NUM_2   // Built-in LED

// Shared state
static volatile int button_press_count = 0;
static volatile bool led_state = false;

/**
 * @brief ISR callback for button press.
 * 
 * This function is called from interrupt context, so it should be fast
 * and avoid blocking operations.
 * 
 * @param pin The pin number that triggered the interrupt
 * @param user_data User-provided context pointer
 */
static void IRAM_ATTR button_isr_handler(uint32_t pin, void* user_data) {
    // Toggle LED state flag
    led_state = !led_state;
    
    // Increment press counter
    button_press_count++;
    
    // In a real application, you might set a flag here and
    // handle the actual work in a task to keep the ISR fast
}

extern "C" void app_main(void) {
    printf("GPIO Abstraction Layer - Button Interrupt Example\n");
    
    // Create LED pin
    GpioPinESP32 led(LED_GPIO);
    auto led_config = PinConfigBuilder()
        .as_output(Level::LOW)
        .build();
    
    if (led.init(led_config) != ErrorCode::OK) {
        printf("Failed to initialize LED\n");
        return;
    }
    
    // Create button pin with interrupt
    GpioPinESP32 button(BUTTON_GPIO);
    auto button_config = PinConfigBuilder()
        .as_input(Pull::UP)
        .with_interrupt(
            InterruptTrigger::FALLING_EDGE,  // Trigger on button press (active low)
            button_isr_handler,
            nullptr  // No user data needed in this example
        )
        .build();
    
    if (button.init(button_config) != ErrorCode::OK) {
        printf("Failed to initialize button\n");
        return;
    }
    
    printf("Button and LED initialized\n");
    printf("Press the BOOT button to toggle the LED\n");
    
    int last_count = 0;
    
    // Main loop
    while (true) {
        // Update LED based on button state
        led.set_level(led_state ? Level::HIGH : Level::LOW);
        
        // Print status when count changes
        if (button_press_count != last_count) {
            printf("Button pressed %d times, LED is %s\n", 
                   button_press_count, 
                   led_state ? "ON" : "OFF");
            last_count = button_press_count;
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));  // Poll at 10Hz
    }
}
