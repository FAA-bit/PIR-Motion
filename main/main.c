
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define PIR_GPIO GPIO_NUM_4

void app_main(void)
{
    gpio_config_t pir_config = {
        .pin_bit_mask = (1ULL << PIR_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    ESP_ERROR_CHECK(gpio_config(&pir_config));

    printf("PIR motion detector starting...\n");
    printf("Allow the sensor time to stabilize.\n");


int previous_motion = -1;

while (1)
{
    int motion = gpio_get_level(PIR_GPIO);

    if (motion != previous_motion)
    {
        if (motion == 1)
        {
            printf("Motion detected!\n");
        }
        else
        {
            printf("No motion detected.\n");
        }

        previous_motion = motion;
    }

    vTaskDelay(pdMS_TO_TICKS(100));
}
}
