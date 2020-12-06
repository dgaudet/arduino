#include <FastLED.h>

#define NUM_LEDS 18
#define LED_PIN 2

CRGB leds[NUM_LEDS];

uint8_t patternCounter = 0;
bool upDown = false;
bool isRunning = false;

void checkTimer(){
  EVERY_N_SECONDS(5) {
    nextPattern();
    Serial.print("pattern:");
    Serial.print(patternCounter);
    Serial.print("\n");
  }
}

#include "MovingDot.h"
#include "Chaser.h"
#include "ChaserSawTooth.h"

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);
}

void loop() {
  Serial.print("----in main loop");
  Serial.print("\n");
  switch (patternCounter) {
    case 0:
      runMovingDot();
      break;
    case 1:
      runChaser();
      break;
    case 2:
      runSawTooth();
      break;
  }
}

void nextPattern() {
  isRunning = false;
  patternCounter = (patternCounter + 1) %2;
}

void runMovingDot() {
  Serial.print("run moving dot");
  Serial.print("\n");
  isRunning = true;
  MovingDot movingDot = MovingDot();
  while(isRunning) movingDot.runPattern(leds, NUM_LEDS);
}

void runChaser() {
  Serial.print("run chaser");
  Serial.print("\n");
  isRunning = true;
  Chaser chaser = Chaser(NUM_LEDS);
  while(isRunning) chaser.runPattern(leds);
}

void runSawTooth() {
  Serial.print("run saw tooth");
  Serial.print("\n");
  
  isRunning = true;
  ChaserSawTooth chaser = ChaserSawTooth();
  while(isRunning) chaser.runPattern(leds, NUM_LEDS);
}
