#include "Arduino.h"

class Chaser {
  public:
    Chaser(int numLedsInput) {
      numLeds = numLedsInput;
      sinBeat1 = 0;
    };

    void runPattern(CRGB ledStrip[]);
  private:
    bool upDown = false;
    int counter = 0;
    uint8_t waveSpeedBPM = 10;
    uint8_t sinBeat1;
    int numLeds;
};

void Chaser::runPattern(CRGB ledStrip[]) {
  sinBeat1 = beatsin8(waveSpeedBPM, 0, numLeds-1, 0, 0);
  uint8_t sinBeat2 = sinBeat1 - 1;
  CRGB color;
  if (!upDown) {
    color = CRGB::Red;
  } else {
    color = CRGB::Black;
  }
  if (sinBeat1 == 0) {
    upDown = false;
  }
  if (sinBeat1 == numLeds - 1) {
    upDown = true;
  }

  ledStrip[sinBeat1] = color;
  ledStrip[sinBeat2] = color;

  checkTimer();
  FastLED.show();
  Serial.print("counter:");
  Serial.print(sinBeat1);
  Serial.print("\n");
}
