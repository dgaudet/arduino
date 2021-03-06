#include "Arduino.h"

class FadeInAndOut {
  public:
    FadeInAndOut(
      int topNumLedsInput,
      int bottomNumLedsInput
    ) {
      topNumLeds = topNumLedsInput;
      bottomNumLeds = bottomNumLedsInput;
    };

    void runPattern(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, uint32_t color) {
      fadeInAndOut(strip1, topNumLeds, color);
      fadeInAndOut(strip2, bottomNumLeds, color);
    }

  private:
    void (*finishedPatternCB)();
    bool upDown = true;
    int brightness = 0;

    int topNumLeds;
    int bottomNumLeds;

    void fadeInAndOut(Adafruit_NeoPixel &strip, int numLeds, uint32_t color) {
      Serial.print("test");
      Serial.print("\n");
      EVERY_N_MILLISECONDS(10) {
        if (upDown) {
          brightness++;
        } else {
          brightness--;
        }
        
        uint32_t color = strip.Color(0, 0, 0, brightness);
//        uint32_t color = strip.Color(0, 255, 0, 0);
        strip.fill(color, 0, numLeds);
        if (brightness > 250) {
          upDown = false;
          brightness = 100-1;
        }
        if (brightness < 1) {
          upDown = true;
        }
        strip.show();
      }
    }
};
