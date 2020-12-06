#include "Arduino.h"

class ChaserSawTooth {
  public:
    ChaserSawTooth() {};

    void runPattern(CRGB ledStrip[], int numLeds);
  private:
    void loop(CRGB ledStrip[], int numLeds);
};

void ChaserSawTooth::runPattern(CRGB ledStrip[], int numLeds) {
  EVERY_N_MILLISECONDS(20) {
    loop(ledStrip, numLeds);
  }

  checkTimer();
  FastLED.show();
}

void ChaserSawTooth::loop(CRGB ledStrip[], int numLeds) {
  uint8_t waveSpeedBPM = 15;
  uint8_t fadeToBlackSpeed = 45;
  for (uint8_t chaserCount = 0; chaserCount < 12; chaserCount++) {
    uint8_t pos = map(beat8(waveSpeedBPM, chaserCount*330), 0, 255, 0, numLeds -1);
    ledStrip[pos] = CRGB::Blue;
  }

  fadeToBlackBy(ledStrip, numLeds, fadeToBlackSpeed);
}
