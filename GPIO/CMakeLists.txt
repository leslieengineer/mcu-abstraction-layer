# GPIO Abstraction Layer CMake Configuration
# 
# This library provides a portable GPIO abstraction for ESP32, STM32, and other MCUs.
# The CMake configuration conditionally includes platform-specific implementations.

# Determine the target platform
# This can be set by the parent CMakeLists.txt or detected automatically
if(NOT DEFINED GPIO_TARGET_PLATFORM)
    # Try to detect platform from existing CMake variables
    if(DEFINED IDF_TARGET OR DEFINED ENV{IDF_TARGET})
        set(GPIO_TARGET_PLATFORM "esp32")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|ARM)")
        set(GPIO_TARGET_PLATFORM "stm32")
    else()
        message(WARNING "GPIO_TARGET_PLATFORM not set. Defaulting to 'esp32'")
        set(GPIO_TARGET_PLATFORM "esp32")
    endif()
endif()

message(STATUS "GPIO library building for platform: ${GPIO_TARGET_PLATFORM}")

# Common source files (always included)
set(GPIO_COMMON_SOURCES
    # No .cpp in common/ currently since everything is header-only
)

# Platform-specific source files
if(GPIO_TARGET_PLATFORM STREQUAL "esp32")
    set(GPIO_PLATFORM_SOURCES
        esp32/gpio_pin_esp32.cpp
    )
    set(GPIO_PLATFORM_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/esp32
    )
elseif(GPIO_TARGET_PLATFORM STREQUAL "stm32")
    set(GPIO_PLATFORM_SOURCES
        stm32l4/gpio_pin_stm32.cpp
    )
    set(GPIO_PLATFORM_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32l4
    )
else()
    message(FATAL_ERROR "Unsupported GPIO_TARGET_PLATFORM: ${GPIO_TARGET_PLATFORM}")
endif()

# Create the library target named `gpio`.
# `STATIC` means CMake will build an archive library (.a on Linux, .lib on Windows).
add_library(gpio STATIC
    ${GPIO_COMMON_SOURCES}
    ${GPIO_PLATFORM_SOURCES}
)

# Public headers for this library live in `common/include`.
# `PUBLIC` means both this target and any target that links to `gpio`
# can use these include paths.
# `BUILD_INTERFACE` is used while building inside this source tree.
# `INSTALL_INTERFACE` is used after the library is installed elsewhere.
target_include_directories(gpio
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${GPIO_PLATFORM_INCLUDE_DIRS}
)

# Extra compile warnings for this target only.
# These do not create new files; they only change how the target is compiled.
target_compile_options(gpio PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# C++ standard requirement
target_compile_features(gpio PUBLIC cxx_std_11)

# ESP-IDF specific: Register as IDF component if building within esp-idf
if(GPIO_TARGET_PLATFORM STREQUAL "esp32" AND COMMAND idf_component_register)
    idf_component_register(
        REQUIRES esp_driver_gpio
    )
endif()
