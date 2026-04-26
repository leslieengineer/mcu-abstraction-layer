#ifndef COMMON_GPIO_BUILDER_HPP
#define COMMON_GPIO_BUILDER_HPP

#include "common_gpio_types.hpp"

namespace gpio {

/**
 * @brief Builder class for fluent GPIO pin configuration.
 * 
 * This builder provides a type-safe, readable way to configure GPIO pins.
 * 
 * Example usage:
 * @code
 * auto config = PinConfigBuilder()
 *     .direction(Direction::OUTPUT)
 *     .output_mode(OutputMode::PUSH_PULL)
 *     .initial_level(Level::LOW)
 *     .build();
 * @endcode
 */
class PinConfigBuilder {
public:
    PinConfigBuilder() = default;

    PinConfigBuilder& direction(Direction dir) {
        config_.direction = dir;
        return *this;
    }

    PinConfigBuilder& pull(Pull p) {
        config_.pull = p;
        return *this;
    }

    PinConfigBuilder& output_mode(OutputMode mode) {
        config_.output_mode = mode;
        return *this;
    }

    PinConfigBuilder& interrupt_trigger(InterruptTrigger trigger) {
        config_.interrupt_trigger = trigger;
        return *this;
    }

    PinConfigBuilder& interrupt_callback(InterruptCallback callback, void* user_data = nullptr) {
        config_.interrupt_callback = callback;
        config_.interrupt_user_data = user_data;
        return *this;
    }

    PinConfigBuilder& initial_level(Level level) {
        config_.initial_level = level;
        return *this;
    }

    /**
     * @brief Convenience method: Configure as simple input with optional pull.
     */
    PinConfigBuilder& as_input(Pull p = Pull::NONE) {
        config_.direction = Direction::INPUT;
        config_.pull = p;
        return *this;
    }

    /**
     * @brief Convenience method: Configure as simple output with optional initial level.
     */
    PinConfigBuilder& as_output(Level initial = Level::LOW, OutputMode mode = OutputMode::PUSH_PULL) {
        config_.direction = Direction::OUTPUT;
        config_.initial_level = initial;
        config_.output_mode = mode;
        return *this;
    }

    /**
     * @brief Convenience method: Configure with interrupt.
     */
    PinConfigBuilder& with_interrupt(InterruptTrigger trigger, InterruptCallback callback, void* user_data = nullptr) {
        config_.interrupt_trigger = trigger;
        config_.interrupt_callback = callback;
        config_.interrupt_user_data = user_data;
        return *this;
    }

    /**
     * @brief Build and return the final configuration.
     */
    PinConfig build() const {
        return config_;
    }

private:
    PinConfig config_;
};

} // namespace gpio

#endif // COMMON_GPIO_BUILDER_HPP
