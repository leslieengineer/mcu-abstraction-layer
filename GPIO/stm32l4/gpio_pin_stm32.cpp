#include "gpio_pin_stm32.hpp"

// This implementation assumes STM32 HAL is available
// Include the appropriate HAL header in your project:
// - For STM32L4: #include "stm32l4xx_hal.h"
// - For STM32F4: #include "stm32f4xx_hal.h"
// etc.

#ifdef HAL_GPIO_MODULE_ENABLED

namespace gpio {

GpioPinSTM32::GpioPinSTM32(GPIO_TypeDef* port, uint16_t pin)
    : port_(port), pin_(pin), initialized_(false) {
}

GpioPinSTM32::~GpioPinSTM32() {
    // RAII: Automatically deinitialize when the object is destroyed
    if (initialized_) {
        deinit();
    }
}

ErrorCode GpioPinSTM32::init(const PinConfig& config) {
    if (initialized_) {
        return ErrorCode::ALREADY_INITIALIZED;
    }

    if (!port_ || pin_ == 0) {
        return ErrorCode::INVALID_PIN;
    }

    // Store configuration for later use
    config_ = config;

    // Build STM32 HAL GPIO_InitTypeDef from our common config
    GPIO_InitTypeDef gpio_init = {};
    gpio_init.Pin = pin_;

    // Map direction
    switch (config.direction) {
        case Direction::INPUT:
            gpio_init.Mode = GPIO_MODE_INPUT;
            break;
        case Direction::OUTPUT:
            gpio_init.Mode = (config.output_mode == OutputMode::PUSH_PULL) 
                ? GPIO_MODE_OUTPUT_PP : GPIO_MODE_OUTPUT_OD;
            break;
        case Direction::INPUT_OUTPUT:
            gpio_init.Mode = GPIO_MODE_OUTPUT_OD;  // Open-drain for bidirectional
            break;
        default:
            return ErrorCode::INVALID_CONFIG;
    }

    // Map interrupt trigger
    if (config.interrupt_trigger != InterruptTrigger::NONE) {
        switch (config.interrupt_trigger) {
            case InterruptTrigger::RISING_EDGE:
                gpio_init.Mode = GPIO_MODE_IT_RISING;
                break;
            case InterruptTrigger::FALLING_EDGE:
                gpio_init.Mode = GPIO_MODE_IT_FALLING;
                break;
            case InterruptTrigger::BOTH_EDGES:
                gpio_init.Mode = GPIO_MODE_IT_RISING_FALLING;
                break;
            default:
                // STM32 doesn't directly support level-triggered interrupts
                // via HAL in the same way
                return ErrorCode::UNSUPPORTED_OPERATION;
        }
    }

    // Map pull resistors
    switch (config.pull) {
        case Pull::NONE:
            gpio_init.Pull = GPIO_NOPULL;
            break;
        case Pull::UP:
            gpio_init.Pull = GPIO_PULLUP;
            break;
        case Pull::DOWN:
            gpio_init.Pull = GPIO_PULLDOWN;
            break;
        case Pull::UP_DOWN:
            // STM32 cannot enable both simultaneously
            return ErrorCode::UNSUPPORTED_OPERATION;
        default:
            return ErrorCode::INVALID_CONFIG;
    }

    // Speed (use high speed by default for outputs)
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;

    // Initialize the pin
    HAL_GPIO_Init(port_, &gpio_init);

    // Set initial level for output pins
    if (config.direction == Direction::OUTPUT || config.direction == Direction::INPUT_OUTPUT) {
        HAL_GPIO_WritePin(port_, pin_, 
            (config.initial_level == Level::HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    // Enable interrupt if configured
    if (config.interrupt_trigger != InterruptTrigger::NONE) {
        int irq_num = get_irq_number();
        if (irq_num >= 0) {
            HAL_NVIC_SetPriority(static_cast<IRQn_Type>(irq_num), 5, 0);
            HAL_NVIC_EnableIRQ(static_cast<IRQn_Type>(irq_num));
        }
    }

    initialized_ = true;
    return ErrorCode::OK;
}

ErrorCode GpioPinSTM32::deinit() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    // Disable interrupt if configured
    if (config_.interrupt_trigger != InterruptTrigger::NONE) {
        int irq_num = get_irq_number();
        if (irq_num >= 0) {
            HAL_NVIC_DisableIRQ(static_cast<IRQn_Type>(irq_num));
        }
    }

    // Deinitialize the pin
    HAL_GPIO_DeInit(port_, pin_);

    initialized_ = false;
    return ErrorCode::OK;
}

ErrorCode GpioPinSTM32::set_level(Level level) {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    HAL_GPIO_WritePin(port_, pin_, 
        (level == Level::HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return ErrorCode::OK;
}

ErrorCode GpioPinSTM32::get_level(Level& level) {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    GPIO_PinState pin_state = HAL_GPIO_ReadPin(port_, pin_);
    level = (pin_state == GPIO_PIN_SET) ? Level::HIGH : Level::LOW;
    return ErrorCode::OK;
}

ErrorCode GpioPinSTM32::toggle() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    HAL_GPIO_TogglePin(port_, pin_);
    return ErrorCode::OK;
}

ErrorCode GpioPinSTM32::enable_interrupt() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    if (config_.interrupt_trigger == InterruptTrigger::NONE) {
        return ErrorCode::INVALID_CONFIG;
    }

    int irq_num = get_irq_number();
    if (irq_num >= 0) {
        HAL_NVIC_EnableIRQ(static_cast<IRQn_Type>(irq_num));
        return ErrorCode::OK;
    }
    
    return ErrorCode::HARDWARE_ERROR;
}

ErrorCode GpioPinSTM32::disable_interrupt() {
    if (!initialized_) {
        return ErrorCode::NOT_INITIALIZED;
    }

    int irq_num = get_irq_number();
    if (irq_num >= 0) {
        HAL_NVIC_DisableIRQ(static_cast<IRQn_Type>(irq_num));
        return ErrorCode::OK;
    }
    
    return ErrorCode::HARDWARE_ERROR;
}

uint32_t GpioPinSTM32::get_pin_number() const {
    // Convert pin mask to pin number
    // GPIO_PIN_0 = 0x0001, GPIO_PIN_1 = 0x0002, etc.
    uint32_t pin_num = 0;
    uint16_t mask = pin_;
    while (mask > 1) {
        mask >>= 1;
        pin_num++;
    }
    return pin_num;
}

bool GpioPinSTM32::is_initialized() const {
    return initialized_;
}

int GpioPinSTM32::get_irq_number() const {
    // Map GPIO pin to EXTI IRQ number
    // This is simplified; actual mapping depends on the STM32 family
    uint32_t pin_num = get_pin_number();
    
    #if defined(EXTI0_IRQn) && defined(EXTI15_10_IRQn)
    // Common mapping for many STM32 families
    if (pin_num == 0) return EXTI0_IRQn;
    if (pin_num == 1) return EXTI1_IRQn;
    if (pin_num == 2) return EXTI2_IRQn;
    if (pin_num == 3) return EXTI3_IRQn;
    if (pin_num == 4) return EXTI4_IRQn;
    if (pin_num >= 5 && pin_num <= 9) return EXTI9_5_IRQn;
    if (pin_num >= 10 && pin_num <= 15) return EXTI15_10_IRQn;
    #endif
    
    return -1;  // Unsupported or invalid pin
}

} // namespace gpio

#else
    #warning "STM32 HAL GPIO module is not enabled. GpioPinSTM32 will not be compiled."
#endif // HAL_GPIO_MODULE_ENABLED
