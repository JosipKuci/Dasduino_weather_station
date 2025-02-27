/**************************************************
 *
 * @file        Dasduino_weather_station.ino
 * @brief       Initializes all components, handles timer interrupt and transfers data to oled and post_request components
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#include "oled_display.h"
#include "bme280_sensor.h"
#include "post_request_sender.h"
#define PRESCALER 80 //Prescaler which is divided by the timer clock cycle
hw_timer_t *Timer0_Cfg = NULL; //Instance of a pointer to the hardware timer we'll use for an interrupt

const long interrupt_period = 3000000; //How many times timer should increment before triggering interrupt, currently 3 seconds

volatile bool doesUpdateOled = false; //Boolean that decides if we should refresh the data displayed

int oled_refresh_counter=0; //Count how many times we have refreshed the OLED display

String values_as_string; //Holds formatted data of the sensor readings

//Function is called when the Timer0 interrupt is made
void IRAM_ATTR Timer0_ISR()
{
    doesUpdateOled=true;
}
void Timer0_interrupt_initialize()
{
  /*Timer0 increments upwards at a hertz defined by: PRESCALER/80MHz
    With the PRESCALER set to 80, timer increments every 1us*/
  Timer0_Cfg = timerBegin(0, PRESCALER, true);

  //Attaches an interrupt to the timer in the form of a function called Timer0_ISR
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);

  /*Triggers an interrupt when Timer0 increments to value defined by value of interrupt_period,
    third param decides if interrupt should be repeatable*/
  timerAlarmWrite(Timer0_Cfg, interrupt_period , true);

  //Enables the interrupt
  timerAlarmEnable(Timer0_Cfg);
}

//Used to initialize Serial port, wifi, sensor, display and interrupt
void setup() {
  Serial.begin(9600);
  post_request_sender_initialize_wifi();
  bme280_initialize();
  oled_display_initialize();
  Timer0_interrupt_initialize();
}


void loop() {
  if(doesUpdateOled) //Check if interrupt was triggered
  {
    doesUpdateOled = false;
    values_as_string = bme280_sensor_get_readings_as_string();
    oled_display_values_on_screen(values_as_string);
    oled_refresh_counter++;
    if(oled_refresh_counter>=10) //If display has been refreshed 10 times, also send POST request to server
    {
      post_request_send_data(values_as_string);
      oled_refresh_counter=0; //Reset the refresh counter after sending
    }
  }
}
