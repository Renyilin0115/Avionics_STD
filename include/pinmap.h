#pragma once
#include "stm32g0xx_hal.h"

/* SPI1 */
#define MOSI_Pin        GPIO_PIN_7
#define MOSI_GPIO_Port  GPIOA
#define MOSI_AF         GPIO_AF0_SPI1
#define MISO_Pin        GPIO_PIN_6
#define MISO_GPIO_Port  GPIOA
#define MISO_AF         GPIO_AF0_SPI1
#define SCK_Pin         GPIO_PIN_5
#define SCK_GPIO_Port   GPIOA
#define SCK_AF          GPIO_AF0_SPI1
#define NSS_Pin         GPIO_PIN_4        // 片選一般用 GPIO 控
#define NSS_GPIO_Port   GPIOA

/* USART1 */
#define TX1_Pin         GPIO_PIN_9
#define TX1_GPIO_Port   GPIOA
#define TX1_AF          GPIO_AF1_USART1
#define RX1_Pin         GPIO_PIN_10
#define RX1_GPIO_Port   GPIOA
#define RX1_AF          GPIO_AF1_USART1

/* USART2 */
#define TX2_Pin         GPIO_PIN_2
#define TX2_GPIO_Port   GPIOA
#define TX2_AF          GPIO_AF1_USART2
#define RX2_Pin         GPIO_PIN_3
#define RX2_GPIO_Port   GPIOA
#define RX2_AF          GPIO_AF1_USART2
#define CTS2_Pin        GPIO_PIN_0
#define CTS2_GPIO_Port  GPIOA
#define CTS2_AF         GPIO_AF1_USART2
#define RTS2_Pin        GPIO_PIN_1
#define RTS2_GPIO_Port  GPIOA
#define RTS2_AF         GPIO_AF1_USART2

/* I2C1 */
#define SCL1_Pin        GPIO_PIN_6
#define SCL1_GPIO_Port  GPIOB
#define SCL1_AF         GPIO_AF6_I2C1
#define SDA1_Pin        GPIO_PIN_7
#define SDA1_GPIO_Port  GPIOB
#define SDA1_AF         GPIO_AF6_I2C1
#define SMBA1_Pin       GPIO_PIN_5
#define SMBA1_GPIO_Port GPIOB
#define SMBA1_AF        GPIO_AF6_I2C1

/* I2C2（G031：PA11/PA12） */
#define SCL2_Pin        GPIO_PIN_11
#define SCL2_GPIO_Port  GPIOA
#define SCL2_AF         GPIO_AF6_I2C2
#define SDA2_Pin        GPIO_PIN_12
#define SDA2_GPIO_Port  GPIOA
#define SDA2_AF         GPIO_AF6_I2C2

/* 一般 IO */
#define Basic_Pin       GPIO_PIN_6
#define Basic_GPIO_Port GPIOC

/* SWD（僅標註，勿改動） */
#define SWDIO_Pin       GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin       GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
