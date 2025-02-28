/**************************************************
 *
 * @file        analytics.cpp
 * @brief       keeps and modifies data about average readings of sensors
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#include "analytics.h"

float temp_sum=0, humi_sum=0, press_sum=0;
int num_of_readings=0;

//Resets the values after they are printed each hour
void reset_analytics_values()
{
  temp_sum=0;
  press_sum=0;
  humi_sum=0;
  num_of_readings=0;
}

/*Calculates average temerature, humidity and pressure by dividing the sums with the number of readings
  formats them into a json object that we serialize into a string and send the values as a POST request */
void send_analytics()
{
  String formatted_analytics;
  if(num_of_readings != 0) //Just in case a full hour passes before we had the first reading so we dont divide by zero
  {
    float average_temp=temp_sum/num_of_readings;
    float average_humi = humi_sum/num_of_readings;
    float average_press = press_sum/num_of_readings;
    
    StaticJsonDocument<4> json_data;
    json_data["Type"]="Average values for last hour";
    json_data["Average Temperature"]=average_temp;
    json_data["Average Humidity"]=average_humi;
    json_data["Average Pressure"]=average_press;
    serializeJson(json_data, formatted_analytics); //Writes the json object into the formatted_analytics string
    post_request_send_data(formatted_analytics);
  }
  reset_analytics_values();
}

//Gets value of each reading from sensor and puts them in a sum, also keeps track of number of readings
void add_reading_to_analytics_sum(float temperature, float humidity, float pressure)
{
  temp_sum+=temperature;
  humi_sum+=humidity;
  press_sum+=pressure;
  num_of_readings++;
}

