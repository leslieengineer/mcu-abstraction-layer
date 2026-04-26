#include "gpio_pin_esp32.hpp"
#include "driver/gpio.h"
#include "esp_err.h"

namespace gpio {

// Static flag to track if ISR service is installed globally
static bool isr_service_installed = false;

// Static ISR handler that dispatches to the appropriate pin callback
static void IRAM_ATTR gpio_isr_dispatcher(void* arg) {
    GpioPinESP32* pin = static_cast<GpioPinESP32*>(arg);
    if (pin && pin->config_.interrupt_callback) {
        pin->config_.interrupt_callback(pin->pin_num_, pin->config_.interrupt_user_data);
    }
}

GpioPinESP32::GpioPinESP32(gpio_num_t pin_num)
    : pin_num_(pin_num), initialized_(false) {
}

GpioPinESP32::~GpioPinESP32() {
    // RAII: Automatically deinitialize when the object is destroyed
    if (initialized_) {
        deinit();
    }
}

ErrorCode GpioPinESP32::init(const PinConfig& config) {
    if (initialized_) {
        return ErrorCode::ALREADY_INITIALIZED;
    }

    // Validate pin number
    if (!GPIO_IS_VALID_GPIO(pin_num_)) {
        return ErrorCode::INVALID_PIN;
    }

    // Store configuration for later use
    config_ = config;

    // Build ESP-IDF gpio_config_t from our common config
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << pin_num_);

    // Map direction
    switch (config.direction) {
        case Direction::INPUT:
            io_conf.mode = GPIO_MODE_INPUT;
            break;
        case Direction::OUTPUT:
            io_conf.mode = GPIO_MODE_OUTPUT;
            break;
        case Direction::INPUT_OUTPUT:
            io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
            break;
        default:
            return ErrorCode::INVALID_CONFIG;
    }

    // Map pull resistors
    switch (config.pull) {
        case Pull::NONE:
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            break;
        case Pull::UP:
            io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            break;
        case Pull::DOWN:
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
            break;
        case Pull::UP_DOWN:
            io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
            break;
        default:
            return ErrorCode::INVALID_CONFIG;
    }

    // Map interrupt trigger
    switch (config.interrupt_trigger) {
        case InterruptTrigger::NONE:
            io_conf.intr_type = GPIO_INTR_DISABLE;
            break;
        case InterruptTrigger::RISING_EDGE:
            io_conf.intr_type = GPIO_INTR_POSEDGE;
            break;
        case InterruptTrigger::FALLING_EDGE:
            io_conf.intr_type = GPIO_INTR_NEGEDGE;
            break;
        case InterruptTrigger::BOTH_EDGES:
            io_conf.intr_type = GPIO_INTR_ANYEDGE;
            break;
        case InterruptTrigger::LOW_LEVEL:
            io_conf.intr_type = GPIO_INTR_LOW_LEVEL;
            break;
        case InterruptTrigger::HIGH_LEVEL:
            io_conf.intr_type = GPIO_INTR_HIGH_LEVEL;
            break;
        default:
            return ErrorCode::INVALID_CONFIG;
    }

    // Configure the GPIO
    esp_err_t err = gpio_config(&io_conf);
    if (err != ESP_OK) {
        return ErrorCode::HARDWARE_ERROR;
    }

    // Set initial level for output pins
    if (config.direction == Direction::OUTPUT || config.direction == Direction::INPUT_OUTPUT) {
        err = gpio_set_level(pin_num_, static_cast<uint32_t>(config.initial_level));
        if (err != ESP_OK) {
            return ErrorCode::HARDWARE_ERROR;
        }
    }

    // Install ISR service if needed and add handler
    if (config.interrupt_trigger != InterruptTrigger::NONE && config.interrupt_callback != nullptr) {
        // Install ISR service globally (only once)
        if (!isr_service_installed) {
            err = gpio_install_isr_service(0);
            if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
                return ErrorCode::HARDWARE_ERROR;
            }
            isr_service_installed = true;
        }

        // Add ISR handler for this pin
        err = gpio_isr_handler_add(pin_num_, gpio_isr_dispatcher, this);
        if (err != ESP_OK) {
            return ErrorCode::HARDWARE_ERROR;
        }
    }

    initialized_ = true;
    return ErrorCode::OK;
}

ErrorCode GpioPinESP32::deinit() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    // Remove ISR handler if configured
    if (config_.interrupt_trigger != InterruptTrigger::NONE && config_.interrupt_callback != nullptr) {
        gpio_isr_handler_remove(pin_num_);
    }

    // Reset the pin to input with no pulls or interrupts
    gpio_reset_pin(pin_num_);

    initialized_ = false;
    return ErrorCode::OK;
}

ErrorCode GpioPinESP32::set_level(Level level) {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    esp_err_t err = gpio_set_level(pin_num_, static_cast<uint32_t>(level));
    return (err == ESP_OK) ? ErrorCode::OK : ErrorCode::HARDWARE_ERROR;
}

ErrorCode GpioPinESP32::get_level(Level& level) {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    int raw_level = gpio_get_level(pin_num_);
    level = (raw_level == 0) ? Level::LOW : Level::HIGH;
    return ErrorCode::OK;
}

ErrorCode GpioPinESP32::toggle() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    Level current_level;
    ErrorCode err = get_level(current_level);
    if (err != ErrorCode::OK) {
        return err;
    }

    Level new_level = (current_level == Level::LOW) ? Level::HIGH : Level::LOW;
    return set_level(new_level);
}

ErrorCode GpioPinESP32::enable_interrupt() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    if (config_.interrupt_trigger == InterruptTrigger::NONE) {
        return ErrorCode::INVALID_CONFIG;
    }

    esp_err_t err = gpio_intr_enable(pin_num_);
    return (err == ESP_OK) ? ErrorCode::OK : ErrorCode::HARDWARE_ERROR;
}

ErrorCode GpioPinESP32::disable_interrupt() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    esp_err_t err = gpio_intr_disable(pin_num_);
    return (err == ESP_OK) ? ErrorCode::OK : ErrorCode::HARDWARE_ERROR;
}

uint32_t GpioPinESP32::get_pin_number() const {
    return static_cast<uint32_t>(pin_num_);
}

bool GpioPinESP32::is_initialized() const {
    return initialized_;
}

} // namespace gpio
