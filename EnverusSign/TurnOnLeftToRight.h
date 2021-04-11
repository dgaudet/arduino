#include "Arduino.h"

class TurnOnLeftToRight {
  public:
    TurnOnLeftToRight(
      int topNumLedsInput,
      int bottomNumLedsInput
    ) {
      topNumLeds = topNumLedsInput;
      bottomNumLeds = bottomNumLedsInput;
    };

    void runPattern(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, uint32_t color) {
      turnOnLeftToRight(strip1, strip2, topNumLeds, topLedCounter, color);
    }

   private:
    void (*finishedPatternCB)();
    bool upDown = true;
    int topLedCounter = 0;
    int bottomLedCounter = 0;

    int topNumLeds;
    int bottomNumLeds;

    void turnOnLeftToRight(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, int numLeds, int &counter, uint32_t color) {
      int topOuter = 24;
      int topInner = 10;
      
      EVERY_N_MILLISECONDS(300) {
        int top[topOuter][topInner] = {
          //E
          {4,2,3,4,17},
          {3,5,16,18},
          {3,6,15,19},
          {3,7,14,20},
          {5,8,9,12,13,21},
          {5,10,11,12,22,23},
          //N
          {9,24,25,26,27,28,29,30,31,32},
          {1,33},
          {2,34,35},
          {2,36,37},
          {2,38,39},
          {2,40,41},
          {1,42},
          {1,43},
          {1,44},
          //V
          {1,45},
          {1,46},
          {1,47},
          {4,48,49,50,51},
          {4,52,53,54,55},
          {1,56},
          {2,57,58},
          //E
          {2,59,60}
        };
        turnOnArray(strip1, top[counter], color);

        int bottom[topOuter][8] = {
          //E
          {0},
          {1,12},
          {1,13},
          {1,14},
          {1,15},
          {1,16},
          //N
          {1,17},
          {1,18},
          {3,19,20,21},
          {1,22},
          {2,23,24},
          {2,25,26},
          {1,27},
          {1,28},
          {6,29,30,31,32,33,34},
          //V
          {1,35},
          {3,36,37,38},
          {3,38,39,40},
          {2,41,42},
          {2,43,44},
          {2,45,46},
          {3,47,48,49},
          //e
          {7,50,51,52,53,54,55,56}
        };
        turnOnArray(strip2, bottom[counter], color);
        
        counter++;
        Serial.print("counter: ");
        Serial.print(counter);
        Serial.print("\n");
        if (counter > topOuter-1) {
          counter = 0;
          Serial.print("-------End-------");
          Serial.print("\n");
          strip1.fill();
          strip2.fill();
        }
        strip1.show();
        strip2.show();
      }
    }

    void turnOnArray(Adafruit_NeoPixel &strip, int lights[], uint32_t color) {
      int inner;
      int columns = lights[0];
      for(inner = 1; inner <= columns; inner++) {
          int pixel = lights[inner];
          strip.setPixelColor(pixel, color);
          Serial.print("pixel: ");
          Serial.print(lights[inner]);
          Serial.print("\n");
        }
        Serial.print("\n----------\n");
    }
};
