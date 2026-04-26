#ifndef GPIO_PIN_ESP32_HPP
#define GPIO_PIN_ESP32_HPP

#include "common_gpio.hpp"
#include "driver/gpio.h"

namespace gpio {

/**
 * @brief ESP32-specific GPIO pin implementation.
 * 
 * This class implements the IGpioPin interface for ESP32 chips.
 * It wraps ESP-IDF GPIO driver and provides RAII semantics.
 * 
 * Usage example:
 * @code
 * #include "gpio_pin_esp32.hpp"
 * 
 * using namespace gpio;
 * 
 * // LED on GPIO2
 * GpioPinESP32 led(GPIO_NUM_2);
 * auto config = PinConfigBuilder().as_output(Level::LOW).build();
 * led.init(config);
 * led.set_level(Level::HIGH);  // Turn on LED
 * // LED automatically deinitialized when led goes out of scope
 * @endcode
 */
class GpioPinESP32 : public IGpioPin {
public:
    /**
     * @brief Construct a GPIO pin object for the given ESP32 pin number.
     * 
     * @param pin_num ESP32 GPIO number (e.g., GPIO_NUM_2).
     */
    explicit GpioPinESP32(gpio_num_t pin_num);

    /**
     * @brief Destructor. Automatically deinitializes the pin (RAII).
     */
    ~GpioPinESP32() override;

    // Disable copy and move to prevent resource double-free
    GpioPinESP32(const GpioPinESP32&) = delete;
    GpioPinESP32& operator=(const GpioPinESP32&) = delete;
    GpioPinESP32(GpioPinESP32&&) = delete;
    GpioPinESP32& operator=(GpioPinESP32&&) = delete;

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

    // Make config_ and pin_num_ accessible to ISR dispatcher
    friend void IRAM_ATTR gpio_isr_dispatcher(void* arg);
    PinConfig config_;
    gpio_num_t pin_num_;

private:
    bool initialized_;
};

} // namespace gpio

#endif // GPIO_PIN_ESP32_HPP
