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
//      turnOnLeftToRight(strip1, strip2, topNumLeds, topLedCounter, color);
      turnOnLeftToRightTop(strip1, topLedCounter, color);
      turnOnLeftToRightBottom(strip2, bottomLedCounter, color);
    }

   private:
    void (*finishedPatternCB)();
    int topLedCounter = 0;
    int bottomLedCounter = 0;
    int lightChangeDelay = 500;

    int topNumLeds;
    int bottomNumLeds;

    void turnOnLeftToRightTop(Adafruit_NeoPixel &strip, int &counter, uint32_t color) {
      int topOuter = 7;//50
      int topInner = 10;
      
      EVERY_N_MILLISECONDS(lightChangeDelay) {
        int top[topOuter][topInner] = {
//          //E
//          {4,2,3,4,17},
//          {3,5,16,18},
//          {3,6,15,19},
//          {3,7,14,20},
//          {5,8,9,12,13,21},
//          {5,10,11,12,22,23},
//          //N
//          {9,24,25,26,27,28,29,30,31,32},
//          {1,33},
//          {2,34,35},
//          {2,36,37},
//          {2,38,39},
//          {2,40,41},
//          {1,42},
//          {1,43},
//          {1,44},
//          //V
//          {1,45},
//          {1,46},
//          {1,47},
//          {4,48,49,50,51},
//          {4,52,53,54,55},
//          {1,56},
//          {2,57,58},
          //E
          {2,59,60},
          {1,61},
          {7,62,70,71,72,79,80,81},
          {4,63,69,73,82},
          {4,64,68,74,83},
          {7,65,66,67,75,76,84,85},
          //R
//          {8,86,87,88,89,90,91,92,93},
//          {1,94},
//          {1,95},
//          {1,96},
//          {1,97},
//          {1,98},
//          {6,99,100,101,102,103,104},
//          //U
//          {5,105,106,107,108,109},
//          {1,110},
//          {1,111},
//          {6,112,113,114,115,116,117},
//          {7,118,119,120,121,122,123,124},
//          {1,125},
//          {5,126,127,128,129,130},
//          //S
//          {4,132,133,134,135},
//          {1,136},
//          {3,137,146,147},
//          {3,138,145,148},
//          {3,139,144,149},
//          {2,140,143},
//          {2,141,142}
        };
        turnOnArray(strip, top[counter], color);
        
        counter++;
        Serial.print("counter: ");
        Serial.print(counter);
        Serial.print("\n");
        if (counter > topOuter-1) {
          counter = 0;
          Serial.print("-------End-------");
          Serial.print("\n");
          strip.fill();
        }
        strip.show();
      }
    }

    void turnOnLeftToRightBottom(Adafruit_NeoPixel &strip,int &counter, uint32_t color) {
      int topOuter = 7; //49;
      int topInner = 10;
      
      EVERY_N_MILLISECONDS(lightChangeDelay) {
        int bottom[topOuter][8] = {
//          //E
//          {0},
//          {1,12},
//          {1,13},
//          {1,14},
//          {1,15},
//          {1,16},
//          //N
//          {1,17},
//          {1,18},
//          {3,19,20,21},
//          {1,22},
//          {2,23,24},
//          {2,25,26},
//          {1,27},
//          {1,28},
//          {6,29,30,31,32,33,34},
//          //V
//          {1,35},
//          {3,36,37,38},
//          {3,38,39,40},
//          {2,41,42},
//          {2,43,44},
//          {2,45,46},
//          {3,47,48,49},
          //e
          {7,50,51,52,53,54,55,56},
          {1,57},
          {1,58},
          {1,59},
          {1,60},
          {1,61},
//          //R
//          {1,62},
//          {2,63,64},
//          {2,65,66},
//          {2,67,68},
//          {2,69,70},
//          {1,71},
//          {2,72,73},
//          //U
//          {1,74},
//          {1,75},
//          {1,76},
//          {1,77},
//          {2,78,79},
//          {1,80},
//          {2,81,82},
//          //S
//          {3,83,92,93},
//          {3,84,91,94},
//          {3,85,90,95},
//          {3,86,89,96},
//          {4,87,88,97,98},
//          {2,99,103},
//          {3,100,101,102}
        };
        turnOnArray(strip, bottom[counter], color);
        
        counter++;
        Serial.print("counter: ");
        Serial.print(counter);
        Serial.print("\n");
        if (counter > topOuter-1) {
          counter = 0;
          Serial.print("-------End-------");
          Serial.print("\n");
          strip.fill();
        }
        strip.show();
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
