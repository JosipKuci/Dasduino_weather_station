/**************************************************
 *
 * @file        ntp.h
 * @brief       prototypes of functions that initialize and maintain the NTP protocol connection
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#ifndef NTP_H
#define NTP_H
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "post_request_sender.h"
#include "analytics.h"
void ntp_get_current_time();
void ntp_initialize();
void ntp_increment_offline();
#endif