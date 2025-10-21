#include "stm32g0xx_hal.h"
#include "boards.h"
#include "pinmap.h"

extern UART_HandleTypeDef huart1;

int main(void){
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_BoardInit();
  MX_USART1_BoardInit(115200, 0);   // 無 RTS/CTS
  MX_SPI1_BoardInit();
  MX_I2C1_BoardInit(100);           // 100 kHz

  const char *msg="READY\r\n";
  HAL_UART_Transmit(&huart1,(uint8_t*)msg,6,50);

  LSE_BYPASS_Enable();
  SystemClock_Config();

  while(1){
    HAL_GPIO_TogglePin(Basic_GPIO_Port, Basic_Pin);
    HAL_Delay(500);
  }
}
