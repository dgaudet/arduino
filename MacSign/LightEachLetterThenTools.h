#include "Arduino.h"
#include "Fade.h"

class LightEachLetterThenTools {
  private:
    void (*finishedPatternCB)();
    
    uint8_t numRuns;
    bool upDown = true;
    uint8_t runCounter = 0;
    unsigned long letterStartDelay;
    unsigned long previousMillis = millis();
    uint8_t defaultFadeAmount = 5;

    Fade mFader;
    Fade aFader;
    Fade cFader;
    Fade toolFader;

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
    LightEachLetterThenTools(
      uint8_t numRunsInput,
      uint8_t maxBrightness,
      unsigned long fadeInterval,
      unsigned long letterStartDelayInput,
      void (*finishedCallBack)())
    {
      numRuns = numRunsInput;
      letterStartDelay = letterStartDelayInput;
      finishedPatternCB = finishedCallBack;

      mFader = Fade(0, maxBrightness, fadeInterval, true);
      aFader = Fade(0, maxBrightness, fadeInterval, false);
      cFader = Fade(0, maxBrightness, fadeInterval, false);
      toolFader = Fade(0, maxBrightness, fadeInterval, false);
    };

    void runPattern(uint8_t analogPins[], CRGB ledStrip[], CHSV color){
      unsigned long currentMillis = millis();
      int macFadeAmount = defaultFadeAmount;
      if (!upDown) {
        macFadeAmount = -1 * macFadeAmount;
      }
    
      uint8_t current_mFade = mFader.startFader(macFadeAmount);
      analogWrite(analogPins[0], current_mFade);
      if (currentMillis - previousMillis >= letterStartDelay) {
        analogWrite(analogPins[1], aFader.startFader(macFadeAmount));
      }
      if (currentMillis - previousMillis >= letterStartDelay*2) {
        analogWrite(analogPins[2], cFader.startFader(macFadeAmount));
      }
      if (currentMillis - previousMillis >= letterStartDelay*3) {
        uint8_t tool_fade = toolFader.startFader(macFadeAmount);
        toolsAnimation(ledStrip, tool_fade, color);
      }
      if (currentMillis - previousMillis >= letterStartDelay*5) {
        upDown = false;
      }
      if (current_mFade == 0 && !upDown) {
        finishedPatternCB();
      }
    }
};
