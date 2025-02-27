# Dasduino Weather Station
A weather station made using the Dasuino CONNECTPLUS (ESP32) board, BME280 sensor and OLED I2C White 0.96" SSD1306 display

## Features
-Read data from sensor at a user-specified amount (by default every 3s)  
-Display the sensor data onto the OLED display  
-Every 10 screen refreshes, send a POST request to a user-specified url (by default every 30s)  

## How to set up

### Connecting
The sensor and display were connected to the board via the easyC connector, which uses the I2C communication protocol  
To be able to easily use the Arduino IDE with Dasduino boards, Download and install the [Dasduino Board Definitions for Arduino IDE](https://github.com/SolderedElectronics/Dasduino-Board-Definitions-for-Arduino-IDE) by following the steps in the repository  

### External libraries
All of the libraries were imported by downloading them from their respective repositories in a .zip format and included into the Arduino IDE by going to **Sketch->Include Library->Add .ZIP Library**  
Used libraries:  
[Soldered OLED Display Arduino Library](https://github.com/SolderedElectronics/Soldered-OLED-Display-Arduino-Library/tree/main)  
[Soldered BME280 and BME680 EasyC Arduino library](https://github.com/SolderedElectronics/Soldered-BME280-BME680-Gas-Sensor-Arduino-Library/tree/main)  

Libraries used that are already included with the Arduino IDE:  
[WiFi](https://github.com/arduino-libraries/WiFi)  
[HTTPClient](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient)  

### Setting variable values
To be able to send POST requests, the board must make a WiFi connection  
You must set the values of your access point into the post_request_sender.cpp file here:
```c
  //Define the network you wish to use
  const char* ssid = "ENTER_YOUR_SSID_HERE";
  const char* password = "ENTER_YOUR_PASSWORD_HERE";
```

Also define the url to which you want to send the requests by changing the serverName variable in the same file:
```c
  //Define the url where the POST request will be made
  String serverName = "ENTER_URL_WHERE_REQUEST_WILL_BE_SENT_HERE";
```

You can also change the interval when data is being fetched/displayed by changing the value of the interrupt_period variable in Dasduino_weather_station.ino:
```c
  const long interrupt_period = 3000000; //How many times timer should increment before triggering interrupt, currently 3 seconds
```
Intervals can also be modified by changing the PRESCALER macro in the same file, see more about ESP32 Timer interrupts here: [ESP32 Timers & Timer Interrupt Tutorial (Arduino IDE)](https://deepbluembedded.com/esp32-timers-timer-interrupt-tutorial-arduino-ide/)

The number of OLED refreshes before a POST request can also be changed by changing the REFRESHES_BEFORE_POST_REQUEST macro:  

```c
  #define REFRESHES_BEFORE_POST_REQUEST 10 //How many times should the screen refresh before sending a POST request
```

## Output
Every time the sensor data is read, it is formatted into a string like this:
```
  Temperature: xx.xx C

  Pressure: xxxx.xx hPa

  Humidity: xx.xx %
```
Data is sent like that in the POST request as a text/plain content type.

The display adds an extra line which shows the currents status of the Wifi connection, for example:
```
  Temperature: 20.86 C

  Pressure: 1005.88 hPa

  Humidity: 42.06 %

  WiFi stat: Connected
```

## Error handling & Debugging
### OLED Display
If the OLED display is not connected/detected, a message is sent over the serial port : "Error: Display not connected"  
The program continues normally and still sends POST requests

### Sensor
If the sensor is not connected, when trying to access data, it will show all of it as 0. If that is detected, instead of the normal output, the OLED and POST request will display:
```
  Bad sensor readings, check connection
```
The board will still try to read data from the sensor in case it reconnects

### WiFi
The board checks if the wifi status is connected every time it tries to send a POST request, if it is not connected it tries to restablish a connection every 30s  
The current status of the WiFi is also shown on the OLED display and refreshed every 3s (or how the user defines the oled display refresh interval). The display and sensor work regardless if the WiFi works or not

### HTTP requests
Everytime a POST request is made, the response code is stored into the httpResponseCode variable and displayed on the serial monitor, negative values mean an error client side


