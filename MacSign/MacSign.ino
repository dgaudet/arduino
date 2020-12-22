#include <FastLED.h>
#include "Fade.h"

// using 450 ma at 255 brightness full white strip
// using 178 ma at 100 brightness full white strip

//using 275 ma at 100 brightness both colors on 
//using 746 ma at 255 brightness both colors on 

//addressable leds 525ma for 55leds at 150 white
//addressable leds 565ma for 55leds at 160 white probably brightest white
//addressable leds 595ma for 55leds at 200 white but it becomes yellow
//addressable leds 640ma for 55leds at 255 white but it is completely yellow
//addressable leds 17 leds at 100 stays at white
//addressable leds 17 leds at 160 stays white for a short time only
#define M_DATA_PIN 6
#define A_DATA_PIN 5
#define C_DATA_PIN 3
#define TOOLS_DATA_PIN 2

uint8_t brightness = 0;
// I need to stop at 245 instead of 255 because I bump up the brightness at an interval of 5
// so stopping higher causes problems where sometimes we roll over from 255 to 0
uint8_t maxBrightness = 245;
// the letterFadeInterval and letterStartDelay are tightly integrated if you fade to slowly
// it won't make it to the full amount before it starts fading down
unsigned long letterFadeInterval = 25;
unsigned long letterStartDelay = 1500;
bool upDown = true;
unsigned long previousMillis = 0;

Fade mFader = Fade(0, maxBrightness, letterFadeInterval, false);
Fade aFader = Fade(0, maxBrightness, letterFadeInterval, false);
Fade cFader = Fade(0, maxBrightness, letterFadeInterval, false);
Fade toolFader = Fade(0, maxBrightness, letterFadeInterval, true);

#define NUM_TOOL_LEDS 55
CRGB toolLeds[NUM_TOOL_LEDS];


void setup() {
  pinMode(M_DATA_PIN, OUTPUT);
  pinMode(A_DATA_PIN, OUTPUT);
  pinMode(C_DATA_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, TOOLS_DATA_PIN, GRB>(toolLeds, NUM_TOOL_LEDS);
  FastLED.setBrightness(255);
  fill_solid(toolLeds, NUM_TOOL_LEDS, CRGB::Black);
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
  // 100 - 1.86v
  // 200 - 3.69v
  // 255 - 4.72v
//  analogWrite(M_DATA_PIN, 255);
  fadeClass();
//  allFadeOnThenOff();
}

void allFadeOnThenOff() {
  unsigned long currentMillis = millis();
  int macFadeAmount = 5;
  if (!upDown) {
    macFadeAmount = -1 * macFadeAmount;
  }
  
  uint8_t current_mFade = mFader.startFader(macFadeAmount);
  analogWrite(M_DATA_PIN, current_mFade);
  analogWrite(A_DATA_PIN, current_mFade);
  analogWrite(C_DATA_PIN, current_mFade);
  toolsAnimation(current_mFade);

  if (currentMillis - previousMillis >= letterStartDelay*2) {
    upDown = false;
  }
  if (current_mFade == 0 && !upDown) {
    finishedPattern();
  }
}

void fadeClass() {
  unsigned long currentMillis = millis();
  int macFadeAmount = 5;
  if (!upDown) {
    macFadeAmount = -1 * macFadeAmount;
  }

  uint8_t current_mFade = mFader.startFader(macFadeAmount);
  analogWrite(M_DATA_PIN, current_mFade);
  if (currentMillis - previousMillis >= letterStartDelay) {
    analogWrite(A_DATA_PIN, aFader.startFader(macFadeAmount));
  }
  if (currentMillis - previousMillis >= letterStartDelay*2) {
    analogWrite(C_DATA_PIN, cFader.startFader(macFadeAmount));
  }
  if (currentMillis - previousMillis >= letterStartDelay*3) {
    uint8_t tool_fade = toolFader.startFader(macFadeAmount);
    toolsAnimation(tool_fade);
  }
  if (currentMillis - previousMillis >= letterStartDelay*5) {
    upDown = false;
  }
  if (current_mFade == 0 && !upDown) {
    finishedPattern();
  }
}

void finishedPattern() {
  Serial.print("------finished pattern-----\n");
  upDown = true;
  analogWrite(M_DATA_PIN, 0);
  analogWrite(A_DATA_PIN, 0);
  analogWrite(C_DATA_PIN, 0);
  fill_solid(toolLeds, NUM_TOOL_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000);
  previousMillis = millis();
}

void toolsAnimation(uint8_t hue) {
//  CHSV color = CHSV(137, 0, hue); // white
  // using red instead of white because the white is blue sometimes and yellow others during fade
  CHSV color = CHSV(0, 255, hue); //red
//  CHSV color = CHSV(255, 100, 100); //green
//  fill_solid(toolLeds, NUM_TOOL_LEDS, color); //set all ledStrip to black once we get to the end

  //top line
  colorSection(toolLeds, color, 0, 8);
  colorSection(toolLeds, color, 10, 14);
  colorSection(toolLeds, color, 15, 16);
  colorSection(toolLeds, color, 19, 22);

  //right side
  colorSection(toolLeds, color, 24, 25);

  //bottom
  colorSection(toolLeds, color, 27, 34);
  colorSection(toolLeds, color, 36, 39);
  colorSection(toolLeds, color, 41, 44);
  colorSection(toolLeds, color, 46, 48);
  colorSection(toolLeds, color, 50, 52);
  FastLED.show();
}

void colorSection(CRGB ledStrip[], CHSV color, uint8_t first, uint8_t last) {
  for(uint8_t ledCounter = first; ledCounter <= last; ledCounter ++) {
    ledStrip[ledCounter] = color;
  }
}
