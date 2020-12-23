#include "Arduino.h"

class LeftToRightScroller {
  private:
    void (*finishedPatternCB)();

    int numLeds;
    uint8_t numRuns;
    uint8_t maxBrightness;
    bool leftRight = true;
    uint8_t letterCounter = 0;
    uint8_t leftCounter = 0;
    uint8_t runCounter = 0;

    void colorSection(CRGB ledStrip[], CHSV color, uint8_t first, uint8_t last) {
      for(uint8_t ledCounter = first; ledCounter <= last; ledCounter ++) {
        ledStrip[ledCounter] = color;
      }
    }
  
  public:
    LeftToRightScroller(
      int numLedsInput,
      uint8_t numRunsInput,
      uint8_t brightness,
      void (*finishedCallBack)())
    {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
      maxBrightness = brightness;
      finishedPatternCB = finishedCallBack;
    };

    void runPattern(uint8_t analogPins[], CRGB ledStrip[], CHSV color) {
      CHSV blackColor = CHSV(0, 0, 0);
      CHSV currentColor = color;
      uint8_t currentBrightness = maxBrightness;
    
      EVERY_N_MILLISECONDS(150) {
        if (leftRight) {
          currentBrightness = maxBrightness;
        } else {
          currentBrightness = 0;
        }
        analogWrite(analogPins[letterCounter], currentBrightness);
        letterCounter++; 
      }
      
      EVERY_N_MILLISECONDS(25) {
        if (leftRight) {
          currentColor = color;
        } else {
          currentColor = blackColor;
        }
        colorSection(ledStrip, currentColor, 0, leftCounter);
        colorSection(ledStrip, currentColor, numLeds-4 - leftCounter, numLeds-1);
        
        if (leftCounter > numLeds/2-5) {
          leftRight = !leftRight;
          leftCounter = 0;
          letterCounter = 0;
          runCounter++;
          if (runCounter >= numRuns*2) {
            Serial.print("------finished pattern-----\n");
            finishedPatternCB();
          }
        }
        leftCounter++;
        Serial.print(leftCounter);
        Serial.print("\n");
      }
      
      FastLED.show();
    }
};
