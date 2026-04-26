#ifndef COMMON_GPIO_ITF_HPP
#define COMMON_GPIO_ITF_HPP

#include "common_gpio_types.hpp"

namespace gpio {

/**
 * @brief Pure virtual interface for GPIO pin operations.
 * 
 * This interface defines the contract that all platform-specific
 * GPIO implementations must follow. It enables dependency injection
 * and makes testing easier.
 * 
 * Thread safety: Implementations are NOT required to be thread-safe.
 * Users must handle synchronization if needed.
 */
class IGpioPin {
public:
    virtual ~IGpioPin() = default;

    /**
     * @brief Initialize the GPIO pin with the given configuration.
     * 
     * This method must be called before any other operation.
     * Calling init() on an already-initialized pin returns ALREADY_INITIALIZED.
     * 
     * @param config Pin configuration.
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode init(const PinConfig& config) = 0;

    /**
     * @brief Deinitialize the GPIO pin and release resources.
     * 
     * After calling deinit(), the pin must be re-initialized before use.
     * Calling deinit() on a non-initialized pin returns NOT_INITIALIZED.
     * 
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode deinit() = 0;

    /**
     * @brief Set the output level of the GPIO pin.
     * 
     * Only valid for OUTPUT or INPUT_OUTPUT direction.
     * 
     * @param level Desired level (HIGH or LOW).
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode set_level(Level level) = 0;

    /**
     * @brief Read the current level of the GPIO pin.
     * 
     * Valid for both INPUT and OUTPUT directions.
     * 
     * @param level Output parameter for the read level.
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode get_level(Level& level) = 0;

    /**
     * @brief Toggle the output level of the GPIO pin.
     * 
     * Only valid for OUTPUT or INPUT_OUTPUT direction.
     * 
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode toggle() = 0;

    /**
     * @brief Enable interrupt for this pin.
     * 
     * The interrupt callback must be set during init() via PinConfig.
     * 
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode enable_interrupt() = 0;

    /**
     * @brief Disable interrupt for this pin.
     * 
     * @return ErrorCode::OK on success, error code otherwise.
     */
    virtual ErrorCode disable_interrupt() = 0;

    /**
     * @brief Get the raw pin number.
     * 
     * Useful for debugging or low-level operations.
     * 
     * @return The platform-specific pin number.
     */
    virtual uint32_t get_pin_number() const = 0;

    /**
     * @brief Check if the pin is initialized.
     * 
     * @return true if initialized, false otherwise.
     */
    virtual bool is_initialized() const = 0;
};

} // namespace gpio

#endif // COMMON_GPIO_ITF_HPP
