#include <FastLED.h>
#include "FadeOffAndOn.h"
#include "LeftToRightScroller.h"
#include "LightEachLetterThenTools.h"

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

#define NUM_TOOL_LEDS 53
CRGB toolLeds[NUM_TOOL_LEDS];

bool isRunning = false;

uint8_t analogLetterPins[3] = {
  M_DATA_PIN,
  A_DATA_PIN,
  C_DATA_PIN
};
CHSV redColor = CHSV(0, 255, maxBrightness); //red
CHSV defaultToolsColor = redColor;

void setup() {
  pinMode(analogLetterPins[0], OUTPUT);
  pinMode(analogLetterPins[1], OUTPUT);
  pinMode(analogLetterPins[2], OUTPUT);
  FastLED.addLeds<WS2812B, TOOLS_DATA_PIN, GRB>(toolLeds, NUM_TOOL_LEDS);
  FastLED.setBrightness(255);
  fill_solid(toolLeds, NUM_TOOL_LEDS, CRGB::Black);
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
//  analogWrite(M_DATA_PIN, 255);
//  lightEachLetterThenTools();
  runLightEachLetterThenTools();
//  runLeftToRightScroller();
//  runAllFadeOnThenOff();
}

void finishedPattern() {
  Serial.print("------finished pattern-----\n");
  analogWrite(M_DATA_PIN, 0);
  analogWrite(A_DATA_PIN, 0);
  analogWrite(C_DATA_PIN, 0);
  fill_solid(toolLeds, NUM_TOOL_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000);
  isRunning = false;
}

void runLightEachLetterThenTools() {
  isRunning = true;
  
  LightEachLetterThenTools animation = LightEachLetterThenTools(
    2,
    maxBrightness,
    letterFadeInterval,
    letterStartDelay,
    finishedPattern
  );
  while(isRunning) animation.runPattern(analogLetterPins, toolLeds, defaultToolsColor);
}

void runAllFadeOnThenOff() {
  isRunning = true;
  
  FadeOffAndOn fader = FadeOffAndOn(
    2,
    maxBrightness,
    letterFadeInterval,
    finishedPattern
  );
  while(isRunning) fader.runPattern(analogLetterPins, toolLeds, defaultToolsColor);
}

void runLeftToRightScroller() {
  isRunning = true;
  
  LeftToRightScroller scroller = LeftToRightScroller(NUM_TOOL_LEDS, 2, maxBrightness, finishedPattern);
  while(isRunning) scroller.runPattern(analogLetterPins, toolLeds, defaultToolsColor);
}
