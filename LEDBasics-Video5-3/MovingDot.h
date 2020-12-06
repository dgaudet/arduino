#include "Arduino.h"

class MovingDot {
  public:
    MovingDot() {};

    void runPattern(CRGB ledStrip[], int numLeds);
  private:
    void pattern(CRGB ledStrip[], int numLeds);
};

void MovingDot::runPattern(CRGB ledStrip[], int numLeds) {
  EVERY_N_MILLISECONDS(20) {
    pattern(ledStrip, numLeds);
  }

  checkTimer();
  FastLED.show();
}

void MovingDot::pattern(CRGB ledStrip[], int numLeds) {
  uint16_t posBeat  = beatsin16(30, 0, numLeds -1, 0, 0);
  uint16_t posBeat1 = beatsin16(60, 0, numLeds -1, 0, 0);

  uint16_t posBeat3 = beatsin16(30, 0, numLeds -1, 0, 32767);
  uint16_t posBeat4 = beatsin16(60, 0, numLeds -1, 0, 32767);

  // Wave for LED color
  uint8_t colBeat = beatsin8(45, 0, 255, 0, 0);

  ledStrip[(posBeat + posBeat1) /2] = CHSV(colBeat, 255, 255);
  ledStrip[(posBeat3 + posBeat4) /2] = CHSV(colBeat, 255, 255);

  fadeToBlackBy(ledStrip, numLeds, 10);
}
