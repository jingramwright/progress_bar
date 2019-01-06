/*-----------------------------------------------------------------------------
                                               
                   ____  _________  ____ _________  __________
                  / __ \/ ___/ __ \/ __ `/ ___/ _ \/ ___/ ___/
                 / /_/ / /  / /_/ / /_/ / /  /  __(__  |__  ) 
                / .___/_/   \____/\__, /_/   \___/____/____/  
               /_/              _/____/                       
                               / /_  ____ ______              
                              / __ \/ __ `/ ___/              
                             / /_/ / /_/ / /                  
                            /_.___/\__,_/_/        
            
--------------------------------------------------------------------------------
OVERVIEW
--------------------------------------------------------------------------------
  The purpose of this file is to provide a working example of an instance of
  the ProgressBar class.
--------------------------------------------------------------------------------
VERSION HISTORY
--------------------------------------------------------------------------------
  VERSION         DATE         AUTHOR                DESCRIPTION
  -------         ----         ------                -----------
  1.0             06/01/19     J. Ingram-Wright      Initial version
--------------------------------------------------------------------------------
EXTRA NOTES
--------------------------------------------------------------------------------
  N/A
------------------------------------------------------------------------------*/


#include <progress_bar.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// ProgressBar properties.
const int kProgressBarMinimumValue = - 20;
const int kProgressBarMaximumValue =  100;

const int kProgressBarHXPosition =   4;
const int kProgressBarHYPosition =  27;
const int kProgressBarHWidth     =  90;
const int kProgressBarHHeight    =  10;

const int kProgressBarVXPosition = 116;
const int kProgressBarVYPosition =   4;
const int kProgressBarVWidth     =  10;
const int kProgressBarVHeight    =  56;

// Create two instances of ProgressBar to be drawn on the display.
ProgressBar progressbarh(&display, kProgressBarHXPosition, 
                         kProgressBarHYPosition,  kProgressBarHWidth, 
                         kProgressBarHHeight, kProgressBarMinimumValue, 
                         kProgressBarMaximumValue);
ProgressBar progressbarv(&display, kProgressBarVXPosition, 
                         kProgressBarVYPosition,  kProgressBarVWidth, 
                         kProgressBarVHeight, kProgressBarMinimumValue, 
                         kProgressBarMaximumValue, VERTICAL);

// For display update timing.
const int   kUpdateInterval = 20;
signed long previousmillis = 0;

// Value to be displayed.
int progressvalue = -20;
int incrementvalue = 1;

void setup()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (true); //Display not connected. Don't proceed, loop forever.
  }

  display.clearDisplay();
  
  display.display();
}

void updateProgressValue()
{
      if (progressvalue >= 100)
    {
      progressvalue = -20;

      if (incrementvalue >= 10)
      {
        incrementvalue = 1;
      }
      else
      {
        incrementvalue++;
      }
    }
    else
    {
      if ((progressvalue + incrementvalue) > 100)
      {
        progressvalue = 100;
      }
      else
      {
        progressvalue += incrementvalue;
      }
    }
}

void loop()
{
  unsigned long currentmillis = millis();

  if (currentmillis - previousmillis >= kUpdateInterval)
  {
    previousmillis = currentmillis;

    display.clearDisplay();
    progressbarh.update(progressvalue);
    progressbarv.update(progressvalue);
    display.display();

    updateProgressValue();
  }
}