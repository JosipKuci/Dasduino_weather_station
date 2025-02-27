/**************************************************
 *
 * @file        post_request_sender.h
 * @brief       Header file for function prototypes for initializing and checking WiFi connection as well as sending data
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/

#ifndef POST_REQUEST_SENDER_H
#define POST_REQUEST_SENDER_H
#include <WiFi.h>
#include <HTTPClient.h>
void post_request_sender_initialize_wifi();
void post_request_send_data(String sensor_data);
String post_request_get_wifi_status();
#endif