#ifndef GPIO_PIN_STM32_HPP
#define GPIO_PIN_STM32_HPP

#include "common_gpio.hpp"

// Forward declarations for STM32 HAL types
// Users must include the appropriate STM32 HAL header before this file
struct GPIO_TypeDef;

namespace gpio {

/**
 * @brief STM32-specific GPIO pin implementation.
 * 
 * This class implements the IGpioPin interface for STM32 chips.
 * It wraps STM32 HAL GPIO driver and provides RAII semantics.
 * 
 * Note: This implementation requires STM32 HAL library.
 * Include the appropriate stm32xxxx_hal.h before including this header.
 * 
 * Usage example:
 * @code
 * #include "stm32l4xx_hal.h"
 * #include "gpio_pin_stm32.hpp"
 * 
 * using namespace gpio;
 * 
 * // LED on PA5
 * GpioPinSTM32 led(GPIOA, GPIO_PIN_5);
 * auto config = PinConfigBuilder().as_output(Level::LOW).build();
 * led.init(config);
 * led.set_level(Level::HIGH);  // Turn on LED
 * @endcode
 */
class GpioPinSTM32 : public IGpioPin {
public:
    /**
     * @brief Construct a GPIO pin object for the given STM32 port and pin.
     * 
     * @param port GPIO port (e.g., GPIOA, GPIOB).
     * @param pin GPIO pin mask (e.g., GPIO_PIN_0, GPIO_PIN_1).
     */
    GpioPinSTM32(GPIO_TypeDef* port, uint16_t pin);

    /**
     * @brief Destructor. Automatically deinitializes the pin (RAII).
     */
    ~GpioPinSTM32() override;

    // Disable copy and move to prevent resource double-free
    GpioPinSTM32(const GpioPinSTM32&) = delete;
    GpioPinSTM32& operator=(const GpioPinSTM32&) = delete;
    GpioPinSTM32(GpioPinSTM32&&) = delete;
    GpioPinSTM32& operator=(GpioPinSTM32&&) = delete;

    // IGpioPin interface implementation
    ErrorCode init(const PinConfig& config) override;
    ErrorCode deinit() override;
    ErrorCode set_level(Level level) override;
    ErrorCode get_level(Level& level) override;
    ErrorCode toggle() override;
    ErrorCode enable_interrupt() override;
    ErrorCode disable_interrupt() override;
    uint32_t get_pin_number() const override;
    bool is_initialized() const override;

private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
    PinConfig config_;
    bool initialized_;

    // Helper to get IRQn from pin
    int get_irq_number() const;
};

} // namespace gpio

#endif // GPIO_PIN_STM32_HPP
