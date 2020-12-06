#include <FastLED.h>

#define NUM_LEDS 18
#define LED_PIN 2

CRGB leds[NUM_LEDS];

uint8_t patternCounter = 0;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);
}

void loop() {
  switch (patternCounter) {
    case 0:
      movingDots();
      break;
    case 1:
      rainbowBeat();
      break;
    case 2:
      redWhiteBlue();
      break;
  }

  EVERY_N_SECONDS(5) {
    nextPattern();
  }

  FastLED.show();
}

void nextPattern() {
  patternCounter = (patternCounter + 1) %3;
}

void movingDots() {
  uint16_t posBeat  = beatsin16(30, 0, NUM_LEDS -1, 0, 0);
  uint16_t posBeat1 = beatsin16(60, 0, NUM_LEDS -1, 0, 0);

  uint16_t posBeat3 = beatsin16(30, 0, NUM_LEDS -1, 0, 32767);
  uint16_t posBeat4 = beatsin16(60, 0, NUM_LEDS -1, 0, 32767);

  // Wave for LED color
  uint8_t colBeat = beatsin8(45, 0, 255, 0, 0);

  leds[(posBeat + posBeat1) /2] = CHSV(colBeat, 255, 255);
  leds[(posBeat3 + posBeat4) /2] = CHSV(colBeat, 255, 255);

  fadeToBlackBy(leds, NUM_LEDS, 10);
}

void rainbowBeat() {
//  uint16_t beatA = beatsin16(30, 0, 255);
//  uint16_t beatb = beatsin16(20, 0, 255);
//
//  fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 8);
}

void redWhiteBlue() {
  
}
