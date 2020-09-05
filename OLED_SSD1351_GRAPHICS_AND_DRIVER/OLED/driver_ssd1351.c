/*
 * driver_ssd1351.c
 *
 *  Created on: 07.08.2020
 *      Author: Laurin
 */

#include "driver_ssd1351.h"

s_ssd1351 *driver_ssd1351_functions_global;

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_init(s_ssd1351 *function_pointers)
{
    if(function_pointers == 0) return;

    driver_ssd1351_functions_global = function_pointers;

    driver_ssd1351_reset();

    driver_ssd1351_functions_global->pin_cs(1);
    driver_ssd1351_functions_global->delay(1000);    // display needs some time after reset

    driver_ssd1351_send_command(CMD_SET_COMMAND_LOCK);
    driver_ssd1351_send_data_single(0xB1);

    driver_ssd1351_send_command(CMD_SET_DIVIDER);
    driver_ssd1351_send_data_single(0xF0);

    driver_ssd1351_send_command(CMD_COLORDEPTH);
    driver_ssd1351_send_data_single(0x60);

    driver_ssd1351_send_command(CMD_SET_LINE_START);
    driver_ssd1351_send_data_single(0x00);

    driver_ssd1351_send_command(CMD_SET_DISPLAY_OFFSET);
    driver_ssd1351_send_data_single(0x00);

    driver_ssd1351_send_command(CMD_SET_BRIGHTNESS);
    driver_ssd1351_send_data_single(0x0F);

    driver_ssd1351_set_cursor_std();    // set the standard cursor

    driver_ssd1351_memory_clear();      // clear display memory before displaying it

    driver_ssd1351_send_command(CMD_DISPLAY_GDDRAM);    // displays memory of display (black because cleared)
    driver_ssd1351_send_command(CMD_SLEEP_OFF);         // gets display out of sleep mode
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_send_something(uint8_t sth, uint8_t dc)
{
    driver_ssd1351_functions_global->pin_cs(0);
    driver_ssd1351_functions_global->pin_dc(dc);             //set dc pin to command
    driver_ssd1351_functions_global->transmit_data(&sth, 1);
    driver_ssd1351_functions_global->pin_cs(1);
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_send_command(uint8_t cmd)
{
    driver_ssd1351_functions_global->pin_cs(0);
    driver_ssd1351_functions_global->pin_dc(0);             //set dc pin to command
    driver_ssd1351_functions_global->transmit_data(&cmd, 1);
    driver_ssd1351_functions_global->pin_cs(1);
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_send_data(uint8_t *data, uint16_t len)
{
    driver_ssd1351_functions_global->pin_cs(0);
    driver_ssd1351_functions_global->pin_dc(1);             //set dc pin to data
    driver_ssd1351_functions_global->transmit_data(data, len);
    driver_ssd1351_functions_global->pin_cs(1);
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_send_data_single(uint8_t data)
{
    driver_ssd1351_functions_global->pin_cs(0);
    driver_ssd1351_functions_global->pin_dc(1);             //set dc pin to data
    driver_ssd1351_functions_global->transmit_data(&data, 1);
    driver_ssd1351_functions_global->pin_cs(1);
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_reset(void)
{
    driver_ssd1351_functions_global->pin_rs(1);
    driver_ssd1351_functions_global->pin_rs(0);
    driver_ssd1351_functions_global->delay(1000);
    driver_ssd1351_functions_global->pin_rs(1);
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_memory_clear(void)
{
    driver_ssd1351_set_cursor_std();

    driver_ssd1351_send_command(CMD_WRITE_RAM);

    for(uint16_t i = 0; i < 32768; i++)
    {
        driver_ssd1351_send_data_single(0x00);
    }
}

/**
 *
 *
 *
 *
 * */
void driver_ssd1351_set_cursor_std(void)
{
    uint8_t TxBuff[2] = { 0 , 0 };

    TxBuff[0] = 0x00;
    TxBuff[1] = 127;
    driver_ssd1351_send_command(CMD_SET_COLUMN);
    driver_ssd1351_send_data(TxBuff, 2);

    TxBuff[1] = 127;
    driver_ssd1351_send_command(CMD_SET_ROW);
    driver_ssd1351_send_data(TxBuff, 2);
}
