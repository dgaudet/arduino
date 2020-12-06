#include <FastLED.h>

// video FastLED basics 3 - https://www.youtube.com/watch?v=Ukq0tH2Tnkc
// this is the palette blending section of the video

#define NUM_LEDS 18
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

uint8_t colorIndex[NUM_LEDS];
uint8_t whichPalette = 0;

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0, 0, 255, 245,
  46, 0, 21, 255,
  179, 12, 250, 0,
  255, 0, 255, 245
};

DEFINE_GRADIENT_PALETTE( orangepink_gp ) {
  0, 255, 100, 0,         //orange
  90, 255, 0, 255,     //magenta
  150, 255, 100, 0,   //orange
  255, 255, 100, 0    // orange
};

DEFINE_GRADIENT_PALETTE( browngreen_gp ) {
  0, 6, 255, 0,         //green
  71, 0, 255, 153,     //blueGreen
  122, 200, 200, 200,   //gray
  181, 110, 61, 6,    // brown
  255, 6, 255, 0    // green
};

// this activates the palettes
CRGBPalette16 currentPalette(greenblue_gp);
CRGBPalette16 targetPalette(orangepink_gp);

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  // fill the color index array with random numbers from 0-255
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
}

void loop() {
  blendPalettes();
}

void blendPalettes() {
  //color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex[i]);
  }

  nblendPaletteTowardPalette(currentPalette, targetPalette, 10);

  switch (whichPalette) {
    case 0:
      targetPalette = orangepink_gp;
      break;
    case 1:
      targetPalette = browngreen_gp;
      break;
    case 2:
      targetPalette = greenblue_gp;
      break;
  }

  EVERY_N_MILLISECONDS(5) {
    whichPalette++;
    if (whichPalette > 2) whichPalette = 0;
  }

  EVERY_N_MILLISECONDS(5) {
    for (int i = 0; i< NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }

  FastLED.show();
}
