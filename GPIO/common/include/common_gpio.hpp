#ifndef COMMON_GPIO_HPP
#define COMMON_GPIO_HPP

/**
 * @file common_gpio.hpp
 * @brief Main header for the common GPIO abstraction layer.
 * 
 * This abstraction provides a portable, pin-centric API for GPIO operations
 * across ESP32, STM32, and other microcontroller families.
 * 
 * Design principles:
 * - Pin-centric: Each pin is represented by an object with its own state.
 * - RAII: Pins are automatically deinitialized when destroyed.
 * - Builder pattern: Fluent, type-safe configuration.
 * - Interface-based: Easy to mock and test.
 * - Clear error handling: All operations return ErrorCode.
 * 
 * Example usage (ESP32):
 * @code
 * #include "common_gpio.hpp"
 * #include "esp32/gpio_pin_esp32.hpp"
 * 
 * using namespace gpio;
 * 
 * // Create a pin object
 * GpioPinESP32 led_pin(GPIO_NUM_2);
 * 
 * // Configure using builder
 * auto config = PinConfigBuilder()
 *     .as_output(Level::LOW)
 *     .build();
 * 
 * // Initialize
 * if (led_pin.init(config) == ErrorCode::OK) {
 *     // Use the pin
 *     led_pin.set_level(Level::HIGH);
 * }
 * // Pin is automatically deinitialized when led_pin goes out of scope
 * @endcode
 */

#include "common_gpio_types.hpp"
#include "common_gpio_itf.hpp"
#include "common_gpio_builder.hpp"

#endif // COMMON_GPIO_HPP
