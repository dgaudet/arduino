#include "Arduino.h"

class Tracer {
  public:
    Tracer(int numLedsInput, uint8_t numRuns) {
      numLeds = numLedsInput;
    };

    void runPattern(CRGB ledStrip[]);
  private:
    uint8_t numRuns;
    bool upDown = false;
    uint8_t waveSpeedBPM = 10;
    int numLeds;
    uint8_t runCounter = 0;
};

void Tracer::runPattern(CRGB ledStrip[]) {
  // this one uses a wave where it goes from the start to the end of the strip
  // then back the opposite direction but has a nice tail and fade out effect
  uint8_t waveSpeedBPM = 20;
  uint8_t sinBeat1 = beatsin8(waveSpeedBPM, 0, numLeds -1, 0, 0);
  uint8_t sinBeat2 = sinBeat1 - 1;
  ledStrip[sinBeat1] = redColor;
  ledStrip[sinBeat2] = redColor;
  
  fadeToBlackBy(ledStrip, numLeds, 20);
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*2) {
    runCounter++;
    Serial.print("adding in tracer");
    Serial.print("\n");
    if (runCounter = numRuns) {
      fill_solid(ledStrip, numLeds, CRGB::Black); //set all ledStrip to black once we get to the end
      finishedPattern();
    }
  }
}
