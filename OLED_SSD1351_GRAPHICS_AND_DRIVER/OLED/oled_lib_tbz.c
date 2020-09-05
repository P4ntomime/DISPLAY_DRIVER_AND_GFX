/*
 * oled_lib_tbz.c
 *
 *  Created on: 08.08.2020
 *      Author: Laurin
 */

#include "oled_lib_tbz.h"

void oled_init(s_ssd1351 *function_pointer, uint8_t orientation)
{
    driver_ssd1351_init(function_pointer);

    gfx_std_init(orientation);
}
