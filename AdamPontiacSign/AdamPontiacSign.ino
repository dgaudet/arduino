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
  nextPattern();
}

#include "Chaser.h"
#include "Tracer.h"

uint8_t chaserBeat = 0;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.setBrightness(20);

  animationFunctions[0] = twoSidedOnThenOff;
  animationFunctions[1] = chaserUsingSawToothWave;
  animationFunctions[2] = fadeOffThenOn;
}

void loop() {
  if (functionRunCounter == 5) {
    functionRunCounter = 0;
    fill_solid(leds, NUM_LEDS, blackColor);
    FastLED.show();
    delay(1000);
    Serial.print("---------Reset--------\n");
  } else if (functionRunCounter < 2) {
    animationFunctions[0]();
  } else if (functionRunCounter == 1) {
    runTracer(3); //need to do this one an extra time since the second time we run this, it skips the first count
  } else if (functionRunCounter > 1 && functionRunCounter < 4) {
    animationFunctions[1](); //need to do this one an extra time since the second time we run this, it skips the first count
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

void chaserUsingSawToothWave() {
  // this one kicks off the same sawtooth wave 9 times, just offset by a certain amount
  // of time so they look like they are chasing eachother and as if it goes on forever
  // the number of chaserCount, the second param passed into the beat8 function and
  // the fadeToBlackBy number determine how they work together
  // period of wave 60/bpm *1000
  // so if you have 10 bpm you get 6000ms which means it takes 6sec for the wave to reach the end
  // of the strip
  
  uint8_t waveSpeedBPM = 15;
  uint8_t fadeToBlackSpeed = 45;
  for (uint8_t chaserCount = 0; chaserCount < 12; chaserCount++) {
    uint8_t pos = map(beat8(waveSpeedBPM, chaserCount*330), 0, 255, 0, NUM_LEDS -1);
    leds[pos] = redColor;
  }

  fadeToBlackBy(leds, NUM_LEDS, fadeToBlackSpeed);
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*2) {
    functionRunCounter++;
    Serial.print("adding in chaserUsingSawTooth");
    Serial.print("\n");
  }
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
