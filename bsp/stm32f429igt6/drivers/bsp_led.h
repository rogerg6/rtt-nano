#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"


///////////////// 引脚定义 ////////////////////
// Red Led
#define LED1_PIN			GPIO_Pin_10
#define LED1_GPIO_PORT		GPIOH
#define LED1_GPIO_CLK		RCC_AHB1Periph_GPIOH

// Green Led
#define LED2_PIN			GPIO_Pin_11
#define LED2_GPIO_PORT		GPIOH
#define LED2_GPIO_CLK		RCC_AHB1Periph_GPIOH

// Blue Led
#define LED3_PIN			GPIO_Pin_12
#define LED3_GPIO_PORT		GPIOH
#define LED3_GPIO_CLK		RCC_AHB1Periph_GPIOH

// 小指示灯
#define LED4_PIN			GPIO_Pin_11
#define LED4_GPIO_PORT		GPIOD
#define LED4_GPIO_CLK		RCC_AHB1Periph_GPIOD



///////////////// 控制灯亮灭 ////////////////////
#define ON  0
#define OFF 1

#define LED1(x) if (x) GPIO_SetBits(LED1_GPIO_PORT, LED1_PIN); else GPIO_ResetBits(LED1_GPIO_PORT, LED1_PIN)
#define LED2(x) if (x) GPIO_SetBits(LED2_GPIO_PORT, LED2_PIN); else GPIO_ResetBits(LED2_GPIO_PORT, LED2_PIN)
#define LED3(x) if (x) GPIO_SetBits(LED3_GPIO_PORT, LED3_PIN); else GPIO_ResetBits(LED3_GPIO_PORT, LED3_PIN)
#define LED4(x) if (x) GPIO_SetBits(LED4_GPIO_PORT, LED4_PIN); else GPIO_ResetBits(LED4_GPIO_PORT, LED4_PIN)

//////////////// 直接操作寄存器方法控制IO //////////////
#define digitalHi(p, i)			{ p->BSRRL = i; }	// set high level
#define digitalLo(p, i)			{ p->BSRRH = i; }	// set low  level
#define digitalToggle(p, i)		{ p->ODR ^= i;  }	// 反转电平

#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT, LED1_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT, LED1_PIN)
#define LED1_OFF		digitalHi(LED1_GPIO_PORT, LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT, LED2_PIN)
#define LED2_ON			digitalLo(LED2_GPIO_PORT, LED2_PIN)
#define LED2_OFF		digitalHi(LED2_GPIO_PORT, LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT, LED3_PIN)
#define LED3_ON			digitalLo(LED3_GPIO_PORT, LED3_PIN)
#define LED3_OFF		digitalHi(LED3_GPIO_PORT, LED3_PIN)

#define LED4_TOGGLE		digitalToggle(LED4_GPIO_PORT, LED4_PIN)
#define LED4_ON			digitalLo(LED4_GPIO_PORT, LED4_PIN)
#define LED4_OFF		digitalHi(LED4_GPIO_PORT, LED4_PIN)


// Red
#define LED_RED LED1(ON); \
				LED2(OFF); \
				LED3(OFF)
// Green
#define LED_GREEN LED1(OFF); \
				LED2(ON); \
				LED3(OFF)

// Blue
#define LED_BLUE LED1(OFF); \
				LED2(OFF); \
				LED3(ON)

// Yellow( R+G)
#define LED_YELLOW LED1(ON); \
				LED2(ON); \
				LED3(OFF)
// purple (R+B)
#define LED_PURPLE LED1(ON); \
				LED2(OFF); \
				LED3(ON)

// cyan (G+B)
#define LED_CYAN LED1(OFF); \
				LED2(ON); \
				LED3(ON)

// White (R+G+B)
#define LED_WHITE LED1(ON); \
				LED2(ON); \
				LED3(ON)

// Black 
#define LED_BLACK LED1(OFF); \
				LED2(OFF); \
				LED3(OFF)

void LED_GPIO_Config(void);

#endif

