#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include "FadeInAndOut.h"
#include "TurnOnLeftToRight.h"

#define TOP_PIN 5
#define BOTTOM_PIN 7
#define TOP_LEDS 150
#define BOTTOM_LEDS 104
#define E_PIN 4
#define E_LEDS 26
#define BRIGHTNESS 10

Adafruit_NeoPixel topStrip(TOP_LEDS, TOP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottomStrip(BOTTOM_LEDS, BOTTOM_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eMiddleStrip(E_LEDS, E_PIN, NEO_GRB + NEO_KHZ800);

uint32_t whiteColor = bottomStrip.Color(0, 0, 0, BRIGHTNESS);
uint32_t redColor = topStrip.Color(BRIGHTNESS, 0, 0, 0);
uint32_t bothColor = topStrip.Color(BRIGHTNESS, 0, 0, BRIGHTNESS);
uint32_t greenColor = topStrip.Color(0, BRIGHTNESS, 0, 0);

bool isRunning = false;

void setup() {
  // put your setup code here, to run once:
  topStrip.begin();
  bottomStrip.begin();
  eMiddleStrip.begin();
  Serial.begin(9600);
  topStrip.show();
  bottomStrip.show();
  eMiddleStrip.show();
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
//  fadeInAndOut();
//  uint32_t greenColor = topStrip.Color(0, BRIGHTNESS, 0, 0);
  turnOnOneByOneClass(greenColor);
}

void fadeInAndOut() {
  Serial.print("run fade in and out");
  Serial.print("\n");
  isRunning = true;
  FadeInAndOut animation = FadeInAndOut(TOP_LEDS, BOTTOM_LEDS);
  while(isRunning) animation.runPattern(topStrip, bottomStrip, whiteColor);
}

void turnOnOneByOneClass(uint32_t color) {
  Serial.print("turn on left to right");
  Serial.print("\n");
  isRunning = true;
  TurnOnLeftToRight animation = TurnOnLeftToRight();
  while(isRunning) animation.runPattern(topStrip, bottomStrip, eMiddleStrip, color);
}
