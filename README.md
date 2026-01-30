# Pan+Tilt Controller
A FreeRTOS application demonstrating servo control on a STM32 Nucleo C031C6 board.

## System
[Wiring Diagram](https://app.cirkitdesigner.com/project/9a58236c-4db8-42aa-8752-c295fa226ef1)
* STM32 Nucleo C031C6
* Tower SG90 Servo (x2)
* Bourns PEC11 Rotary Encoder (x2)

## Firmware
* FreeRTOS
* STM32C0 HAL
* CMSIS6
* Unity
* CMake

## TODO
- [x] Encoder unit tests
- [x] Servo unit tests
- [x] Clean up STM32 init code
- [x] Push encoder button to reset servo position
- [x] Remove BSP layer (LED, UART, blue btn)
- [ ] Remove STM32 FreeRTOS wrapper(s) (e.g. `osDelay(1);` vs `vTaskDelay(1)`)
- [x] Consistent code style
- [ ] Encoder angular velocity
- [ ] Table of tasks names and priorities?
- [ ] TIM2 encoder mode experiment