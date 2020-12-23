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

#define NUM_TOOL_LEDS 53
CRGB toolLeds[NUM_TOOL_LEDS];

bool isRunning = false;
uint8_t functionRunCounter = 0;

uint8_t analogLetterPins[3] = {
  M_DATA_PIN,
  A_DATA_PIN,
  C_DATA_PIN
};
CHSV redColor = CHSV(0, 255, maxBrightness); //red
CHSV defaultToolsColor = redColor;

void setup() {
  for (int pinCounter = 0; pinCounter <= sizeof(analogLetterPins); pinCounter++) {
    pinMode(analogLetterPins[pinCounter], OUTPUT);
  }
  FastLED.addLeds<WS2812B, TOOLS_DATA_PIN, GRB>(toolLeds, NUM_TOOL_LEDS);
  FastLED.setBrightness(255);
  fill_solid(toolLeds, NUM_TOOL_LEDS, CRGB::Black);
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
  switch (functionRunCounter) {
    case 0:
      runLightEachLetterThenTools(2);
      break;
    case 1:
      runLeftToRightScroller(2);
      break;
    default:
      runAllFadeOnThenOff(2);
      break;
  }
}

void finishedPattern() {
  Serial.print("------finished pattern-----\n");
  for (int pinCounter = 0; pinCounter <= sizeof(analogLetterPins); pinCounter++) {
    analogWrite(analogLetterPins[pinCounter], 0);
  }
  fill_solid(toolLeds, NUM_TOOL_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000);
  isRunning = false;
  functionRunCounter++;
  if (functionRunCounter >=3) {
    functionRunCounter = 0;
    Serial.print("---------Reset--------\n");
  }
}

void runLightEachLetterThenTools(uint8_t numRuns) {
  isRunning = true;
  
  LightEachLetterThenTools animation = LightEachLetterThenTools(
    numRuns,
    maxBrightness,
    letterFadeInterval,
    letterStartDelay,
    finishedPattern
  );
  while(isRunning) animation.runPattern(analogLetterPins, toolLeds, defaultToolsColor);
}

void runAllFadeOnThenOff(uint8_t numRuns) {
  isRunning = true;
  
  FadeOffAndOn fader = FadeOffAndOn(
    numRuns,
    maxBrightness,
    letterFadeInterval,
    finishedPattern
  );
  while(isRunning) fader.runPattern(analogLetterPins, toolLeds, defaultToolsColor);
}

void runLeftToRightScroller(uint8_t numRuns) {
  isRunning = true;
  
  LeftToRightScroller scroller = LeftToRightScroller(NUM_TOOL_LEDS, numRuns, maxBrightness, finishedPattern);
  while(isRunning) scroller.runPattern(analogLetterPins, toolLeds, defaultToolsColor);
}
