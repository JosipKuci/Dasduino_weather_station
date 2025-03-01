/**************************************************
 *
 * @file        ntp.cpp
 * @brief       maintains the NTP protocol connection and keeps an offline timestamp
 *
 * @copyright GNU General Public License v3.0
 * @authors   Josip Šimun Kuči
 ***************************************************/
#include "ntp.h"
#define INCREMENTATION_VALUE 3 //IF YOU CHANGE THE INTERRUPT PERIOD, CHANGE THIS TO HOW MUCH SECONDS IT IS
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

int h=-1,m=-1,s=-1;

void ntp_initialize()
{
  timeClient.begin(); //Creates a UDP connection with the NTP server
  timeClient.setTimeOffset(3600); //GMT+1
}


/*An offline time tracker so that we dont access the NTP server too often
  IF YOU CHANGE INTERRUPT PERIOD YOU MUST CHANGE S VARIABLE INCREMENTATION*/
void ntp_increment_offline()
{
  if(h!=-1 && m!=-1 && s!=-1)//Check if we made an NTP connection, if not dont keep track of clock
  {
    s+=INCREMENTATION_VALUE; //Since the interrupt is triggered every 3s, we increment the seconds like that also
    if(s>59)
    {
      m++;
      s=s%60;
      if(m>59)
      {
        h++;
        send_analytics(); //Send the data gathered every hour
        m=0;
        if(post_request_get_wifi_status()=="Connected")
        {
        }
        if(h>23)
        {
          h=0;
          ntp_get_current_time(); //We get the time from the server every day for precision (if we are currently connected to WiFi)
        }
      }
    }
  }
}

//Slices the formatted date time we get from the server into hour, minute and second integer values
void format_time_into_h_m_s(String formattedDate)
{
  /*
    Since the date time we get is in the format:
      2024-02-27T16:00:13Z
    we can slice it up into just the time by finding the index of
    the "T" character, after that we know that we can slice it by taking every 2 characters after that
    and ignoring the ":" character
  */
  int T_index=formattedDate.indexOf("T");
  String h_unformatted = formattedDate.substring(T_index+1,T_index+3);
  String m_unformatted = formattedDate.substring(T_index+4,T_index+6);
  String s_unformatted = formattedDate.substring(T_index+7,T_index+9);

  //Converting the sliced strings into integers
  h=h_unformatted.toInt();
  m=m_unformatted.toInt();
  s=s_unformatted.toInt();
}

//Get current time from server
void ntp_get_current_time()
{
  timeClient.update(); 
  String formattedDate = timeClient.getFormattedDate(); //Gets datetime data in form of string

  Serial.println(formattedDate); //Print to serial to check if time is good
  format_time_into_h_m_s(formattedDate); 
}

