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

    void runPattern(CRGB ledStrip[], CHSV color);
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    uint8_t waveSpeedBPM = 20;
    int numLeds;
    uint8_t runCounter = 0;
};

void Tracer::runPattern(CRGB ledStrip[], CHSV color) {
  // this one uses a wave where it goes from the start to the end of the strip
  // then back the opposite direction but has a nice tail and fade out effect
  uint8_t sinBeat1 = beatsin8(waveSpeedBPM, 0, numLeds -1, 0, 0);
  uint8_t sinBeat2 = sinBeat1 - 1;
  ledStrip[sinBeat1] = color;
  ledStrip[sinBeat2] = color;
  
  fadeToBlackBy(ledStrip, numLeds, 20);
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*2) {
    runCounter++;
    Serial.print("adding in tracer");
    Serial.print("\n");
    if (runCounter == numRuns) {
      finishedPatternCB();
    }
  }
}
