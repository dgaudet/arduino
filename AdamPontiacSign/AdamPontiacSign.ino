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
  nextPattern();
}

#include "Tracer.h"

uint8_t chaserBeat = 0;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.setBrightness(20);

  animationFunctions[0] = twoSidedOnThenOff;
  animationFunctions[1] = tracer;
  animationFunctions[2] = chaserUsingSawToothWave;
  animationFunctions[3] = fadeOffThenOn;
  animationFunctions[4] = chaser;
}

void loop() {
  if (functionRunCounter == 13) {
    functionRunCounter = 0;
    fill_solid(leds, NUM_LEDS, blackColor);
    FastLED.show();
    delay(1000);
    Serial.print("---------Reset--------\n");
  } else if (functionRunCounter < 2) {
    animationFunctions[0]();
  } else if (functionRunCounter > 1 && functionRunCounter < 5) {
    runTracer(3); //need to do this one an extra time since the second time we run this, it skips the first count
  } else if (functionRunCounter > 4 && functionRunCounter < 6) {
    animationFunctions[2](); //need to do this one an extra time since the second time we run this, it skips the first count
  } else if (functionRunCounter > 5 && functionRunCounter < 10) {
    animationFunctions[3]();
    chaserBeat = 0;
  } else {
    animationFunctions[4](); //need to do this one an extra time since the second time we run this, it skips the first count
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
  Serial.print("run tracer dot");
  Serial.print("\n");
  isRunning = true;
  Tracer tracer = Tracer(NUM_LEDS, numRuns);
  while(isRunning) tracer.runPattern(leds);
}

void chaser() {
  // this function will light up all leds one at a time from the start to the end
  // then on the way back it will turn each led off one at a time to the start
  // A sinBeat is the number of the led in the leds array too light up from 0 to number of leds
  // I needed to add 2 sinBeat's because once I started using over 85 leds it was
  // skipping a few numbers I think because it was going through the numbers too fast
  uint8_t waveSpeedBPM = 10;
  chaserBeat = beatsin8(waveSpeedBPM, 0, NUM_LEDS -1, 0, 0);
  uint8_t sinBeat2 = chaserBeat - 1;
  CRGB color;
  if (upDown == 0){
    color = redColor;
  } else {
    color = CRGB::Black;
  }
  if (chaserBeat == 0) {
    upDown = 0;
  }
  if (chaserBeat == NUM_LEDS -1) {
    upDown = 1;
  }
  
  leds[chaserBeat] = color;
  leds[sinBeat2] = color;
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*1.75) {
    functionRunCounter++;
    Serial.print("adding in chaser");
    Serial.print("\n");
  }
}

void tracer() {
  // this one uses a wave where it goes from the start to the end of the strip
  // then back the opposite direction but has a nice tail and fade out effect
  uint8_t waveSpeedBPM = 20;
  uint8_t sinBeat1 = beatsin8(waveSpeedBPM, 0, NUM_LEDS -1, 0, 0);
  uint8_t sinBeat2 = sinBeat1 - 1;
  leds[sinBeat1] = redColor;
  leds[sinBeat2] = redColor;
  
  fadeToBlackBy(leds, NUM_LEDS, 20);
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*2) {
    functionRunCounter++;
    Serial.print("adding in tracer");
    Serial.print("\n");
    fill_solid(leds, NUM_LEDS, CRGB::Black); //set all leds to black once we get to the end
  }
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
