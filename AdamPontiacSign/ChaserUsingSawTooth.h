#include "Arduino.h"

class ChaserUsingSawTooth {
  public:
    ChaserUsingSawTooth(
      int numLedsInput,
      uint8_t numRunsInput,
      void (*finishedCallBack)())
    {
      numLeds = numLedsInput;
      numRuns = numRunsInput;
      finishedPatternCB = finishedCallBack;
    };

    void runPattern(CRGB ledStrip[], CHSV color) {
      // this one kicks off the same sawtooth wave 9 times, just offset by a certain amount
      // of time so they look like they are chasing eachother and as if it goes on forever
      // the number of chaserCount, the second param passed into the beat8 function and
      // the fadeToBlackBy number determine how they work together
      // period of wave 60/bpm *1000
      // so if you have 10 bpm you get 6000ms which means it takes 6sec for the wave to reach the end
      // of the strip
      
      uint8_t fadeToBlackSpeed = 45;
      for (uint8_t chaserCount = 0; chaserCount < 12; chaserCount++) {
        uint8_t pos = map(beat8(waveSpeedBPM, chaserCount*330), 0, 255, 0, numLeds -1);
        ledStrip[pos] = color;
      }
    
      fadeToBlackBy(ledStrip, numLeds, fadeToBlackSpeed);
      FastLED.show();
    
      int timeForOneFullWave = (60/waveSpeedBPM)*1000;
      EVERY_N_MILLISECONDS(timeForOneFullWave*2) {
        runCounter++;
        Serial.print("adding in chaserUsingSawTooth");
        Serial.print("\n");
        if (runCounter == numRuns) {
          finishedPatternCB();
        }
      }
    }
    
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    uint8_t waveSpeedBPM = 15;
    int numLeds;
    uint8_t runCounter = 0;
};
