#include "Arduino.h"

class TwoSidedOnAndOff {
  public:
    TwoSidedOnAndOff(int numLedsInput, uint8_t numRunsInput) {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
    };

    void runPattern(CRGB ledStrip[]);
  private:
    uint8_t numRuns;
    uint8_t waveSpeedBPM = 20;
    int numLeds;
    uint8_t runCounter = 0;
    bool upDown = true;
    uint8_t brightness = 0;
};

void TwoSidedOnAndOff::runPattern(CRGB ledStrip[]) {
  CHSV color;

  EVERY_N_MILLISECONDS(50) {
    if (brightness == 0) {
      fill_solid(ledStrip, numLeds, blackColor);
    }
    if (upDown){
      color = redColor;
      ledStrip[brightness] = color;
      ledStrip[numLeds - brightness -1] = color;
      brightness++;
    } else {
      color = blackColor;
      ledStrip[brightness] = color;
      ledStrip[numLeds - brightness -1] = color;
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
        finishedPattern();
      }
    }
    FastLED.show();
  }
}
