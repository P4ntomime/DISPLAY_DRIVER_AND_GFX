/*
 * gfx.h
 *
 *  Created on: 07.08.2020
 *      Author: Laurin
 */

#ifndef GFX_H_
#define GFX_H_

#include "stdint.h"
#include "driver_ssd1351.h"

#define DISPLAYBUFFER

#define DISPLAY_ORIENTATION_UP    0
#define DISPLAY_ORIENTATION_DOWN  1
#define DISPLAY_ORIENTATION_LEFT  2
#define DISPLAY_ORIENTATION_RIGHT 3

typedef struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}Color;

typedef struct
{
    Color red;
    Color green;
    Color blue;
    Color cyan;
    Color magenta;
    Color yellow;
    Color black;
    Color white;
    Color gray;
}Colors;

extern Colors colors;

void gfx_std_init(uint8_t orientation);
void gfx_std_screen_clear(Color color);
void gfx_std_draw_pixel(uint8_t x, uint8_t y, Color color, uint8_t drawpixel);
void gfx_std_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color, uint8_t drawline);
void gfx_std_draw_rectangle(uint8_t x, uint8_t y, uint8_t a, uint8_t b, Color color, uint8_t drawrect);
void gfx_std_draw_rectangle_filled(uint8_t x, uint8_t y, uint8_t a, uint8_t b, Color color, uint8_t drawrect);
void gfx_std_draw_circle(uint8_t x, uint8_t y, uint8_t r, Color color, uint8_t drawcirc);
void gfx_std_draw_circle_filled(uint8_t x, uint8_t y, uint8_t r, Color color, uint8_t drawcirc);
void gfx_adv_text(uint8_t x, uint8_t y, char *text, Color color_foreground, Color color_background, uint8_t drawbackground, uint8_t drawtext);
void gfx_std_buffer_send();                                 // sends screen buffer if it is enabled


#endif /* GFX_H_ */
