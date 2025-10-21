#pragma once
#include "stm32g0xx_hal.h"

/* 全域外設 handle */
extern UART_HandleTypeDef huart1, huart2;
extern SPI_HandleTypeDef  hspi1;
extern I2C_HandleTypeDef  hi2c1, hi2c2;

/* 系統與板級初始化 */
void SystemClock_Config(void);
void MX_GPIO_BoardInit(void);
void MX_USART1_BoardInit(uint32_t baud, uint8_t hwflow); // hwflow: 0/1
void MX_USART2_BoardInit(uint32_t baud, uint8_t hwflow);
void MX_SPI1_BoardInit(void);
void MX_I2C1_BoardInit(uint32_t khz);   // 100 或 400
void MX_I2C2_BoardInit(uint32_t khz);   // 依需要呼叫
