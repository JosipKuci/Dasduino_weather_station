/**************************************************
 *
 * @file        bme280_sensor.cpp
 * @brief       Initializes, reads data from bme280 sensor, and formats the values into string
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/

#include "bme280_sensor.h"
BME280 bme280; 

/* The sensor isn't factory calibrated, 
   if readings are off, add an offest value */
float offset=0;

float temperature,pressure,humidity;

/*Uses the standard begin method from Soldered bme280 library
  Starts an I2C communication with the sensor by checking each I2C address*/
void bme280_initialize()
{
  bme280.begin();
}

void bme280_sensor_get_readings()
{
  bme280.readSensorData(temperature,humidity,pressure);//Reads the sensor value of the temperature, humidity and pressure sensor and converts it to C,%,hPa respectively

  temperature+=offset;//We add the user defined offset to the temperature

  add_reading_to_analytics_sum(temperature, humidity, pressure);
}

//Checks values of sensor data, returns false if there is an invalid reading, true if readings are fine
bool bme280_sensor_check_connection()
{
  /*
  If a connection isnt established, the sensor sends back 0 for all values.
  Since a pressure of 0hPa is only possible at absolute zero, we can assume that the readings are invalid
  */
  if(temperature==0 && humidity==0 && pressure==0)
  {
    return false;
  }
  return true;
}



/*
Formats the data so that it is ready to display,
Returns if readings are valid:
Temperature: xx.xx C

Pressure: xxxx.xx hPa

Humidity: xx.xx %
*/
String bme280_sensor_get_readings_as_string()
{
  String formatted_data;
  bme280_sensor_get_readings();
  if(bme280_sensor_check_connection())
  {
    formatted_data =      "Temperature: " + String(temperature) + " C\n\n" + 
                          "Pressure: " + String(pressure) + " hPa\n\n" + 
                          "Humidity: " + String(humidity) + " %\n";
  }
  else
  {
    formatted_data="Bad sensor readings, check connection";
  }
  return formatted_data;
}

/*Takes a new reading and formats it as a json object,
  Then converts it into a string that follows json format
  (Could have just written a string that follows json format, 
    but I personally found this way much more readable)*/
String bme280_sensor_get_readings_as_json()
{
  StaticJsonDocument<4> json_data;
  if(bme280_sensor_check_connection())
  {
    json_data["Temperature"]=temperature;
    json_data["Pressure"]=pressure;
    json_data["Humidity"]=humidity;
  }
  else
  {
    json_data["error"]="Bad sensor readings, check connection";
  }
  String serialized_json;
  serializeJson(json_data, serialized_json); //Writes the json object into the serialized_json string
  return serialized_json;
}