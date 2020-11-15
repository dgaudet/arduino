#include <FastLED.h>

#define NUM_LEDS 147
#define DATA_PIN 8
CRGB leds[NUM_LEDS];

uint8_t value = 0;
uint8_t upDown = 0;

uint8_t functionRunCounter = 0;

uint8_t ledsLit = 0;

CHSV redColor = CHSV(0, 255, 255); // bright red
CHSV blackColor = CHSV(0, 0, 0);

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  Serial.begin(9600);
}

void loop() {
//  tracer();
  if (functionRunCounter == 10) {
    functionRunCounter = 0;
    fill_solid(leds, NUM_LEDS, blackColor);
    FastLED.show();
    delay(1000);
    Serial.print("---------Reset--------");
  } else if (functionRunCounter < 2) {
    fadeOffThenOn();
  } else if (functionRunCounter > 1 && functionRunCounter < 4) {
    twoSidedOnThenOff();
  } else if (functionRunCounter > 3 && functionRunCounter < 7) {
    chaserUsingSawToothWave();
  } else {
    tracer();
  }

  EVERY_N_MILLISECONDS(1000) {
    Serial.print(functionRunCounter);
  }
}

void chaser() {
//  CRGB color = CRGB::Purple;
  CHSV color = CHSV(192, 128, 200);
  for(int dot = 0;dot < NUM_LEDS; dot++) {
    leds[dot] = color;
    FastLED.show();
    leds[dot] = CRGB::Black;
    delay(25);
  }

  for(int dot = NUM_LEDS-1;dot > 0; dot--) {
    leds[dot] = color;
    FastLED.show();
    leds[dot] = CRGB::Black;
    delay(25);
  }
}

void tracer() {
  // this one uses a wave where it goes from the start to the end of the strip
  // then back the opposite direction but has a nice tail and fade out effect
  uint8_t waveSpeedBPM = 20;
  uint8_t sinBeat = beatsin8(waveSpeedBPM, 0, NUM_LEDS -1, 0, 0);
  leds[sinBeat] = redColor;
  
  fadeToBlackBy(leds, NUM_LEDS, 10);
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*3) {
    functionRunCounter++;
    Serial.print("adding in tracer");
    Serial.print("\n");
  }
}

void chaserUsingSawToothWave() {
  // this one kicks off the same sawtooth wave 9 times, just offset by a certain amount
  // of time so they look like they are chasing eachother and as if it goes on forever
  // the number of chaserCount, the second param passed into the beat8 function and
  // the fadeToBlackBy number determine how they work together
  // period of wave 60/bpm *1000
  // so if you have 10 bpm you get 6000ms which means it takes 6sec for the wave to reach the end
  // of the strip
  
  uint8_t waveSpeedBPM = 15;
  uint8_t fadeToBlackSpeed = 45;
  for (uint8_t chaserCount = 0; chaserCount < 12; chaserCount++) {
    uint8_t pos = map(beat8(waveSpeedBPM, chaserCount*330), 0, 255, 0, NUM_LEDS -1);
    leds[pos] = redColor;
  }

  fadeToBlackBy(leds, NUM_LEDS, fadeToBlackSpeed);
  FastLED.show();

  int timeForOneFullWave = (60/waveSpeedBPM)*1000;
  EVERY_N_MILLISECONDS(timeForOneFullWave*2) {
    functionRunCounter++;
    Serial.print("adding in chaserUsingSawTooth");
    Serial.print("\n");
  }
}


void twoSidedOnThenOff() {
  CHSV color;

  EVERY_N_MILLISECONDS(50) {
    if (value == 0) {
      fill_solid(leds, NUM_LEDS, blackColor);
      FastLED.show();
    }
    if (upDown == 0){
      color = redColor;
      leds[value] = color;
      leds[NUM_LEDS - value -1] = color;
      value++;
    } else {
      color = blackColor;
      leds[value] = color;
      leds[NUM_LEDS - value -1] = color;
      value--;
    }
    if (value > NUM_LEDS/2){
      upDown = 1;
    }
    if (value < 1) {
      upDown = 0;
      functionRunCounter++;   //increment functionRunCounter everytime we make it through one full cycle
      Serial.print("adding in twoSidedOnThenOff");
      Serial.print("\n");
    }
    FastLED.show();
  }
}

void fadeOffThenOn() {
  CHSV color = CHSV(0, 255, value);

  fill_solid(leds, NUM_LEDS, color);
  
  EVERY_N_MILLISECONDS(15) {
    if (upDown == 0){
      value++;
    } else {
      value--;
    }
    if (value > 200){
      upDown = 1;
    }
    if (value < 1) {
      upDown = 0;
      functionRunCounter++;   //increment functionRunCounter everytime we make it through one full cycle
      Serial.print("adding in fadeOffThenOn");
      Serial.print("\n");
    }
  }

  FastLED.show();
}
