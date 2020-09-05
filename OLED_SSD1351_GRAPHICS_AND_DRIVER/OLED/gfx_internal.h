/*
 * gfx_internal.h
 *
 *  Created on: 07.08.2020
 *      Author: Laurin
 */

#ifndef GFX_INTERNAL_H_
#define GFX_INTERNAL_H_

#include "stdint.h"

uint8_t gfx_std_get_bigger_difference(int16_t dx, int16_t dy);                      // returns which of the two is bigger, needed for line calculation
float   gfx_std_round(float val);                                                   // very simple round function (for conversion to integer)
void    gfx_std_draw_line_vertical(uint8_t x, uint8_t y1, uint8_t y2, Color color, uint8_t drawline);   //faster and simpler line functions for the filled circle function
void    gfx_std_draw_line_horizontal(uint8_t x1, uint8_t x2, uint8_t y, Color color, uint8_t drawline);
uint8_t gfx_adv_char(uint8_t x, uint8_t y, char c, Color foreground_color, Color background_color, uint8_t drawbackground, uint8_t drawchar);  // draw a single char, needed for gfx_adv_text function, doesn't need to be public

#endif /* GFX_INTERNAL_H_ */
