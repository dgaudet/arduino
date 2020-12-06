#include <FastLED.h>

// bugs/new features
// when starting each new function, the starting position might not be correct
// chaser stops randomly, not at the end of a full run, and starts randomly
// tracer starts randomly


#define NUM_LEDS 147
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

uint8_t value = 0;
uint8_t upDown = 0;
bool isRunning = false;

uint8_t functionRunCounter = 0;

uint8_t ledsLit = 0;

CHSV redColor = CHSV(0, 255, 255); // bright red
CHSV blackColor = CHSV(0, 0, 0);

typedef void (*fn)();
static fn animationFunctions[5];

void finishedPattern() {
  fill_solid(leds, NUM_LEDS, CRGB::Black); //set all ledStrip to black once we get to the end
  FastLED.show();
  nextPattern();
}

#include "Chaser.h"
#include "Tracer.h"
#include "TwoSidedOnAndOff.h"
#include "ChaserUsingSawTooth.h"

uint8_t chaserBeat = 0;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.setBrightness(20);

  animationFunctions[0] = twoSidedOnThenOff;
  animationFunctions[1] = fadeOffThenOn;
}

void loop() {
  if (functionRunCounter == 4) {
    functionRunCounter = 0;
    fill_solid(leds, NUM_LEDS, blackColor);
    FastLED.show();
    delay(1000);
    Serial.print("---------Reset--------\n");
  } else if (functionRunCounter == 0) {
    runTwoSidedOnAndOff(2);
  } else if (functionRunCounter == 1) {
    runTracer(3); //need to do this one an extra time since the second time we run this, it skips the first count
  } else if (functionRunCounter == 2) {
    runChaserUsingSawTooth(2); //need to do this one an extra time since the second time we run this, it skips the first count
  } else {
    runChaser(3); 
  }

  EVERY_N_MILLISECONDS(1000) {
    Serial.print(functionRunCounter);
  }
}

void nextPattern() {
  isRunning = false;
  functionRunCounter = functionRunCounter+1;
}

void runTwoSidedOnAndOff(uint8_t numRuns) {
  Serial.print("run two sided on and off");
  Serial.print("\n");
  isRunning = true;
  TwoSidedOnAndOff twoSidedOnAndOff = TwoSidedOnAndOff(NUM_LEDS, numRuns);
  while(isRunning) twoSidedOnAndOff.runPattern(leds);
}

void runTracer(uint8_t numRuns) {
  Serial.print("run tracer");
  Serial.print("\n");
  isRunning = true;
  Tracer tracer = Tracer(NUM_LEDS, numRuns);
  while(isRunning) tracer.runPattern(leds);
}

void runChaser(uint8_t numRuns) {
  Serial.print("run chaser");
  Serial.print("\n");
  isRunning = true;
  Chaser chaser = Chaser(NUM_LEDS, numRuns);
  while(isRunning) chaser.runPattern(leds);
}

void runChaserUsingSawTooth(uint8_t numRuns) {
  Serial.print("run ChaserUsingSawTooth");
  Serial.print("\n");
  isRunning = true;
  ChaserUsingSawTooth chaser = ChaserUsingSawTooth(NUM_LEDS, numRuns);
  while(isRunning) chaser.runPattern(leds);
}

void twoSidedOnThenOff() {
  CHSV color;

  EVERY_N_MILLISECONDS(50) {
    if (value == 0) {
      fill_solid(leds, NUM_LEDS, blackColor);
      FastLED.show();
    }
    if (upDown == 0){
      color = redColor;
      leds[value] = color;
      leds[NUM_LEDS - value -1] = color;
      value++;
    } else {
      color = blackColor;
      leds[value] = color;
      leds[NUM_LEDS - value -1] = color;
      value--;
    }
    if (value > NUM_LEDS/2){
      upDown = 1;
    }
    if (value < 1) {
      upDown = 0;
      functionRunCounter++;   //increment functionRunCounter everytime we make it through one full cycle
      Serial.print("adding in twoSidedOnThenOff");
      Serial.print("\n");
      fill_solid(leds, NUM_LEDS, CRGB::Black); //set all leds to black once we get to the end
    }
    FastLED.show();
  }
}

void fadeOffThenOn() {
  CHSV color = CHSV(0, 255, value);

  fill_solid(leds, NUM_LEDS, color);
  
  EVERY_N_MILLISECONDS(15) {
    if (upDown == 0){
      value++;
    } else {
      value--;
    }
    if (value > 200){
      upDown = 1;
    }
    if (value < 1) {
      upDown = 0;
      functionRunCounter++;   //increment functionRunCounter everytime we make it through one full cycle
      Serial.print("adding in fadeOffThenOn");
      Serial.print("\n");
      fill_solid(leds, NUM_LEDS, CRGB::Black); //set all leds to black once we get to the end
    }
  }

  FastLED.show();
}
