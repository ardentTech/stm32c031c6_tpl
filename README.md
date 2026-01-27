# Pan+Tilt Controller
A FreeRTOS application demonstrating servo control on a STM32 Nucleo C031c6 board.

## System
TODO diagram

## Hardware
* STM32 Nucleo C031C6
* Tower SG90 Servo (x2)
* Rotary Encoder (x2)

## Firmware
* FreeRTOS
* STM32C0 HAL
* CMSIS6
* Unity
* CMake

## TODO
- [x] Encoder unit tests
- [x] Servo unit tests
- [ ] TIM2 encoder mode
- [ ] Clean up STM32 init code
- [ ] Push encoder button to reset servo position
- [ ] Remove BSP layer (LED, UART, blue btn)
- [ ] Remove STM32 FreeRTOS wrapper(s) (e.g. `osDelay(1);` vs `vTaskDelay(1)`)
- [ ] Consistent code style
- [ ] Unit test mocks?
- [ ] Encoder angular velocity
- [ ] Table of tasks names and priorities