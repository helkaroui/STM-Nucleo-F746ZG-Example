/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 500

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
struct gpio_dt_spec leds[3];

void setup(void){
	int ret;

	if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2))
	{
		return;
	}

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE) ||
		  gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE) ||
		  gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return;
	}

	leds[0] = led0;
	leds[1] = led1;
	leds[2] = led2;

	for (int i = 0; i < 3; i++)
	{
		gpio_pin_set(leds[i].port, leds[i].pin, 1);
	}
}

void main(void)
{
	setup();

	while (1)
	{
		for (int i = 0; i < 3; i++)
		{
			gpio_pin_toggle_dt(&leds[i]);
			k_msleep(SLEEP_TIME_MS);
		}
	}
}
