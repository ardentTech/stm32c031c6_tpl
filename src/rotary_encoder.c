// #include "rotary_encoder.h"
//
// // TODO unit test
// int8_t encoder_read(RotaryEncoder *rot_enc) {
//     static uint8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
//
//     rot_enc->prevNextCode <<= 2;
//     if (HAL_GPIO_ReadPin(rot_enc->dt_port, rot_enc->dt_pin)) { // CLK
//         rot_enc->prevNextCode |= 0x02;
//     }
//     if (HAL_GPIO_ReadPin(rot_enc->clk_port, rot_enc->clk_pin)) { // DT
//         rot_enc->prevNextCode |= 0x01;
//     }
//     // clear 4 MSBs
//     rot_enc->prevNextCode &= 0x0f;
//
//     if (rot_enc_table[rot_enc->prevNextCode]) { // if sequence is valid
//         rot_enc->store <<= 4;
//         rot_enc->store |= rot_enc->prevNextCode;
//         if ((rot_enc->store & 0xff) == 0x2b) {
//             return COUNTER_CLOCKWISE;
//         }
//         if ((rot_enc->store & 0xff) == 0x17) {
//             return CLOCKWISE;
//         }
//     }
//     return 0;
// }
