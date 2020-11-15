#include <FastLED.h>

// video FastLED basics 3 - https://www.youtube.com/watch?v=Ukq0tH2Tnkc

#define NUM_LEDS 18
#define DATA_PIN 8
CRGB leds[NUM_LEDS];

uint8_t paletteIndex = 0;

//Basic RGB Palette
DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0, 0, 0, 0,         //black
  128, 255, 0, 0,     //red
  200, 255, 255, 0,   //bright yellow
  255, 255, 255, 255 // full white
};

// this activates the palette
CRGBPalette16 myPal = heatmap_gp;

CRGBPalette16 purplePalette = CRGBPalette16 (
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,

  CRGB::Magenta,
  CRGB::Magenta,
  CRGB::Linen,
  CRGB::Linen,

  CRGB::Magenta,
  CRGB::Magenta,
  CRGB::DarkViolet,
  CRGB::DarkViolet,

  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::Linen,
  CRGB::Linen
);

// array of ints for each of the leds in the strip
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0, 0, 255, 245,
  46, 0, 21, 255,
  179, 12, 250, 0,
  255, 0, 255, 245
};

CRGBPalette16 greenblue = greenblue_gp;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  // fill the color index array with random numbers from 0-255
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
}

void loop() {
//  gradientChaser();
//  randomFader();
  randomlyTwinkle();
}

void randomlyTwinkle() {
  //color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i]);
  }

  EVERY_N_MILLISECONDS(5) {
    for (int i=0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }

  FastLED.show();
}

// this makes a very cool twinkly pattern through your color palette
void randomFader() {
  EVERY_N_MILLISECONDS(50) {
    //switch on an LED at random, chosing a ranomd color from the palette
    leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(purplePalette, random8(), 255, LINEARBLEND);
  }

  //fade all LEDS down by 1 in brightness each time this function is called
  fadeToBlackBy(leds, NUM_LEDS, 1);

  FastLED.show();
}

void gradientChaser() {
  fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, purplePalette, 255, LINEARBLEND);

  EVERY_N_MILLISECONDS(10) {
    paletteIndex++;
  }

  FastLED.show();
}
