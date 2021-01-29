#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define DATA_PIN 2
#define NUM_LEDS 50

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);
uint8_t ledCounter = 0;

uint32_t whiteColor = strip.Color(0, 0, 0, 255);
uint32_t redColor = strip.Color(255, 0, 0, 0);
uint32_t bothColor = strip.Color(255, 0, 0, 255);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  Serial.begin(9600);
  strip.show();
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
    strip.fill(redColor, 0, NUM_LEDS);
//    strip.fill(bothColor, 0, NUM_LEDS);
    strip.show();
//  turnOnOneByOne_2();
}

void turnOnOneByOne_2() {
//  uint32_t color = strip.Color(0, 64, 0, 64); //green-ish-white
  uint32_t color = whiteColor;
  EVERY_N_MILLISECONDS(150) {
    strip.setPixelColor(ledCounter, color);
    Serial.print(ledCounter);
    Serial.print("\n");
    ledCounter++;
    if (ledCounter > NUM_LEDS) {
      ledCounter = 0;
      strip.fill();
    }
  }
  strip.show();
}
