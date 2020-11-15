#include <FastLED.h>

// from this video - https://www.youtube.com/watch?v=FQpXStjJ4Vc

#define NUM_LEDS 18
#define DATA_PIN 8
#define POT_PIN A0
CRGB leds[NUM_LEDS];

uint8_t hue = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);
}

void loop() {
//  fill_solid(leds, NUM_LEDS, CRGB::Black);
  customRainbowByChangingHue();
//  twinklyPattern();
//  twinklyPatternWithPotentiometer();
}

void twinklyPatternWithPotentiometer() {
  // this makes a very twinkly pattern by randomly changing the saturation
  // between 0 - 255, and changing the value between 100 - 255

  uint16_t potRead = analogRead(POT_PIN);
  // this is mapping the value of potRead which normally goes from 0 - 1023 down to
  // between 0 - 200. Why 200? 255 is the max brightness and is just too bright, so he picked 200
  uint8_t brightness = map(potRead, 0, 1023, 0, 200);
  FastLED.setBrightness(brightness);
  
  EVERY_N_MILLISECONDS(50) {
    // Create a new pixel for led[0]
    leds[0] = CHSV(160, random8(), random8(100, 255));
  
    //Copy each pixel to the next one, starting at the far end
    //which 'moves' the pattern along the strip
    for(int i = NUM_LEDS -1; i >- 0; i--) {
      leds[i] = leds[i - 1];
    }
    FastLED.show();
  }
}

void twinklyPattern() {
  // this makes a very twinkly pattern by randomly changing the saturation
  // between 0 - 255, and changing the value between 100 - 255
  EVERY_N_MILLISECONDS(50) {
    // Create a new pixel for led[0]
    leds[0] = CHSV(160, random8(), random8(100, 255));
  
    //Copy each pixel to the next one, starting at the far end
    //which 'moves' the pattern along the strip
    for(int i = NUM_LEDS -1; i >- 0; i--) {
      leds[i] = leds[i - 1];
    }
    FastLED.show();
  }
}

void customRainbowByChangingHue() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i*10), 255, 255);
  }

  EVERY_N_MILLISECONDS(15) {
    hue++;
  }
  FastLED.show();
}
