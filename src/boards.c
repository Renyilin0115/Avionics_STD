#include "pinmap.h"
#include "boards.h"

/* -------- handles -------- */
UART_HandleTypeDef huart1, huart2;
SPI_HandleTypeDef  hspi1;
I2C_HandleTypeDef  hi2c1, hi2c2;

/* -------- helpers -------- */
static void gpio_af(GPIO_TypeDef* port, uint16_t pin, uint32_t af, uint32_t pull, uint32_t speed){
  GPIO_InitTypeDef g={0};
  g.Pin = pin; g.Mode = GPIO_MODE_AF_PP; g.Pull = pull; g.Speed = speed; g.Alternate = af;
  HAL_GPIO_Init(port, &g);
}
static void i2c_timing_set(I2C_HandleTypeDef* hi2c, uint32_t khz){
  /* 64 MHz SYSCLK 下常用 timing（建議後續用 CubeMX 精算） */
  hi2c->Init.Timing = (khz>=400) ? 0x0010020A : 0x00303D5B; // ~400k / ~100k
}

/* -------- clocks -------- */

static void LSE_BYPASS_Enable(void) {
    RCC_OscInitTypeDef osc = {0};
    osc.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    osc.LSEState = RCC_LSE_BYPASS;     // 方波輸入
    HAL_RCC_OscConfig(&osc);
}

void SystemClock_Config(void){
  RCC_OscInitTypeDef osc = {0};
  RCC_ClkInitTypeDef clk = {0};

  osc.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  osc.HSIState            = RCC_HSI_ON;
  osc.HSIDiv              = RCC_HSI_DIV1;
  osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  osc.PLL.PLLState        = RCC_PLL_ON;
  osc.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  osc.PLL.PLLM            = RCC_PLLM_DIV1;
  osc.PLL.PLLN            = 8;
  osc.PLL.PLLR            = RCC_PLLR_DIV2;
  osc.PLL.PLLP            = RCC_PLLP_DIV2;
  osc.PLL.PLLQ            = RCC_PLLQ_DIV2;
  HAL_RCC_OscConfig(&osc);

  clk.ClockType      = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  clk.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  clk.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2);
}

/* -------- board gpio (LED/NSS 等) -------- */
void MX_GPIO_BoardInit(void){
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef g={0};

  /* LED / Basic IO */
  g.Pin=Basic_Pin; g.Mode=GPIO_MODE_OUTPUT_PP; g.Pull=GPIO_NOPULL; g.Speed=GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Basic_GPIO_Port,&g);

  /* NSS 片選 */
  g.Pin=NSS_Pin; g.Mode=GPIO_MODE_OUTPUT_PP; g.Pull=GPIO_NOPULL; g.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(NSS_GPIO_Port,&g);
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
}

/* -------- USART -------- */
void MX_USART1_BoardInit(uint32_t baud, uint8_t hwflow){
  __HAL_RCC_USART1_CLK_ENABLE();
  gpio_af(TX1_GPIO_Port, TX1_Pin, TX1_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
  gpio_af(RX1_GPIO_Port, RX1_Pin, RX1_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);

  huart1.Instance = USART1;
  huart1.Init.BaudRate = baud;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits   = UART_STOPBITS_1;
  huart1.Init.Parity     = UART_PARITY_NONE;
  huart1.Init.Mode       = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl  = hwflow ? UART_HWCONTROL_RTS_CTS : UART_HWCONTROL_NONE;
  HAL_UART_Init(&huart1);
}

void MX_USART2_BoardInit(uint32_t baud, uint8_t hwflow){
  __HAL_RCC_USART2_CLK_ENABLE();
  gpio_af(TX2_GPIO_Port, TX2_Pin, TX2_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
  gpio_af(RX2_GPIO_Port, RX2_Pin, RX2_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
  if(hwflow){
    gpio_af(CTS2_GPIO_Port, CTS2_Pin, CTS2_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
    gpio_af(RTS2_GPIO_Port, RTS2_Pin, RTS2_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
  }

  huart2.Instance = USART2;
  huart2.Init.BaudRate = baud;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits   = UART_STOPBITS_1;
  huart2.Init.Parity     = UART_PARITY_NONE;
  huart2.Init.Mode       = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl  = hwflow ? UART_HWCONTROL_RTS_CTS : UART_HWCONTROL_NONE;
  HAL_UART_Init(&huart2);
}

/* -------- SPI1 -------- */
void MX_SPI1_BoardInit(void){
  __HAL_RCC_SPI1_CLK_ENABLE();
  gpio_af(SCK_GPIO_Port,  SCK_Pin,  SCK_AF,  GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
  gpio_af(MISO_GPIO_Port, MISO_Pin, MISO_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
  gpio_af(MOSI_GPIO_Port, MOSI_Pin, MOSI_AF, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase    = SPI_PHASE_1EDGE;
  hspi1.Init.NSS         = SPI_NSS_SOFT;              // 片選改用 GPIO
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // 視需求
  hspi1.Init.FirstBit    = SPI_FIRSTBIT_MSB;
  HAL_SPI_Init(&hspi1);

  /* NSS 預設為高 */
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
}

/* -------- I2C -------- */
void MX_I2C1_BoardInit(uint32_t khz){
  __HAL_RCC_I2C1_CLK_ENABLE();

  /* I2C 腳需開漏；HAL 會處理 ODR，這裡只需 AF_PP + AF 指派 */
  gpio_af(SCL1_GPIO_Port, SCL1_Pin, SCL1_AF, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW);
  gpio_af(SDA1_GPIO_Port, SDA1_Pin, SDA1_AF, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW);
  /* 可選 SMBA */
  gpio_af(SMBA1_GPIO_Port, SMBA1_Pin, SMBA1_AF, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW);

  hi2c1.Instance = I2C1;
  i2c_timing_set(&hi2c1, khz);
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&hi2c1);
}

void MX_I2C2_BoardInit(uint32_t khz){
  __HAL_RCC_I2C2_CLK_ENABLE();
  gpio_af(SCL2_GPIO_Port, SCL2_Pin, SCL2_AF, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW);
  gpio_af(SDA2_GPIO_Port, SDA2_Pin, SDA2_AF, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW);

  hi2c2.Instance = I2C2;
  i2c_timing_set(&hi2c2, khz);
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&hi2c2);
}
