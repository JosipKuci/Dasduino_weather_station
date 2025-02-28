/**************************************************
 *
 * @file        post_request_sender.cpp
 * @brief       Initializes and gets status of WiFi connection, sends a HTTP 
 * @brief       POST request of sensor data to server
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#include "post_request_sender.h"

//Define the network you wish to use
const char* ssid = "ENTER_YOUR_SSID_HERE";
const char* password = "ENTER_YOUR_PASSWORD_HERE";

HTTPClient http;

//Define the url where the POST request will be made
String serverName = "ENTER_URL_WHERE_REQUEST_WILL_BE_SENT_HERE";


void post_request_sender_initialize_wifi()
{
  WiFi.begin(ssid, password); //Initializes the WiFi library's network settings and provides the current status.
}


void post_request_send_data(String sensor_data)
{
  if(WiFi.status()==WL_CONNECTED) //Check if the WiFi is connected before attempting to send a request
  {
    http.begin(serverName);//Opens port 80 for TCP communication and tries to make connection with server
    http.addHeader("Content-Type", "application/json"); //Adds what content type we want to send in the request body
    int httpResponseCode = http.POST(sensor_data); //Send a post request to the server and save responce code in variable
    Serial.println("HTTP:"+String(httpResponseCode));//Print the response to the serial monitor
    http.end(); // After the payload, closes the TCP connection
  }
  else //If we aren't connected, retry connecting
  {
    post_request_sender_initialize_wifi();
  }
}

//Returns current wifi status in form of a string
String post_request_get_wifi_status()
{
  switch(WiFi.status())
  {
    case WL_CONNECTED:
      return "Connected";
    case WL_CONNECT_FAILED:
      return "Failed";
    case WL_CONNECTION_LOST:
      return "Lost";
    case WL_NO_SSID_AVAIL:
      return "No SSID";
    case WL_DISCONNECTED:
      return "Failed";
    default:
      return "Unknown";
  }
}



