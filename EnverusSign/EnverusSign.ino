#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include "FadeInAndOut.h"

#define TOP_PIN 13
#define BOTTOM_PIN 6
#define TOP_LEDS 150
#define BOTTOM_LEDS 104

Adafruit_NeoPixel topStrip(TOP_LEDS, TOP_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel bottomStrip(BOTTOM_LEDS, BOTTOM_PIN, NEO_GRBW + NEO_KHZ800);
uint32_t ledCounter = 0;
uint32_t ledCounter1 = 0;
bool upDown = true;

uint32_t whiteColor = bottomStrip.Color(0, 0, 0, 55);
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
//    strip.fill(whiteColor, 0, NUM_LEDS);
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
  fadeInAndOutClass();
//  fadeInAndOut1(topStrip, TOP_LEDS, ledCounter1);
//  fadeInAndOut2();
}

void fadeInAndOutClass() {
  Serial.print("run fade in and out");
  Serial.print("\n");
  isRunning = true;
  FadeInAndOut animation = FadeInAndOut(TOP_LEDS, BOTTOM_LEDS);
  while(isRunning) animation.runPattern(topStrip, bottomStrip);
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

void fadeInAndOut() {
  EVERY_N_MILLISECONDS(10) {
    if (upDown) {
      ledCounter++;
    } else {
      ledCounter--;
    }
    
    uint32_t color = topStrip.Color(0, 0, 0, ledCounter);
    topStrip.fill(color, 0, TOP_LEDS);
    if (ledCounter > 100) {
      upDown = false;
      ledCounter = 100-1;
    }
    if (ledCounter < 1) {
      upDown = true;
    }
    topStrip.show();
  }
}
