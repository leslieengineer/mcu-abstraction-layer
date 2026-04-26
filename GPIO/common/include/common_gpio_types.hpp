#ifndef COMMON_GPIO_TYPES_HPP
#define COMMON_GPIO_TYPES_HPP

#include <cstdint>

namespace gpio {

/**
 * @brief Error codes returned by GPIO operations.
 */
enum class ErrorCode : int8_t {
    OK = 0,
    INVALID_PIN = -1,
    INVALID_CONFIG = -2,
    ALREADY_INITIALIZED = -3,
    NOT_INITIALIZED = -4,
    HARDWARE_ERROR = -5,
    UNSUPPORTED_OPERATION = -6
};

/**
 * @brief GPIO pin direction.
 */
enum class Direction {
    INPUT,
    OUTPUT,
    INPUT_OUTPUT  // Open-drain or bidirectional
};

/**
 * @brief GPIO pin level (high/low).
 */
enum class Level : uint8_t {
    LOW = 0,
    HIGH = 1
};

/**
 * @brief Pull-up/pull-down resistor configuration.
 */
enum class Pull {
    NONE,
    UP,
    DOWN,
    UP_DOWN  // Both (some MCUs support this)
};

/**
 * @brief Output drive mode.
 */
enum class OutputMode {
    PUSH_PULL,
    OPEN_DRAIN
};

/**
 * @brief Interrupt trigger type.
 */
enum class InterruptTrigger {
    NONE,
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES,
    LOW_LEVEL,
    HIGH_LEVEL
};

/**
 * @brief GPIO interrupt callback function type.
 * @param pin The pin number that triggered the interrupt.
 * @param user_data User-provided context pointer.
 */
using InterruptCallback = void (*)(uint32_t pin, void* user_data);

/**
 * @brief Complete GPIO pin configuration.
 * 
 * This struct represents all possible GPIO configuration options.
 * Not all options may be supported on all platforms.
 */
struct PinConfig {
    Direction direction = Direction::INPUT;
    Pull pull = Pull::NONE;
    OutputMode output_mode = OutputMode::PUSH_PULL;
    InterruptTrigger interrupt_trigger = InterruptTrigger::NONE;
    InterruptCallback interrupt_callback = nullptr;
    void* interrupt_user_data = nullptr;
    Level initial_level = Level::LOW;  // Only for OUTPUT
};

} // namespace gpio

#endif // COMMON_GPIO_TYPES_HPP
