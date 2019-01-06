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
  The aim of this class is to provide simple horizontal and vertical progress
  bar functionality for OLED screens compatible with Arduino and the 
  Adafruit_SSD1306 library.
--------------------------------------------------------------------------------
VERSION HISTORY
--------------------------------------------------------------------------------
  VERSION         DATE         AUTHOR                DESCRIPTION
  -------         ----         ------                -----------
  1.0             06/01/19     J. Ingram-Wright      Initial version
--------------------------------------------------------------------------------
EXTRA NOTES
--------------------------------------------------------------------------------
  Installation of Adafruit_SSD1306 and Adafruit_GFX is necessary.
------------------------------------------------------------------------------*/


#ifndef _PROGRESS_BAR_h
#define _PROGRESS_BAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum Orientation
{
  HORIZONTAL,
  VERTICAL
};

class ProgressBar
{
  // Functions.
  public:
    explicit ProgressBar(Adafruit_SSD1306 * display, 
                         const int kXAxisPosition,
                         const int kYAxisPosition,
                         const int kWidth, const int kHeight, 
                         const int kValueMinimum,
                         const int kValueMaximum,
                         const Orientation kOrientation = HORIZONTAL);

    void update(const int value);

  // Functions.
  private:
    void drawHorizontalProgress(const int value);

    void drawVerticalProgress(const int value);


  // Variables and Constants.
  private:
    // Pointer to Display Instance.
    Adafruit_SSD1306 * display_;

    // Axis Properties.
    const int kWidth_,         kHeight_;
    const int kXAxisPosition_, kYAxisPosition_;

    // Value Properties.
    const int kValueMinimum_;
    const int kValueMaximum_;

    const Orientation kOrientation_;
};

#endif