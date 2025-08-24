#include "bsp_led.h"

void LED_GPIO_Config(void) {
	GPIO_InitTypeDef gpio_cfg;
	
	RCC_AHB1PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK | LED4_GPIO_CLK, ENABLE);
	
	// led1
	gpio_cfg.GPIO_Pin = LED1_PIN;
	gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
	gpio_cfg.GPIO_OType = GPIO_OType_PP;
	gpio_cfg.GPIO_Speed = GPIO_Speed_2MHz;
	gpio_cfg.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(LED1_GPIO_PORT, &gpio_cfg);
	
	// led2
	gpio_cfg.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_GPIO_PORT, &gpio_cfg);
	
	// led3
	gpio_cfg.GPIO_Pin = LED3_PIN;
	GPIO_Init(LED3_GPIO_PORT, &gpio_cfg);
	
	// led4
	gpio_cfg.GPIO_Pin = LED4_PIN;
	GPIO_Init(LED4_GPIO_PORT, &gpio_cfg);
	
	// rgb off
	LED_BLACK;
	
	// led4 on
	LED4(ON);
}

