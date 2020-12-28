#include "Arduino.h"

//bugs:
// can I use fadeToBlackBy here instead of the brightness down?
// the brightness down gets fidgety at the end

class FadeOffThenOn {
  public:
    FadeOffThenOn(
      int numLedsInput,
      uint8_t numRunsInput,
      uint8_t maxBrightnessInput,
      unsigned long stayOnTimeInput,
      void (*finishedCallBack)()) {
      numLeds = numLedsInput;
      maxBrightness = maxBrightnessInput;
      stayOnTime = stayOnTimeInput;
      numRuns = numRunsInput;
      finishedPatternCB = finishedCallBack;

      previousMillis = 0;
    };

    void runPattern(CRGB ledStrip[], CHSV color) {
      unsigned long currentMillis = millis();
      CHSV currentColor = CHSV(color.hue, color.saturation, brightness);
    
      fill_solid(ledStrip, numLeds, currentColor);
      
      EVERY_N_MILLISECONDS(15) {
        if (upDown){
          brightness++;
        } else {
          brightness--;
        }
        if (brightness >= maxBrightness-1){
          brightness = maxBrightness-1;
          if (stayOnTime > 0) {
            if (previousMillis == 0) {
              previousMillis = currentMillis;
            }
            if (currentMillis - previousMillis >= stayOnTime){
              upDown = false;
              previousMillis = 0;
            }
          } else {
            upDown = false;
          }
        }
        if (brightness < 1) {
          upDown = true;
          runCounter++;
          Serial.print("adding in fadeOffThenOn");
          Serial.print("\n");
          if (runCounter == numRuns) {
            finishedPatternCB();
          }
        }
      }
    
      FastLED.show();
    }
  
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    uint8_t maxBrightness;
    unsigned long stayOnTime = 0;
    unsigned long previousMillis;
    bool upDown = true;
    int numLeds;
    uint8_t runCounter = 0;
    uint8_t brightness = 0;
};
