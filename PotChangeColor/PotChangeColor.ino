#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 8
#define POT_PIN A0
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t potRead = analogRead(POT_PIN);
  // this is mapping the value of potRead which normally goes from 0 - 1023 down to
  // between 0 - 200. Why 200? 255 is the max brightness and is just too bright, so he picked 200
  uint8_t potMapp255 = map(potRead, 0, 712, 0, 255);
  
//  FastLED.setBrightness(potMapp255);
  Serial.print(potMapp255);
  Serial.print("\n");

  CHSV color = CHSV(potMapp255, 255, 200);
  
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}
