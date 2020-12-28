#include "Arduino.h"

class Tracer {
  public:
    Tracer(
      int numLedsInput,
      uint8_t numRunsInput,
      void (*finishedCallBack)())
    {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
      finishedPatternCB = finishedCallBack;
    };

    void runPattern(CRGB ledStrip[], CHSV color) {
      // this one uses a wave where it goes from the start to the end of the strip
      // then back the opposite direction but has a nice tail and fade out effect
      EVERY_N_MILLISECONDS(7) {
        if (upDown) {
          lightCounter++;
        } else {
          lightCounter--;
        }

        if (lightCounter >= numLeds) {
          upDown = false;
          runCounter++;
          Serial.print("adding in tracer");
          Serial.print("\n");
        }
        if (lightCounter <= 0) {
          upDown = true;
          runCounter++;
          Serial.print("adding in tracer");
          Serial.print("\n");
        }
      }

      if (runCounter == numRuns*2) {
        finishedPatternCB();
      }

      ledStrip[lightCounter] = color;
      fadeToBlackBy(ledStrip, numLeds, 20);
      FastLED.show();
    }

  private:
    void (*finishedPatternCB)();

    boolean upDown = true;
    uint8_t numRuns;
    uint8_t waveSpeedBPM = 20;
    int lightCounter = 0;
    int numLeds;
    uint8_t runCounter = 0;
};
