/**************************************************
 *
 * @file        oled_display.cpp
 * @brief       Functions for initializing and writing to the display
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#include "oled_display.h"
#include "post_request_sender.h"
OLED_Display oled_display = OLED_Display();
void oled_display_initialize()
{
  /*Initializes an I2C communication with the display on address 0x3C
    And defines it as a 128x64 display*/
  if(!oled_display.begin()) //Check if the display was found
  {
    Serial.println("Error: Display not connected");
  }
}

void oled_display_values_on_screen(String sensor_values)
{
  oled_display.clearDisplay();              //Clears the previous screen
  oled_display.setTextSize(1);              // Normal 1:1 pixel scale
  oled_display.setTextColor(SSD1306_WHITE); // Draw white text
  oled_display.setCursor(0, 0);             // Start at top-left corner
  oled_display.println(sensor_values);      //Display the sensor values in the form of a string
  oled_display.println("WiFi stat: "+ post_request_get_wifi_status()); //Displays the status of the WiFi connection onto the display
  oled_display.display();
}