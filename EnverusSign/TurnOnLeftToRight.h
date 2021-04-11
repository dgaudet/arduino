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
      int outerLength = 9;
      int innerLength = 6;
      int top2[outerLength][innerLength] = {};
      
      int bottom[outerLength][innerLength] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {12,12,12},
        {13,13,13},
        {14,14,14},
        {15,15,15},
        {16,16,16},
        {17,17,17},
        {18,18,18},
        {19,19,19},
        {9,12,12},
        {10,11,10}
      };

//      strip2.setPixelColor(5, color);
//      strip2.show();
      
      EVERY_N_MILLISECONDS(500) {
        int top[outerLength][innerLength] = {
          {0,0,0,0,0,0},
          {1,1,1,1,1,1},
          {2,3,4,17,17,17},
          {5,16,16,18,18,18},
          {6,15,15,19,19,19},
          {7,14,14,20,20,20},
          {8,9,12,13,21,21},
          {10,11,12,22,23,23},
          {24,25,26,27,28,28}
        };
        
        turnOnArray(strip1, top[counter], innerLength, color);
//        turnOnArray(strip2, bottom[counter], 3, color);
        
        counter++;
        Serial.print("counter: ");
        Serial.print(counter);
        Serial.print("\n");
        if (counter > outerLength) {
          counter = 0;
          strip1.fill();
          strip2.fill();
        }
        strip1.show();
        strip2.show();
      }
    }

    void turnOnArray(Adafruit_NeoPixel &strip, int lights[], int columns, uint32_t color) {
      int inner;
      for(inner = 0; inner < columns; inner++) {
          int pixel = lights[inner];
          strip.setPixelColor(pixel, color);
          Serial.print("pixel: ");
          Serial.print(lights[inner]);
          Serial.print("\n");
        }
        Serial.print("\n----------\n");
    }
};
