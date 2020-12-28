#include "Arduino.h"

class Chaser {
  public:
    Chaser(
      int numLedsInput,
      uint8_t numRunsInput,
      void (*finishedCallBack)()) 
    {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
      finishedPatternCB = finishedCallBack;
    };

    void runPattern(CRGB ledStrip[], CHSV ledColor) {
      // this function will light up all leds one at a time from the start to the end
      // then on the way back it will turn each led off one at a time to the start
      CRGB color;

      EVERY_N_MILLISECONDS(25) {
        if (upDown) {
          lightCounter++;
          color = ledColor;
        } else {
          lightCounter--;
          color = CRGB::Black;
        }

        if (lightCounter >= numLeds) {
          upDown = false;
          runCounter++;
          Serial.print("adding in chaser");
          Serial.print("\n");
        }
        if (lightCounter <= 0) {
          upDown = true;
          runCounter++;
          Serial.print("adding in chaser");
          Serial.print("\n");
        }
      }

      if (runCounter == numRuns*2) {
        finishedPatternCB();
      }

      ledStrip[lightCounter] = color;
      FastLED.show();
    }

  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    bool upDown = true;
    int numLeds;
    int lightCounter = 0;
    uint8_t runCounter = 0;
};
