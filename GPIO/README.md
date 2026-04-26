# GPIO Abstraction Layer

A portable, pin-centric GPIO abstraction layer for ESP32, STM32, and other microcontroller families.

## Design Principles

This abstraction layer follows these key principles:

1. **Pin-Centric**: Each GPIO pin is represented by an object with its own state
2. **RAII**: Pins are automatically deinitialized when destroyed (Resource Acquisition Is Initialization)
3. **Builder Pattern**: Fluent, type-safe configuration using builders
4. **Interface-Based**: Easy to mock and test with pure virtual interfaces
5. **Clear Error Handling**: All operations return `ErrorCode` enum
6. **Platform Agnostic**: Application code is portable across different MCUs

## Features

- ✅ Unified API for GPIO operations across ESP32 and STM32
- ✅ Type-safe configuration using builder pattern
- ✅ Automatic resource cleanup with RAII
- ✅ Interrupt support with user callbacks
- ✅ Pull-up/down resistor configuration
- ✅ Output mode selection (push-pull, open-drain)
- ✅ Comprehensive error codes

## Quick Start

### ESP32 Example

```cpp
#include "common_gpio.hpp"
#include "gpio_pin_esp32.hpp"

using namespace gpio;

void app_main() {
    // Create a pin object for GPIO2
    GpioPinESP32 led_pin(GPIO_NUM_2);
    
    // Configure as output with low initial level
    auto config = PinConfigBuilder()
        .as_output(Level::LOW)
        .build();
    
    // Initialize the pin
    if (led_pin.init(config) == ErrorCode::OK) {
        // Blink the LED
        led_pin.set_level(Level::HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000));
        led_pin.set_level(Level::LOW);
    }
    
    // Pin is automatically deinitialized when led_pin goes out of scope
}
```

### STM32 Example

```cpp
#include "stm32l4xx_hal.h"
#include "common_gpio.hpp"
#include "gpio_pin_stm32.hpp"

using namespace gpio;

int main() {
    // HAL initialization
    HAL_Init();
    SystemClock_Config();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // Create a pin object for PA5
    GpioPinSTM32 led_pin(GPIOA, GPIO_PIN_5);
    
    // Configure as output
    auto config = PinConfigBuilder()
        .as_output(Level::LOW)
        .build();
    
    led_pin.init(config);
    
    while(1) {
        led_pin.toggle();
        HAL_Delay(1000);
    }
}
```

### Interrupt Example

```cpp
#include "common_gpio.hpp"
#include "gpio_pin_esp32.hpp"

using namespace gpio;

// Interrupt callback function
void button_isr(uint32_t pin, void* user_data) {
    int* counter = static_cast<int*>(user_data);
    (*counter)++;
}

void app_main() {
    int press_count = 0;
    
    // Create button pin
    GpioPinESP32 button(GPIO_NUM_0);
    
    // Configure as input with pull-up and falling edge interrupt
    auto config = PinConfigBuilder()
        .as_input(Pull::UP)
        .with_interrupt(InterruptTrigger::FALLING_EDGE, button_isr, &press_count)
        .build();
    
    button.init(config);
    
    // Counter will increment on each button press
}
```

## API Reference

### Core Types

#### `ErrorCode` Enum

```cpp
enum class ErrorCode {
    OK = 0,
    INVALID_PIN = -1,
    INVALID_CONFIG = -2,
    ALREADY_INITIALIZED = -3,
    NOT_INITIALIZED = -4,
    HARDWARE_ERROR = -5,
    UNSUPPORTED_OPERATION = -6
};
```

#### `Direction` Enum

```cpp
enum class Direction {
    INPUT,
    OUTPUT,
    INPUT_OUTPUT  // Open-drain or bidirectional
};
```

#### `Level` Enum

```cpp
enum class Level : uint8_t {
    LOW = 0,
    HIGH = 1
};
```

#### `Pull` Enum

```cpp
enum class Pull {
    NONE,
    UP,
    DOWN,
    UP_DOWN  // Both (some MCUs support this)
};
```

#### `OutputMode` Enum

```cpp
enum class OutputMode {
    PUSH_PULL,
    OPEN_DRAIN
};
```

#### `InterruptTrigger` Enum

```cpp
enum class InterruptTrigger {
    NONE,
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES,
    LOW_LEVEL,
    HIGH_LEVEL
};
```

### IGpioPin Interface

All platform implementations must implement this interface:

```cpp
class IGpioPin {
    virtual ErrorCode init(const PinConfig& config) = 0;
    virtual ErrorCode deinit() = 0;
    virtual ErrorCode set_level(Level level) = 0;
    virtual ErrorCode get_level(Level& level) = 0;
    virtual ErrorCode toggle() = 0;
    virtual ErrorCode enable_interrupt() = 0;
    virtual ErrorCode disable_interrupt() = 0;
    virtual uint32_t get_pin_number() const = 0;
    virtual bool is_initialized() const = 0;
};
```

### PinConfigBuilder

Fluent builder for creating `PinConfig`:

```cpp
auto config = PinConfigBuilder()
    .direction(Direction::OUTPUT)
    .pull(Pull::NONE)
    .output_mode(OutputMode::PUSH_PULL)
    .initial_level(Level::LOW)
    .build();

// Or use convenience methods:
auto input_config = PinConfigBuilder()
    .as_input(Pull::UP)
    .build();

auto output_config = PinConfigBuilder()
    .as_output(Level::HIGH, OutputMode::PUSH_PULL)
    .build();

auto interrupt_config = PinConfigBuilder()
    .as_input(Pull::UP)
    .with_interrupt(InterruptTrigger::FALLING_EDGE, my_callback, user_data)
    .build();
```

## CMake Integration

### In ESP-IDF Project

```cmake
# In your project's CMakeLists.txt
add_subdirectory(path/to/mcu-abstraction-layer/GPIO)

# In main/CMakeLists.txt
idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES gpio  # Link the GPIO library
)
```

### In STM32 Project

```cmake
# Set platform before including GPIO library
set(GPIO_TARGET_PLATFORM "stm32")
add_subdirectory(path/to/mcu-abstraction-layer/GPIO)

# Link to your executable
target_link_libraries(your_app PRIVATE gpio)
```

## Architecture

```
GPIO/
├── common/                      # Platform-agnostic code
│   └── include/
│       ├── common_gpio_types.hpp    # Enums, structs, typedefs
│       ├── common_gpio_itf.hpp      # Pure virtual interface
│       ├── common_gpio_builder.hpp  # Builder pattern for config
│       └── common_gpio.hpp          # Main header (includes all above)
├── esp32/                      # ESP32 implementation
│   ├── gpio_pin_esp32.hpp
│   └── gpio_pin_esp32.cpp
├── stm32l4/                    # STM32 implementation
│   ├── gpio_pin_stm32.hpp
│   └── gpio_pin_stm32.cpp
└── CMakeLists.txt             # Platform-aware build config
```

## Platform Support

| Platform | Status | Notes |
|----------|--------|-------|
| ESP32    | ✅ Complete | All features supported |
| STM32L4  | ✅ Complete | Uses STM32 HAL |
| STM32F4  | 🚧 Planned | Same code as STM32L4, just include appropriate HAL |

## Design Decisions

See [ADR-0002](../docs/02-System-Architecture/ADR/ADR-0002-layered-gpio-abstraction-with-core-and-extensions.md) for the rationale behind this layered abstraction approach.

## License

[Your License Here]

## Contributing

Contributions are welcome! To add support for a new platform:

1. Create a new folder (e.g., `nrf52/`)
2. Implement `IGpioPin` interface
3. Update `CMakeLists.txt` to detect and build for the new platform
4. Add examples and tests
