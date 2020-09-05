/*
 * gfx.c
 *
 *  Created on: 07.08.2020
 *      Author: Laurin
 */

#include "gfx.h"
#include "gfx_internal.h"
#include "gfx_adv_charset.h"
#include <math.h>

#ifdef DISPLAYBUFFER

unsigned char ucDisplayBuff[(128*128*2)];

#endif

uint8_t display_direction = 0;

Colors colors =
{
    //black
    .black.red      = 0x00,//0x1F = maximal value
    .black.green    = 0x00,//0x3F = maximal value
    .black.blue     = 0x00,//0x1F = maximal value

    //gray
    .gray.red       = 0x05,
    .gray.green     = 0x0A,
    .gray.blue      = 0x05,

    //white
    .white.red      = 0x1F,
    .white.green    = 0x3F,
    .white.blue     = 0x1F,

    //red
    .red.red        = 0x3F,
    .red.green      = 0x00,
    .red.blue       = 0x00,

    //green
    .green.red      = 0x00,
    .green.green    = 0x3F,
    .green.blue     = 0x00,

    //blue
    .blue.red       = 0x00,
    .blue.green     = 0x00,
    .blue.blue      = 0x3F,

    //yellow
    .yellow.red     = 0x3F,
    .yellow.green   = 0x3F,
    .yellow.blue    = 0x00,

    //magenta
    .magenta.red    = 0x1F,
    .magenta.green  = 0x00,
    .magenta.blue   = 0x1F,

    //cyan
    .cyan.red       = 0x00,
    .cyan.green     = 0x3F,
    .cyan.blue      = 0x3F

};

/**
 *
 *
 *
 *
 * */
void gfx_std_init(uint8_t orientation)                     // TODO: maybe add some more parameters (if needed)
{
    display_direction = orientation;
}

/**
 *
 *
 *
 *
 * */
void gfx_std_screen_clear(Color color)
{

    uint16_t ctr0 = 0;

#ifdef DISPLAYBUFFER

    for(ctr0 = 0; ctr0 < 32768; ctr0+=2)
    {
        ucDisplayBuff[ctr0 + 0] = (color.blue << 3) | (0x07 & (color.green >> 3));
        ucDisplayBuff[ctr0 + 1] = (color.green << 5) | (0x1F & (color.red));
    }

    gfx_std_buffer_send();

#else

    uint8_t ctr1 = 0;

    for(ctr0 = 0; ctr0 < 128; ctr0++)
    {
        for(ctr1 = 0; ctr1 < 128; ctr1++)
        {
            gfx_std_draw_pixel(ctr0, ctr1, color, 1);
        }
    }

#endif
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_pixel(uint8_t x, uint8_t y, Color color, uint8_t drawpixel)
{

    uint8_t tmp = 0;

    if((x < 128) && (y < 128))      //check if coordinates are legal
    {
        switch(display_direction)
        {
        case DISPLAY_ORIENTATION_UP:

            x = 127 - x;
            y = 127 - y;
            break;

        case DISPLAY_ORIENTATION_DOWN:

            // no change needed here
            break;

        case DISPLAY_ORIENTATION_LEFT:

            tmp = 127 - y;
            y = x;
            x = tmp;
            break;

        case DISPLAY_ORIENTATION_RIGHT:

            tmp = 127 - x;
            x = y;
            y = tmp;
            break;

        default:

            // no change needed here
            break;
        }
    }

#ifdef DISPLAYBUFFER

    if((x < 128) && (y < 128))
    {
        ucDisplayBuff[(x*2) + (y*128*2) + 0] = (color.blue << 3) | (0x07 & (color.green >> 3));     // blue subpixel and first part of green subpixel
        ucDisplayBuff[(x*2) + (y*128*2) + 1] = (color.green << 5) | (0x1F & (color.red));           // second part of green subpixel and red subpixel
    }

    if(drawpixel) gfx_std_buffer_send();

#else

    if((x < 128) && (y < 128))
    {
        driver_ssd1351_send_command(CMD_SET_COLUMN);    // set collumn pointer
        driver_ssd1351_send_data_single(x);
        driver_ssd1351_send_data_single(0x7F);

        driver_ssd1351_send_command(CMD_SET_ROW);       // set row pointer
        driver_ssd1351_send_data_single(y);
        driver_ssd1351_send_data_single(0x7F);

        driver_ssd1351_send_command(CMD_WRITE_RAM);     // write in ram
        driver_ssd1351_send_data_single((color.blue << 3) | (0x07 & (color.green >> 3)));
        driver_ssd1351_send_data_single((color.green << 5) | (0x1F & (color.red)));
    }

#endif
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color, uint8_t drawline)
{
    if((x1 < 128) && (x2 < 128) && (y1 < 128) && (y2 < 128))
    {
        float m = 0;
        int16_t dx = x2 - x1;
        int16_t dy = y2 - y1;
        uint8_t tmp = 0;
        uint8_t ctr0 = 0;

        if(gfx_std_get_bigger_difference(dx, dy))
        {
            if(x1 > x2)
            {
                tmp = x1;
                x1 = x2;
                x2 = tmp;
                tmp = y1;
                y1 = y2;
                y2 = tmp;
            }

            m = (y1 - y2) / (x1 - x2);
            for(ctr0 = 0; ctr0 <= (x2 - x1); ctr0++)
            {
                gfx_std_draw_pixel(x1 + ctr0, y1 + (ctr0 * m), color, 0);
            }
        }
        else
        {
            if(y1 > y2)
            {
                tmp = x1;
                x1 = x2;
                x2 = tmp;
                tmp = y1;
                y1 = y2;
                y2 = tmp;
            }

            m = (x1 - x2) / (y1 - y2);
            for(ctr0 = 0; ctr0 <= (y2 - y1); ctr0++)
            {
                gfx_std_draw_pixel(x1 + (ctr0 * m), y1 + ctr0, color, 0);
            }
        }
        if(drawline)gfx_std_buffer_send();
    }
}

/**
 *
 *
 *
 *
 * */
uint8_t gfx_std_get_bigger_difference(int16_t dx, int16_t dy)
{
    if(dx < 0) dx = dx * -1;
    if(dy < 0) dy = dy * -1;

    if(dx > dy) return 1;   // return 1 if x difference is bigger than y differnece
    if(dy > dx) return 0;   // return 0 if y differnece is bigger than x differnece
    if (dx == dy) return 1; // reutrn 1 if x differnece is same as y differnrece (direction doesen't matter)
    return 1;   // return 1 to shut up compiler warning
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_rectangle(uint8_t x, uint8_t y, uint8_t a, uint8_t b, Color color, uint8_t drawrect)
{
    uint8_t ctr = 0;

    for(ctr = 0; ctr < a; ctr++)
        gfx_std_draw_pixel(x + ctr, y, color, 0);       // bottom line of rectangle
    for(ctr = 0; ctr < b; ctr++)
        gfx_std_draw_pixel(x + a, y + ctr, color, 0);   // right line of rectangle
    for(ctr = a; ctr > 0; ctr--)
        gfx_std_draw_pixel(x + ctr, y + b, color, 0);   // upper line of rectangle
    for(ctr = b; ctr > 0; ctr--)
        gfx_std_draw_pixel(x, y + ctr, color, 0);       // left line of rectangle

    if(drawrect) gfx_std_buffer_send();
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_rectangle_filled(uint8_t x, uint8_t y, uint8_t a, uint8_t b, Color color, uint8_t drawrect)
{
    uint8_t aCtr = 0;
    uint8_t bCtr = 0;


    for(bCtr = 0; bCtr < b; bCtr++)
    {
        for(aCtr = 0; aCtr < a; aCtr++)
        {
            gfx_std_draw_pixel(x + aCtr, y + bCtr, color, 0);
        }
    }

    if(drawrect) gfx_std_buffer_send();
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_circle(uint8_t x, uint8_t y, uint8_t r, Color color, uint8_t drawcirc)
{
    if(r == 0) return;

    uint8_t ctr0 = 0;

    uint8_t tmp = 0;

    r -= 1;

    for(ctr0 = 0; ctr0 < r; ctr0++)
    {
        tmp = (uint8_t)gfx_std_round(sqrtf((r*r) - (ctr0*ctr0)));
        gfx_std_draw_pixel(x - tmp, y + ctr0, color, 0);
        gfx_std_draw_pixel(x - ctr0, y + tmp, color, 0);
        gfx_std_draw_pixel(x + ctr0, y + tmp, color, 0);
        gfx_std_draw_pixel(x + tmp, y + ctr0, color, 0);
        gfx_std_draw_pixel(x + tmp, y - ctr0, color, 0);
        gfx_std_draw_pixel(x + ctr0, y - tmp, color, 0);
        gfx_std_draw_pixel(x - ctr0, y - tmp, color, 0);
        gfx_std_draw_pixel(x - tmp, y - ctr0, color, 0);
    }

    if(drawcirc) gfx_std_buffer_send();
}

/**
 *
 *
 *
 *  FIXME: when circle in vicinity of 0 in either x or y (or both), stripes form. This is due to using uint instead of int. Suggest checking if value goes below zero and only drawing to zero if sth like that happens
 * */
void gfx_std_draw_circle_filled(uint8_t x, uint8_t y, uint8_t r, Color color, uint8_t drawcirc)
{
    if(r == 0) return;

    uint8_t ctr0 = 0;

    uint8_t tmp = 0;

    r -= 1;

    for(ctr0 = 0; ctr0 < r; ctr0++)
    {
        tmp = (uint8_t)gfx_std_round(sqrtf((r * r) - (ctr0 * ctr0)));
//        gfx_std_draw_line(x - tmp, y + ctr0, x + tmp, y + ctr0, color, 0);
        gfx_std_draw_line_horizontal(x - tmp, x + tmp, y + ctr0, color, 0);
//        gfx_std_draw_line(x - tmp, y - ctr0, x + tmp, y - ctr0, color, 0);
        gfx_std_draw_line_horizontal(x - tmp, x + tmp, y - ctr0, color, 0);
//        gfx_std_draw_line(x + ctr0, y - tmp, x + ctr0, y + tmp, color, 0);
        gfx_std_draw_line_vertical(x + ctr0, y - tmp, y + tmp, color, 0);
//        gfx_std_draw_line(x - ctr0, y - tmp, x - ctr0, y + tmp, color, 0);
        gfx_std_draw_line_vertical(x - ctr0, y - tmp, y + tmp, color, 0);
    }

    if(drawcirc) gfx_std_buffer_send();
}

/**
 *
 *
 *
 *
 * */
float gfx_std_round(float val)
{

    val = val + 0.5;

    return val;
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_line_vertical(uint8_t x, uint8_t y1, uint8_t y2, Color color, uint8_t drawline)
{
    uint8_t tmp = 0;

    if(y1 > y2)
    {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    while(y1 < y2)
    gfx_std_draw_pixel(x, y1++, color, 0);

    if(drawline) gfx_std_buffer_send();
}

/**
 *
 *
 *
 *
 * */
void gfx_std_draw_line_horizontal(uint8_t x1, uint8_t x2, uint8_t y, Color color, uint8_t drawline)
{
    uint8_t tmp = 0;

    if(x1 > x2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    while(x1 < x2)
    gfx_std_draw_pixel(x1++, y, color, 0);

    if(drawline) gfx_std_buffer_send();
}

/**
 *
 *
 *
 *
 * */
void gfx_std_buffer_send()                                 // sends screen buffer if it is enabled
{

#ifdef DISPLAYBUFFER

    driver_ssd1351_set_cursor_std();

    driver_ssd1351_send_command(CMD_WRITE_RAM);

    driver_ssd1351_functions_global->pin_cs(0);
    driver_ssd1351_functions_global->pin_dc(1);

    driver_ssd1351_functions_global->transmit_data(ucDisplayBuff, (128*128*2));

    driver_ssd1351_functions_global->pin_cs(1);

#endif
}

/**
 *
 *
 *
 *
 * */
uint8_t gfx_adv_char(uint8_t x, uint8_t y, char c, Color color_foreground, Color color_background, uint8_t drawbackground, uint8_t drawchar)
{
    uint8_t RowCtr = 0;
    uint8_t ColCtr = 0;
    uint8_t ArrPos = 0;
    uint8_t nextPos;

    if(c <= 'Z' && c >= 'A') {
        ArrPos = c - 'A';
    }
    else if(c <= 'z' && c >= 'a') {
        ArrPos = c - 'a' + 26;
    }
    else if(c <= '9' && c >= '0') {
        ArrPos = c -'0' + 52;
    }
    else if(c == '.') {
        ArrPos = 64;
    }
    else if(c == '%') {
        ArrPos = 63;
    }
    else if(c == '*') {
        ArrPos = 62;
    }
    else {  //unknown character
        ArrPos = 65;
    }

    for(RowCtr = 0; RowCtr < 14; RowCtr++)
    {
        for(ColCtr = 0; ColCtr < 11; ColCtr++)
        {
            if(c != ' ')
            {
                if(chars_all[ArrPos].character[RowCtr][ColCtr]) gfx_std_draw_pixel(x + ColCtr, y + 13 - RowCtr, color_foreground, 0);
                else if(drawbackground) gfx_std_draw_pixel(x + ColCtr, y + 13 - RowCtr, color_background, 0);
            }
            else
            {
                gfx_std_draw_pixel(x + ColCtr, y + 13 - RowCtr, color_background, 0);
            }
        }
    }

    if(c != ' ')
    {
        nextPos = chars_all[ArrPos].to_next_char;
    }
    else
    {
        nextPos = 5;
    }

    if(drawchar) gfx_std_buffer_send();

    return nextPos;
}

/**
 *
 *
 *
 *
 * */
void gfx_adv_text(uint8_t x, uint8_t y, char *text, Color color_foreground, Color color_background, uint8_t drawbackground, uint8_t drawtext)
{
    uint8_t x_origin = x;

    uint8_t nextPos = 0;

    while(*text)
    {

        nextPos = gfx_adv_char(x, y, *text++, color_foreground, color_background, drawbackground, 0);
        if(nextPos + x < 127)
        {
            x += nextPos;
        }
        else
        {
            y -= 13;
            x = x_origin;
        }
    }
    if(drawtext)
    gfx_std_buffer_send();
}
