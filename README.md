# AVIONICS_STD — STM32G031K8 Standard Avionics Firmware

## 專案簡介
本專案為淡江大學航電開發板（STM32G031K8）之標準韌體模板。
採用 **PlatformIO + STM32Cube HAL** 架構，整合 HSI + LSE_BYPASS (32.768 kHz 方波振盪器) 提供精確時鐘。
所有外設（GPIO、UART、SPI、I²C）透過統一的 `pinmap.h` 與 `boards.c` 管理。

## 系統配置
| 項目 | 設定 |
|------|------|
| MCU | STM32G031K8T6 |
| 系統時鐘 | HSI 16 MHz × PLL ÷ 2 = 64 MHz |
| RTC 時基 | 外部 LSE_BYPASS (32.768 kHz 方波輸入，S3225SMD32.768KOSC) |
| Framework | STM32CubeG0 HAL |
| IDE / Build | PlatformIO + VS Code |
| 燒錄器 | ST-LINK V2 (SWDIO / SWCLK / 3V3 / GND) |

## 專案結構
```
AVIONICS_STD/
├─ src/
│  ├─ main.c          # 主程式入口
│  └─ boards.c        # 時鐘、GPIO、UART、SPI、I²C 初始化
├─ include/
│  ├─ pinmap.h        # 腳位映射與 AF 定義
│  └─ boards.h        # 外設宣告
├─ lib/               # 自訂模組（可選）
├─ platformio.ini     # PIO 設定檔
├─ .gitignore         # Git 忽略清單
└─ README.md
```

## 腳位映射總表
| 功能 | 腳位 | 備註 |
|------|------|------|
| SPI1_MOSI | PA7 | AF0 |
| SPI1_MISO | PA6 | AF0 |
| SPI1_SCK  | PA5 | AF0 |
| SPI1_NSS  | PA4 | GPIO 控制 |
| USART1_TX | PA9 | AF1 |
| USART1_RX | PA10 | AF1 |
| USART2_TX | PA2 | AF1 |
| USART2_RX | PA3 | AF1 |
| I2C1_SCL  | PB6 | AF6 |
| I2C1_SDA  | PB7 | AF6 |
| I2C2_SCL  | PA11 | AF6 |
| I2C2_SDA  | PA12 | AF6 |
| BASIC_IO_LED | PC6 | 通用輸出 |
| LSE_IN | PC14 | 接方波輸出 |
| LSE_OUT | PC15 | 懸空 |
| SWDIO | PA13 | Debug |
| SWCLK | PA14 | Debug |

## 初始化範例
```c
HAL_Init();
LSE_BYPASS_Enable();          // 啟用外部 32.768 kHz 方波
SystemClock_Config();         // 設定 HSI + PLL = 64 MHz

MX_GPIO_BoardInit();          // LED / NSS
MX_USART1_BoardInit(115200,0);
MX_SPI1_BoardInit();
MX_I2C1_BoardInit(100);       // 100 kHz
```

## 編譯與燒錄
1. 開啟 VS Code → PlatformIO → *Open Project* → 選擇本專案資料夾  
2. 接上 ST-LINK  
3. 按 **✓ Build** 編譯  
4. 按 **→ Upload** 燒錄  
5. 若需 UART 監視，在 `platformio.ini` 加入：
   ```ini
   monitor_speed = 115200
   ```
   然後點 **Monitor**

## GitHub 使用流程
```bash
git init
git add .
git commit -m "Initial commit"
git remote add origin https://github.com/<yourname>/AVIONICS_STD.git
git branch -M main
git push -u origin main
```

更新程式後：
```bash
git add .
git commit -m "update: enable LSE and refactor board init"
git push
```

其他成員下載：
```bash
git clone https://github.com/<yourname>/AVIONICS_STD.git
```

## 貢獻指引
1. 每項功能以模組化方式開發（如 `sensor_xx.c` / `sensor_xx.h`）。  
2. 新功能請在新分支開發：
   ```bash
   git checkout -b feature/<module-name>
   ```
3. 維持 `pinmap.h` 為全專案統一腳位表。  
4. 提交前執行 Build 確認無錯誤。

## 授權
MIT License — 可自由修改、再散佈。  
© 淡江大學航電組 2025
