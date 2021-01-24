#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

#define DATA_PIN 2
#define NUM_LEDS 10

//Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
//  strip.begin();
//  strip.show();
  
  FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
  FastLED.setBrightness(40);
//  fill_solid(leds, 20, CRGB::Black);
//  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
//  strip.setPixelColor(1, red, green, blue, white);
//  strip.setPixelColor(0, 255, 0, 0);
//  strip.setPixelColor(1, 0, 255, 0);
//  strip.setPixelColor(2, 0, 0, 255);
////  strip.setPixelColor(2, 50, 64, 50, 64);
//  strip.show();

  leds[0] = CRGB::Red;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
//  fill_solid(leds, 2, CRGB::Blue);
  FastLED.show();
}
