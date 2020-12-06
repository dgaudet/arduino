#include "Arduino.h"

class TwoSidedOnAndOff {
  public:
    TwoSidedOnAndOff(
      int numLedsInput,
      uint8_t numRunsInput,
      void (*finishedCallBack)())
    {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
      finishedPatternCB = finishedCallBack;
    };

    void runPattern(CRGB ledStrip[], CHSV color);
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    int numLeds;
    uint8_t runCounter = 0;
    bool upDown = true;
    uint8_t brightness = 0;
    CHSV blackColor = CHSV(0, 0, 0);
};

void TwoSidedOnAndOff::runPattern(CRGB ledStrip[], CHSV color) {
  CHSV currentColor = color;
  EVERY_N_MILLISECONDS(50) {
    if (brightness == 0) {
      fill_solid(ledStrip, numLeds, blackColor);
      FastLED.show();
    }
    if (upDown){
      currentColor = color;
      ledStrip[brightness] = currentColor;
      ledStrip[numLeds - brightness -1] = currentColor;
      brightness++;
    } else {
      currentColor = blackColor;
      ledStrip[brightness] = currentColor;
      ledStrip[numLeds - brightness -1] = currentColor;
      brightness--;
    }
    if (brightness > numLeds/2){
      upDown = false;
    }
    if (brightness < 1) {
      upDown = true;
      runCounter++;   //increment functionRunCounter everytime we make it through one full cycle
      Serial.print("adding in twoSidedOnThenOff");
      Serial.print("\n");
      if (runCounter == numRuns) {
        finishedPatternCB();
      }
    }
    FastLED.show();
  }
}
