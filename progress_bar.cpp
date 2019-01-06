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

#include "progress_bar.h"

ProgressBar::ProgressBar(Adafruit_SSD1306 * display, 
                         const int kXAxisPosition,
                         const int kYAxisPosition,
                         const int kWidth, const int kHeight, 
                         const int kValueMinimum,
                         const int kValueMaximum,
                         const Orientation kOrientation = HORIZONTAL)
  : display_(display),
    kWidth_(kWidth),
    kHeight_(kHeight),
    kXAxisPosition_(kXAxisPosition),
    kYAxisPosition_(kYAxisPosition),
    kValueMinimum_(kValueMinimum),
    kValueMaximum_(kValueMaximum),
    kOrientation_(kOrientation)
{
  // Left blank intentionally.
}

void ProgressBar::update(const int value)
{    
  if (kOrientation_ == HORIZONTAL)
  {
    drawHorizontalProgress(value);
  }
  else
  {
    drawVerticalProgress(value);
  }
  
  display_->drawRect(kXAxisPosition_, kYAxisPosition_, kWidth_, kHeight_, WHITE); 
}

void ProgressBar::drawHorizontalProgress(const int value)
{
  int progresstoshow = map(value, kValueMinimum_, kValueMaximum_, 0, kWidth_);

  display_->fillRect(kXAxisPosition_, kYAxisPosition_, progresstoshow, kHeight_, 
                     WHITE);
}
void ProgressBar::drawVerticalProgress(const int value)
{
  int progresstoshow = map(value, kValueMinimum_, kValueMaximum_, 0, kHeight_);
  int conpensatedyaxisposition = (kYAxisPosition_ + kHeight_) - progresstoshow;

  display_->fillRect(kXAxisPosition_, conpensatedyaxisposition, kWidth_,
                     progresstoshow, WHITE);
}