/*
 * driver_ssd1351.h
 *
 *  Created on: 07.08.2020
 *      Author: Laurin
 */

#ifndef DRIVER_SSD1351_H_
#define DRIVER_SSD1351_H_

#include "stdint.h"
#include "gfx.h"

#define CMD_SET_COLUMN          0x15
#define CMD_SET_ROW             0x75
#define CMD_SET_LINE_START      0xA1
#define CMD_SET_DISPLAY_OFFSET  0xA2
#define CMD_SET_PHASE           0xB1
#define CMD_SET_COMMAND_LOCK    0xFD
#define CMD_SET_BRIGHTNESS      0xC7
#define CMD_SET_DIVIDER         0xB3
#define CMD_WRITE_RAM           0x5C
#define CMD_COLORDEPTH          0xA0
#define CMD_DISPLAY_ALL_OFF     0xA4
#define CMD_DISPLAY_ALL_ON      0xA5
#define CMD_DISPLAY_GDDRAM      0xA6
#define CMD_DISPLAY_INVERT      0xA7
#define CMD_SLEEP_ON            0xAE
#define CMD_SLEEP_OFF           0xAF

typedef void (*write_pin)(uint8_t pinstate);
typedef void (*delay_ptr)(uint32_t delaytime);
typedef void (*spi_transmit)(uint8_t *data, uint32_t len);

typedef struct ssd1351
{
    write_pin pin_rs;
    write_pin pin_cs;
    write_pin pin_dc;
    delay_ptr delay;
    spi_transmit transmit_data;
}s_ssd1351;

extern s_ssd1351 *driver_ssd1351_functions_global;

void driver_ssd1351_init(s_ssd1351 *function_pointers);
void driver_ssd1351_send_something(uint8_t sth, uint8_t dc);
void driver_ssd1351_send_command(uint8_t cmd);
void driver_ssd1351_send_data(uint8_t *data, uint16_t len);
void driver_ssd1351_send_data_single(uint8_t data);
void driver_ssd1351_reset(void);
void driver_ssd1351_memory_clear(void);
void driver_ssd1351_set_cursor_std(void);

#endif /* DRIVER_SSD1351_H_ */
