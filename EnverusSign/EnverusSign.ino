#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include "FadeInAndOut.h"
#include "TurnOnLeftToRight.h"

#define TOP_PIN 4
#define BOTTOM_PIN 2
#define TOP_LEDS 150
#define BOTTOM_LEDS 104

Adafruit_NeoPixel topStrip(TOP_LEDS, TOP_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel bottomStrip(BOTTOM_LEDS, BOTTOM_PIN, NEO_GRBW + NEO_KHZ800);
uint32_t ledCounter = 0;
uint32_t ledCounter1 = 0;
bool upDown = true;

uint32_t whiteColor = bottomStrip.Color(0, 0, 0, 25);
uint32_t redColor = topStrip.Color(255, 0, 0, 0);
uint32_t bothColor = topStrip.Color(255, 0, 0, 255);
uint32_t greenColor = topStrip.Color(0, 255, 0, 0);

bool isRunning = false;

void setup() {
  // put your setup code here, to run once:
  topStrip.begin();
  bottomStrip.begin();
  Serial.begin(9600);
  topStrip.show();
  bottomStrip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
//  strip.setPixelColor(1, red, green, blue, white);
//  strip.setPixelColor(0, 255, 0, 0, 0);
//  strip.setPixelColor(1, 0, 255, 0);
//  strip.setPixelColor(2, 0, 0, 255, 0);
//  strip.setPixelColor(3, 0, 0, 0, 255);
//  strip.setPixelColor(4, 50, 64, 50, 64);
//  strip.setPixelColor(4, 0, 0, 0, 255);
//    bottomStrip.fill(whiteColor, 0, BOTTOM_LEDS);
//    bottomStrip.show();
//    strip.fill(redColor, 0, NUM_LEDS);
//    strip.fill(bothColor, 0, NUM_LEDS);
//  strip.fill(greenColor, 0, NUM_LEDS);
//  strip.setPixelColor(270, whiteColor);
//  strip.setPixelColor(271, whiteColor);
//  strip.setPixelColor(272, whiteColor);
//  strip.setPixelColor(273, whiteColor);
//  strip.setPixelColor(274, whiteColor);
//  strip.setPixelColor(275, whiteColor);
//  turnOnOneByOne();
//  turnOnOneByOne2();
//  fadeInAndOut();
  turnOnOneByOneClass();
}

void fadeInAndOut() {
  Serial.print("run fade in and out");
  Serial.print("\n");
  isRunning = true;
  FadeInAndOut animation = FadeInAndOut(TOP_LEDS, BOTTOM_LEDS);
  while(isRunning) animation.runPattern(topStrip, bottomStrip, whiteColor);
}

void turnOnOneByOneClass() {
  Serial.print("turn on left to right");
  Serial.print("\n");
  isRunning = true;
  TurnOnLeftToRight animation = TurnOnLeftToRight(TOP_LEDS, BOTTOM_LEDS);
  while(isRunning) animation.runPattern(topStrip, bottomStrip, whiteColor);
}

void turnOnOneByOne() {
//  uint32_t color = strip.Color(0, 64, 0, 64); //green-ish-white
  uint32_t color = whiteColor;
  EVERY_N_MILLISECONDS(25) {
    topStrip.setPixelColor(ledCounter, color);
    Serial.print(ledCounter);
    Serial.print("\n");
    ledCounter++;
    if (ledCounter > TOP_LEDS) {
      delay(10);
      ledCounter = 0;
      topStrip.fill();
    }
    topStrip.show();
  }
}

void turnOnOneByOne2() {
//  uint32_t color = strip.Color(0, 64, 0, 64); //green-ish-white
  uint32_t color = whiteColor;
  EVERY_N_MILLISECONDS(25) {
    bottomStrip.setPixelColor(ledCounter, color);
    Serial.print(ledCounter);
    Serial.print("\n");
    ledCounter++;
    if (ledCounter > BOTTOM_LEDS) {
      delay(10);
      ledCounter = 0;
      bottomStrip.fill();
    }
    bottomStrip.show();
  }
}
