/**************************************************
 *
 * @file        analytics.h
 * @brief       prototypes of functions that send average values of sensor readings
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#ifndef ANALYTICS_H
#define ANALYTICS_H
#include "post_request_sender.h"
void send_analytics();
void add_reading_to_analytics_sum(float temperature, float humidity, float pressure);
#endif