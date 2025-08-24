#include "bsp_usart.h"

static void NVIC_Config(void) {
    NVIC_InitTypeDef nvic_cfg;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    nvic_cfg.NVIC_IRQChannel = DEBUG_USART_IRQ;
    nvic_cfg.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_cfg.NVIC_IRQChannelSubPriority = 1;
    nvic_cfg.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&nvic_cfg);
}

void Debug_USART_Config(void) {
    GPIO_InitTypeDef gpio_cfg;
    USART_InitTypeDef usart_cfg;

    /// 初始化时钟
    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

    /// 配置gpio
    gpio_cfg.GPIO_Mode = GPIO_Mode_AF;
    gpio_cfg.GPIO_OType = GPIO_OType_PP;
    gpio_cfg.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;

    gpio_cfg.GPIO_Pin = DEBUG_USART_TX_PIN;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &gpio_cfg);
    gpio_cfg.GPIO_Pin = DEBUG_USART_RX_PIN;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &gpio_cfg);

    // 配置复用
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);
    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);

    /// 配置串口
    usart_cfg.USART_BaudRate = DEBUG_USART_BAUDRATE;
    usart_cfg.USART_WordLength = USART_WordLength_8b;
    usart_cfg.USART_Parity = USART_Parity_No;
    usart_cfg.USART_StopBits = USART_StopBits_1;
    usart_cfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_cfg.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(DEBUG_USART, &usart_cfg);

    // 使能串口中断
    // NVIC_Config();
    // USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);

    // 使能串口
    USART_Cmd(DEBUG_USART, ENABLE);
}

void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch){
    USART_SendData(pUSARTx, ch);
    // 等待发送数据寄存器为空
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch) {
    uint8_t hi = ch >> 8;
    uint8_t lo = ch & 0xff;
    Usart_SendByte(pUSARTx, hi);
    Usart_SendByte(pUSARTx, lo);
}

void Usart_SendString(USART_TypeDef *pUSARTx, char *str) {
    while (str && *str != '\0') {
        Usart_SendByte(pUSARTx, *str);
        str++;
    }
}

// 重定向fputc到串口，后续可在串口中使用printf
int fputc(int ch, FILE *f) {
    USART_SendData(DEBUG_USART, (uint8_t)ch);
    // 等待串口发送完数据
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);
    return ch;
}

// 重定向fgetc到串口，后续可在串口中使用getchar, scanf
int getc(FILE *f) {
    // 等待串口有数据
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(DEBUG_USART);
}