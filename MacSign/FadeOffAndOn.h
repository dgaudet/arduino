#include "Arduino.h"

class FadeOffAndOn {
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    bool upDown = true;
    uint8_t runCounter = 0;
    uint8_t maxBrightness;
    unsigned long fadeInterval;
    uint8_t currentBrightness = 0;
    uint8_t defaultFadeAmount = 5;

    void toolsAnimation(CRGB toolLeds[], uint8_t brightness, CHSV initialColor) {
      CHSV color = CHSV(initialColor.hue, initialColor.saturation, brightness);
      
      //top line
      colorSection(toolLeds, color, 0, 8);
      colorSection(toolLeds, color, 10, 14);
      colorSection(toolLeds, color, 15, 16);
      colorSection(toolLeds, color, 19, 22);
    
      //right side
      colorSection(toolLeds, color, 24, 25);
    
      //bottom
      colorSection(toolLeds, color, 27, 34);
      colorSection(toolLeds, color, 36, 39);
      colorSection(toolLeds, color, 41, 44);
      colorSection(toolLeds, color, 46, 48);
      colorSection(toolLeds, color, 50, 52);
      FastLED.show();
    }

    void colorSection(CRGB ledStrip[], CHSV color, uint8_t first, uint8_t last) {
      for(uint8_t ledCounter = first; ledCounter <= last; ledCounter ++) {
        ledStrip[ledCounter] = color;
      }
    }

  public:
    FadeOffAndOn(
      uint8_t numRunsInput,
      uint8_t maxBrightnessInput,
      unsigned long fadeIntervalInput,
      void (*finishedCallBack)()) {
      numRuns = numRunsInput;
      maxBrightness = maxBrightnessInput;
      finishedPatternCB = finishedCallBack;
      fadeInterval = fadeIntervalInput;
    };

    void runPattern(uint8_t analogPins[], CRGB ledStrip[], CHSV color){
      int macFadeAmount = defaultFadeAmount;
      if (!upDown) {
        macFadeAmount = -1 * macFadeAmount;
      }

      EVERY_N_MILLISECONDS(fadeInterval) {
        currentBrightness = currentBrightness + macFadeAmount;
        Serial.print(currentBrightness);
        Serial.print("\n");

        for (int pinCounter = 0; pinCounter <= sizeof(analogPins); pinCounter++) {
          analogWrite(analogPins[pinCounter], currentBrightness);
        }
        toolsAnimation(ledStrip, currentBrightness, color);
      
        if (currentBrightness >= maxBrightness-macFadeAmount) {
          upDown = false;
        }
        if (currentBrightness == 0 && !upDown) {
          upDown = true;
          runCounter++;
          if (runCounter >= numRuns) {
            finishedPatternCB();
          }
        }
      }
    }
};
