#include <FastLED.h>

// bugs/new features
// when starting each new function, the starting position might not be correct
// chaser stops randomly, not at the end of a full run, and starts randomly
// tracer starts randomly


#define NUM_LEDS 147
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

bool isRunning = false;
uint8_t functionRunCounter = 0;

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
#include "FadeOffThenOn.h"

uint8_t chaserBeat = 0;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.setBrightness(20);
}

void loop() {
  switch (functionRunCounter) {
    case 0:
      runTwoSidedOnAndOff(2);
      break;
    case 1:
      runTracer(2);
      break;
    case 2:
      runFadeOffThenOn(2);
      break;
    case 3:
      runChaserUsingSawTooth(2);
      break;
    default:
      runChaser(2);
      break;
  }

  EVERY_N_MILLISECONDS(1000) {
    Serial.print(functionRunCounter);
  }
}

void nextPattern() {
  isRunning = false;
  uint8_t numAnimations = 5;
  functionRunCounter = (functionRunCounter+1);
  if(functionRunCounter >= numAnimations) {
    functionRunCounter = 0;
    Serial.print("---------Reset--------\n");
  }
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

void runFadeOffThenOn(uint8_t numRuns) {
  Serial.print("run FadeOffThenOn");
  Serial.print("\n");
  isRunning = true;
  FadeOffThenOn fader = FadeOffThenOn(NUM_LEDS, numRuns);
  while(isRunning) fader.runPattern(leds);
}
