

//1. As a simple GPIO input to read the level on the pin, or as a simple GPIO output to output the desired level on the pin.
//2. As a peripheral signal input/output.

#include "driver/gpio.h"

class GPIOESP32 {
public:
    GPIOESP32()
    {
    }
    void init(gpio_config_t &config) {
        // Configure the GPIO pin based on the provided configuration
        gpio_config(&config);
    }

    void setPinLevel(gpio_num_t pin, uint32_t level) {
        // Set the GPIO pin level (0 or 1)
        gpio_set_level(pin, level);
    }

    void getPinLevel(gpio_num_t pin, uint32_t &level) {
        // Get the current level of the GPIO pin
        level = gpio_get_level(pin);
    }

    void resetPinLevel(gpio_num_t pin) {
        // Reset the GPIO pin level to 0
        gpio_set_level(pin, 0);
    }


private:
    gpio_config_t io_conf = {};

}

    // io_conf.pin_bit_mask = 0; // ((1ULL<<19) // số 1 dịch 19 lần -> chọn GPIO19
    // io_conf.mode = GPIO_MODE_OUTPUT; // Set as output mode
    // io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // Disable pull-up mode
    // io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // Disable pull-down mode
    // io_conf.intr_type = GPIO_INTR_DISABLE; // Disable interrupt

// gpio_config();

//     //zero-initialize the config structure.
//     gpio_config_t io_conf = {};
//     //disable interrupt
//     io_conf.intr_type = GPIO_INTR_DISABLE;
//     //set as output mode
//     io_conf.mode = GPIO_MODE_OUTPUT;
//     //bit mask of the pins that you want to set,e.g.GPIO18/19
//     io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
//     //disable pull-down mode
//     io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
//     //disable pull-up mode
//     io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
//     //configure GPIO with the given settings
//     gpio_config(&io_conf);

//     //interrupt of rising edge
//     io_conf.intr_type = GPIO_INTR_POSEDGE;
//     //bit mask of the pins, use GPIO4/5 here
//     io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
//     //set as input mode
//     io_conf.mode = GPIO_MODE_INPUT;
//     //enable pull-up mode
//     io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
//     gpio_config(&io_conf);

//     //change gpio interrupt type for one pin
//     gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);

//     //create a queue to handle gpio event from isr
//     gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
//     //start gpio task
//     xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

//     //install gpio isr service
//     gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
//     //hook isr handler for specific gpio pin
//     gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
//     //hook isr handler for specific gpio pin
//     gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void*) GPIO_INPUT_IO_1);

//     //remove isr handler for gpio number.
//     gpio_isr_handler_remove(GPIO_INPUT_IO_0);
//     //hook isr handler for specific gpio pin again
//     gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);