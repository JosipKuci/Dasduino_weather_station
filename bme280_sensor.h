/**************************************************
 *
 * @file        bme280_sensor.h
 * @brief       Header file for function prototypes for bme280 sensor initializing and string formatting
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H
#include <BME280-SOLDERED.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
String bme280_sensor_get_readings_as_string();
String bme280_sensor_get_readings_as_json();
void bme280_initialize();
#endif