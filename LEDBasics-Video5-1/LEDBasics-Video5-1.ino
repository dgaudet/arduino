#include <FastLED.h>

#define NUM_LEDS 18
#define LED_PIN 2

CRGB leds[NUM_LEDS];

uint8_t patternCounter = 0;
bool upDown = false;

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
      chaser();
      break;
    case 2:
      chaserSawTooth();
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

void chaser() {
  uint8_t waveSpeedBPM = 30;
  uint8_t sinBeat1 = beatsin8(waveSpeedBPM, 0, NUM_LEDS -1, 0, 0);
  uint8_t sinBeat2 = sinBeat1 - 1;
  CRGB color;
  if (!upDown){
    color = CRGB::Red;
  } else {
    color = CRGB::Black;
  }
  if (sinBeat1 == 0) {
    upDown = false;
  }
  if (sinBeat1 == NUM_LEDS -1) {
    upDown = true;
  }
  
  leds[sinBeat1] = color;
  leds[sinBeat2] = color;
  FastLED.show();
}

void chaserSawTooth() {
  uint8_t waveSpeedBPM = 15;
  uint8_t fadeToBlackSpeed = 45;
  for (uint8_t chaserCount = 0; chaserCount < 12; chaserCount++) {
    uint8_t pos = map(beat8(waveSpeedBPM, chaserCount*330), 0, 255, 0, NUM_LEDS -1);
    leds[pos] = CRGB::Blue;
  }

  fadeToBlackBy(leds, NUM_LEDS, fadeToBlackSpeed);
  FastLED.show();
}
