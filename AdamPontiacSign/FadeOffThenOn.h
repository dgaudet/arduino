#include "Arduino.h"

class FadeOffThenOn {
  public:
    FadeOffThenOn(int numLedsInput, uint8_t numRunsInput) {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
    };

    void runPattern(CRGB ledStrip[]);
  private:
    uint8_t numRuns;
    bool upDown = true;
    uint8_t waveSpeedBPM = 10;
    int numLeds;
    uint8_t runCounter = 0;
    uint8_t chaserBeat = 0;
    uint8_t brightness = 0;
};

void FadeOffThenOn::runPattern(CRGB ledStrip[]) {
  CHSV color = CHSV(0, 255, brightness);

  fill_solid(ledStrip, numLeds, color);
  
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
        finishedPattern();
      }
    }
  }

  FastLED.show();
}
