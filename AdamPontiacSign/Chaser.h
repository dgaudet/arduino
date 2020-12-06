#include "Arduino.h"

class Chaser {
  public:
    Chaser(int numLedsInput, uint8_t numRunsInput) {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
    };

    void runPattern(CRGB ledStrip[]);
  private:
    uint8_t numRuns;
    bool upDown = false;
    uint8_t waveSpeedBPM = 10;
    int numLeds;
    uint8_t runCounter = 0;
    uint8_t chaserBeat = 0;
};

void Chaser::runPattern(CRGB ledStrip[]) {
  // this function will light up all leds one at a time from the start to the end
  // then on the way back it will turn each led off one at a time to the start
  // A sinBeat is the number of the led in the leds array too light up from 0 to number of leds
  // I needed to add 2 sinBeat's because once I started using over 85 leds it was
  // skipping a few numbers I think because it was going through the numbers too fast
  uint8_t waveSpeedBPM = 10;
  chaserBeat = beatsin8(waveSpeedBPM, 0, NUM_LEDS -1, 0, 0);
  uint8_t sinBeat2 = chaserBeat - 1;
  CRGB color;
  if (upDown){
    color = redColor;
  } else {
    color = CRGB::Black;
  }
  if (chaserBeat == 0) {
    upDown = false;
  }
  if (chaserBeat == NUM_LEDS -1) {
    upDown = true;
  }
  
  ledStrip[chaserBeat] = color;
  ledStrip[sinBeat2] = color;
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*1.75) {
    runCounter++;
    Serial.print("adding in chaser");
    Serial.print(runCounter);Serial.print(" : ");Serial.print(numRuns);
    Serial.print("\n");
    if (runCounter == numRuns) {
      finishedPattern();
    }
  }
}
