#include "FastLED.h"                                          // FastLED library.

// from https://www.youtube.com/watch?v=4Ut4UK7612M&feature=youtu.be
// Initialize changeable global variables.
#define NUM_LEDS 30
#define LED_PIN 8
 
struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
 
 
void setup() {
 
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  Serial.begin(57600);
} // setup()
 
 
 
void loop () {
  uint8_t sinBeat = beatsin8(30, 0, NUM_LEDS -1, 0, 0);
  uint8_t sinBeat2 = beatsin8(30, 0, NUM_LEDS -1, 0, 85);
  uint8_t sinBeat3 = beatsin8(30, 0, NUM_LEDS -1, 0, 170);
  
  leds[sinBeat] = CRGB::Purple;
  leds[sinBeat2] = CRGB::Red;
  leds[sinBeat3] = CRGB::Yellow;

//  EVERY_N_MILLISECONDS(1) {
//    for(int i=0; i<4; i++){
//      blur1d(leds, NUM_LEDS, 50);
//    }
//  }

//  fadeToBlackBy(leds, NUM_LEDS, 10);

  EVERY_N_MILLISECONDS(1){
    Serial.print(sinBeat);
    Serial.print(",");
    Serial.print(sinBeat2);
    Serial.print(",");
    Serial.print(sinBeat3);
    Serial.print(",");
  }
  
  FastLED.show();
} // loop()
