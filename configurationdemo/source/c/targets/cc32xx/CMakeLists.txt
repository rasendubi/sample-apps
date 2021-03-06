# Before this module is added, SDK path must be provided
if (NOT EXISTS "${CC32XX_SDK}")
    message(FATAL_ERROR "CC32XX SDK path: ${CC32XX_SDK} not exist!")
endif ()

# Target support library that provides abstractions for cc32xx target.
add_library(target_support
        STATIC
        # Example files contains startup routine and other useful stuff.
        ${CC32XX_SDK}/example/common/uart_if.c
        ${CC32XX_SDK}/example/common/udma_if.c
        ${CC32XX_SDK}/example/common/gpio_if.c
        ${CC32XX_SDK}/example/common/startup_gcc.c
        cc32xx_support.c
        )

target_include_directories(target_support PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# CC32XX SDK libraries

set(LIB_DRIVER ${CC32XX_SDK}/driverlib/gcc/exe/libdriver.a)
set(LIB_SIMPLELINK_NONOS ${CC32XX_SDK}/simplelink/gcc/exe/libsimplelink_nonos.a)
set(CC32XX_SDK_LIBS ${LIB_SIMPLELINK_NONOS} ${LIB_DRIVER})

target_include_directories(target_support
        PUBLIC
        ${CC32XX_SDK}/inc
        ${CC32XX_SDK}/driverlib
        ${CC32XX_SDK}/simplelink
        ${CC32XX_SDK}/simplelink/include
        ${CC32XX_SDK}/simplelink/source
        ${CC32XX_SDK}/example/common)

# Find and use ARM GCC libraries, provided that CMAKE_FIND_ROOT_PATH is properly set

find_library(LIB_C_PATH
        NAMES c libc
        PATHS /lib/armv7e-m/
        NO_DEFAULT_PATH)

find_library(LIB_M_PATH
        NAMES m libm
        PATHS /lib/armv7e-m/
        NO_DEFAULT_PATH)

# TODO: find more elegant solution to support different versions of the gcc library
# Rather than listing versions dirs in PATH_SUFFIXES variables
find_library(LIB_GCC_PATH
        NAMES gcc
        PATHS "${TOOLCHAIN_PATH}/lib/gcc/arm-none-eabi/"
        PATH_SUFFIXES 5.3.0/armv7e-m/ 4.9.3/armv7e-m/
        NO_DEFAULT_PATH
        NO_CMAKE_FIND_ROOT_PATH)

# GCC dependencies
target_link_libraries(target_support PUBLIC ${LIB_C_PATH} ${LIB_M_PATH} ${LIB_GCC_PATH})
# CC32XX dependencies
target_link_libraries(target_support PUBLIC ${CC32XX_SDK_LIBS})
# Propagate linker script
target_link_libraries(target_support PUBLIC -T ${CMAKE_CURRENT_SOURCE_DIR}/app.ld)

message("WiFi AP: ${WIFI_SSID}")
message("WiFi Pass: ${WIFI_PASSWORD}")

# Expose WiFi credentials
target_compile_definitions(target_support
        PUBLIC
        -DWIFI_SSID="${WIFI_SSID}"
        -DWIFI_PASSWORD="${WIFI_PASSWORD}")
