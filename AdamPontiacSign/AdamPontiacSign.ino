#include <FastLED.h>
#include "Chaser.h"
#include "Tracer.h"
#include "TwoSidedOnAndOff.h"
#include "ChaserUsingSawTooth.h"
#include "FadeOffThenOn.h"

// number of lights
// 32 lights across the top plus the 2 frame holding pieces
// 100 for the entire V

#define NUM_LEDS 132
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
uint8_t MAX_BRIGHTNESS = 255;
uint8_t ANIMATION_REPEATS = 2;

bool isRunning = false;
uint8_t functionRunCounter = 0;
CHSV redColor = CHSV(0, 255, 255); // bright red

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.setBrightness(MAX_BRIGHTNESS);
//  FastLED.setBrightness(40);
  fill_solid(leds, 20, CRGB::Black);
  FastLED.show();
}

void loop() {
  switch (functionRunCounter) {
    case 0:
      runTwoSidedOnAndOff(ANIMATION_REPEATS);
      break;
    case 1:
      runTracer(ANIMATION_REPEATS);
      break;
    case 2:
      runFadeOffThenOn(ANIMATION_REPEATS, 1000);
      break;
    case 3:
      runChaserUsingSawTooth(ANIMATION_REPEATS);
      break;
    case 4:
      runChaser(ANIMATION_REPEATS);
      break;
    default:
      runFadeOffThenOn(1, 20000);
      break;
  }
}

void finishedPattern() {
  fill_solid(leds, NUM_LEDS, CRGB::Black); //set all ledStrip to black once we get to the end
  FastLED.show();
  nextPattern();
}

void nextPattern() {
  isRunning = false;
  uint8_t numAnimations = 6;
  functionRunCounter = functionRunCounter+1;
  if(functionRunCounter >= numAnimations) {
    functionRunCounter = 0;
    Serial.print("---------Reset--------\n");
  }
}

void runTwoSidedOnAndOff(uint8_t numRuns) {
  Serial.print("run two sided on and off");
  Serial.print("\n");
  isRunning = true;
  TwoSidedOnAndOff twoSidedOnAndOff = TwoSidedOnAndOff(NUM_LEDS, numRuns, finishedPattern);
  while(isRunning) twoSidedOnAndOff.runPattern(leds, redColor);
}

void runTracer(uint8_t numRuns) {
  Serial.print("run tracer");
  Serial.print("\n");
  isRunning = true;
  Tracer tracer = Tracer(NUM_LEDS, numRuns, finishedPattern);
  while(isRunning) tracer.runPattern(leds, redColor);
}

void runChaser(uint8_t numRuns) {
  Serial.print("run chaser");
  Serial.print("\n");
  isRunning = true;
  Chaser chaser = Chaser(NUM_LEDS, numRuns, finishedPattern);
  while(isRunning) chaser.runPattern(leds, redColor);
}

void runChaserUsingSawTooth(uint8_t numRuns) {
  Serial.print("run ChaserUsingSawTooth");
  Serial.print("\n");
  isRunning = true;
  ChaserUsingSawTooth chaser = ChaserUsingSawTooth(NUM_LEDS, numRuns, finishedPattern);
  while(isRunning) chaser.runPattern(leds, redColor);
}

void runFadeOffThenOn(uint8_t numRuns, unsigned long stayOnDelay) {
  Serial.print("run FadeOffThenOn");
  Serial.print("\n");
  isRunning = true;
  FadeOffThenOn fader = FadeOffThenOn(NUM_LEDS, numRuns, MAX_BRIGHTNESS, stayOnDelay, finishedPattern);
  while(isRunning) fader.runPattern(leds, redColor);
}
