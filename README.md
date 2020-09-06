# Project overview
This is a display driver and basic graphics for a 128x128 OLED screen with an SSD1351 controller chip.

# USING THE LIBRARY
The project is based on an STM32F107VC, but can be adapted to any MCU with an SPI interface and 2 GPIOs (MOSI, SCK, CS, RST, D/C).\
If you are using an STM32 MCU you can open the project in CubeMX and easily change the MCU. \
Otherwise you need to copy the **OLED** folder into your project and include the **oled_lib_tbz.h** file in your main file or wherever you need it.\
Before you can use the commands you need to create following functions: SPI, pin_cs, pin_rs, pin_dc, delay\
```C
void delay_ms(uint32_t period)  // delay in milliseconds
{
    HAL_Delay(period);
}

void pin_cs(uint8_t pinstate)   // changes the CS (chipselect) pinstate to the given value (0 -> CS = 0; >=1 -> CS = 1)
{
    HAL_GPIO_WritePin(GPIOA, OLED_CS, pinstate);
}

void pin_dc(uint8_t pinstate)   // changes the DC (data / command) pinstate to the given value (0 -> DC = 0; >=1 -> DC = 1)
{
    HAL_GPIO_WritePin(GPIOA, OLED_DC, pinstate);
}

void pin_rs(uint8_t pinstate)   // changes the RS (oled reset) pinstate to the given value (0 -> RS = 0; >=1 -> RS = 1)
{
    HAL_GPIO_WritePin(GPIOA, OLED_RESET, pinstate);
}

void transmit_data(uint8_t *data, uint32_t len)   // sends data with length len over SPI
{
    HAL_SPI_Transmit(&hspi1, data, len, 1000);
}
```
After creating the functions you need to create a new function pointer variable and assign them to it.

```C
    s_ssd1351 function_pointers;        // create new function pointer variable

    // assign the functions to the function pointer variables
    function_pointers.pin_cs = pin_cs;  
    function_pointers.pin_rs = pin_rs;
    function_pointers.pin_dc = pin_dc;
    function_pointers.transmit_data = transmit_data;
    function_pointers.delay = delay_ms;
```
You may now initialize the display with the **oled_init** function.

```C
oled_init(&function_pointers, DISPLAY_ORIENTATION_UP);
```

# GFX
The graphics are just basics like plotting dots, drawing lines, rectangles or circles and a simple text output.

To make drawing bigger things on the screen faster it is recommended to use the displaybuffer, which can be enabled or disabled by commenting / uncommenting the **#define DISPLAYBUFFER** line in the **gfx.h** file. Beware that the displaybuffer takes up 32768 bytes (128x128x2) and may also needs to be disabled to save memory.

Some known bugs and issues:
* filled circle glitching when drawn area reaches below-zero-coordinates (this is due to how the filling of the circle is calculated)
* spacing between letters in text may not be correct and has not been tested (can be changed in the **gfx_adv_charset.h** file by changing the **.to_next_char** value (distance in pixels))

# DRIVER
It is a very basic driver for the SSD1351 chip which mainly handles its reset and plotting dots.\
The driver chip itsself supports more options and customizations, which were not needed for my initial usage of it (MiniWS repo) and thus not implemented.
