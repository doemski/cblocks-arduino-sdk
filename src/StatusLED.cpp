#include "StatusLED.h"
#include "Arduino.h"

#include <Adafruit_NeoPixel.h>

namespace CBlocks{
  StatusLED::StatusLED(Adafruit_NeoPixel* strip, int statusPixel) : strip(strip), statusPixel(statusPixel){
    strip->begin();
    clear();
  }

  void StatusLED::clear(){
    for(int i = 0; i< strip->numPixels(); i++){
      strip->setPixelColor(i, 0, 0, 0);
    }
    strip->show();
  }

  void StatusLED::connecting(){
    clear();
    strip->setPixelColor(statusPixel, strip->Color(HIGH_VALUE, HIGH_VALUE, 0));
    strip->show();
  }

  void StatusLED::running(){
    strip->setPixelColor(statusPixel, strip->Color(0, HIGH_VALUE, 0));
    strip->show();
  }

  void StatusLED::error(){
    clear();
    strip->setPixelColor(statusPixel, strip->Color(HIGH_VALUE, 0, 0));
    strip->show();
  }

  void StatusLED::pairing(){
    clear();
    strip->setPixelColor(statusPixel, strip->Color(0, 0, HIGH_VALUE));
    strip->show();
  }
}
