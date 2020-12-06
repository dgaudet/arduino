#include "Arduino.h"

//bugs:
// can I use fadeToBlackBy here instead of the brightness down?
// the brightness down gets fidgety at the end

class FadeOffThenOn {
  public:
    FadeOffThenOn(
      int numLedsInput,
      uint8_t numRunsInput,
      void (*finishedCallBack)()) {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
      finishedPatternCB = finishedCallBack;
    };

    void runPattern(CRGB ledStrip[], CHSV color);
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    bool upDown = true;
    int numLeds;
    uint8_t runCounter = 0;
    uint8_t brightness = 0;
};

void FadeOffThenOn::runPattern(CRGB ledStrip[], CHSV color) {
  CHSV currentColor = CHSV(color.hue, color.saturation, brightness);

  fill_solid(ledStrip, numLeds, currentColor);
  
  EVERY_N_MILLISECONDS(15) {
    if (upDown){
      brightness++;
    } else {
      brightness--;
    }
    if (brightness > 200){
      upDown = false;
    }
    if (brightness < 1) {
      upDown = true;
      runCounter++;
      Serial.print("adding in fadeOffThenOn");
      Serial.print("\n");
      if (runCounter == numRuns) {
        finishedPatternCB();
      }
    }
  }

  FastLED.show();
}
