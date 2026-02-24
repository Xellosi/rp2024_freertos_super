cmake_minimum_required(VERSION 3.13)

set(SUPER_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH "Path to super project root")
set(PICO_BOARD pico CACHE STRING "Target Pico board" FORCE)
set(PICO_SDK_PATH "${SUPER_PROJECT_ROOT}/pico-sdk" CACHE PATH "Path to pico-sdk")
set(FREERTOS_PATH "${SUPER_PROJECT_ROOT}/FreeRTOS" CACHE PATH "Path to FreeRTOS repository")
set(FREERTOS_KERNEL_PATH "${FREERTOS_PATH}/FreeRTOS/Source" CACHE PATH "Path to FreeRTOS kernel")
set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to FreeRTOSConfig.h")

if(NOT DEFINED PICO_NO_PICOTOOL)
    set(PICO_NO_PICOTOOL 0)
endif()

if(NOT DEFINED picotool_DIR)
    set(_picotool_dir_candidates
        "${SUPER_PROJECT_ROOT}/workplace/signal_analysis/build/_deps/picotool"
        "${SUPER_PROJECT_ROOT}/workplace/rp2024/build/_deps/picotool"
    )

    foreach(_candidate IN LISTS _picotool_dir_candidates)
        if(EXISTS "${_candidate}/picotoolConfig.cmake")
            set(picotool_DIR "${_candidate}" CACHE PATH "Path to picotool package directory" FORCE)
            break()
        endif()
    endforeach()
endif()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(blink_freertos C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "blink_freertos super project root: ${SUPER_PROJECT_ROOT}")
message(STATUS "Using pico-sdk: ${PICO_SDK_PATH}")
message(STATUS "Using FreeRTOS: ${FREERTOS_PATH}")

if(NOT EXISTS "${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/library.cmake")
    set(_freertos_kernel_candidates
        "${FREERTOS_PATH}/FreeRTOS-Kernel"
        "${FREERTOS_PATH}"
    )

    foreach(_candidate IN LISTS _freertos_kernel_candidates)
        if(EXISTS "${_candidate}/portable/ThirdParty/GCC/RP2040/library.cmake")
            set(FREERTOS_KERNEL_PATH "${_candidate}" CACHE PATH "Path to FreeRTOS kernel" FORCE)
            break()
        endif()
    endforeach()
endif()

if(NOT EXISTS "${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/library.cmake")
    message(FATAL_ERROR
        "Cannot find RP2040 FreeRTOS kernel port.\n"
        "Checked:\n"
        "  ${FREERTOS_PATH}/FreeRTOS/Source\n"
        "  ${FREERTOS_PATH}/FreeRTOS-Kernel\n"
        "  ${FREERTOS_PATH}\n"
        "Please check submodules and FREERTOS_PATH."
    )
endif()

pico_sdk_init()
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/library.cmake)

add_executable(blink_freertos
    blink.c
)

target_include_directories(blink_freertos PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(blink_freertos
    pico_stdlib
    FreeRTOS-Kernel-Heap4
)

pico_enable_stdio_usb(blink_freertos 1)
pico_enable_stdio_uart(blink_freertos 0)

pico_add_extra_outputs(blink_freertos)
