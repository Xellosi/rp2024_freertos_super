/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25
#endif

static int pico_led_init(void) {
    // Official Raspberry Pi Pico uses onboard LED on GPIO 25.
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
}

static void pico_set_led(bool led_on) {
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
}

static void blink_task(void *ctx) {
    (void)ctx;

    while (true) {
        pico_set_led(true);
        vTaskDelay(pdMS_TO_TICKS(LED_DELAY_MS));
        pico_set_led(false);
        vTaskDelay(pdMS_TO_TICKS(LED_DELAY_MS));
    }
}

int main(void) {
    stdio_init_all();

    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    BaseType_t task_ok = xTaskCreate(
        blink_task,
        "blink",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL);
    hard_assert(task_ok == pdPASS);

    vTaskStartScheduler();

    for (;;) {
        tight_loop_contents();
    }
}
