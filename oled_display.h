/**************************************************
 *
 * @file        oled_display.h
 * @brief       Header file for function prototypes for initializing and writing data to the oled display
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <OLED-Display-SOLDERED.h>
void oled_display_values_on_screen(String values);
void oled_display_initialize();
#endif