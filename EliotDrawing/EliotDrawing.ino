#include <FastLED.h>

#define NUM_LEDS 8
#define DATA_PIN 8
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
}
