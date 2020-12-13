#include "Fade.h"

// using 450 ma at 255 brightness full white strip
// using 178 ma at 100 brightness full white strip

//using 275 ma at 100 brightness both colors on 
//using 746 ma at 255 brightness both colors on 
#define M_DATA_PIN 11
#define A_DATA_PIN 9
//#define C_DATA_PIN 9
//#define TOOLS_DATA_PIN 9

uint8_t brightness = 0;
uint8_t maxBrightness = 100;
unsigned long letterFadeInterval = 50;
unsigned long letterStartDelay = 1000;
bool upDown = true;
unsigned long previousMillis = 0;

Fade mFader = Fade(0, maxBrightness, letterFadeInterval);
Fade aFader = Fade(0, maxBrightness, letterFadeInterval);
//Fade cFader = Fade(0, maxBrightness, letterFadeInterval);
//Fade toolsFader = Fade(0, maxBrightness, letterFadeInterval);

void setup() {
  pinMode(M_DATA_PIN, OUTPUT);
  pinMode(A_DATA_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  fadeClass();
}

void fadeClass() {
  unsigned long currentMillis = millis();
  int fadeAmount = 5;
  if (!upDown) {
    fadeAmount = -5;
  }

  uint8_t current_mFade = mFader.startFader(fadeAmount);
  analogWrite(M_DATA_PIN, current_mFade);
  if (currentMillis - previousMillis >= letterStartDelay) {
    analogWrite(A_DATA_PIN, aFader.startFader(fadeAmount));
  }
//  if (currentMillis - previousMillis >= letterStartDelay*2) {
//    analogWrite(C_DATA_PIN, cFader.startFader(fadeAmount));
//  }
//  if (currentMillis - previousMillis >= letterStartDelay*3) {
//    analogWrite(TOOLS_DATA_PIN, toolsFader.startFader(fadeAmount));
//  }
  if (currentMillis - previousMillis >= letterStartDelay*3) {
    upDown = false;
  }
  if (current_mFade == 0 && !upDown) {
    reset();
  }
}

void reset() {
  Serial.print("------fade at 0-----\n");
  Serial.print("------fade at 0-----\n");
  Serial.print("------fade at 0-----\n");
  Serial.print("------fade at 0-----\n");
  upDown = true;
  previousMillis = millis();
}

//void fadeUpDown(uint8_t start, uint8_t end, uint8_t fadeAmount, unsigned long interval) {
//  unsigned long currentMillis = millis();
//
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;
//
//    if (brightness > 254) {
//      upDown = false;
//    }
//    if (brightness < 1) {
//      upDown = true;
//    }
//    if (upDown) {
//      brightness = brightness +fadeAmount;
//    } else {
//      brightness = brightness -fadeAmount;
//    }
//  }
//}
