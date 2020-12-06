#include <FastLED.h>

#define BODY_NUM_LEDS 47
#define EXTRA_NUM_LEDS 24
#define BODY_DATA_PIN 2
#define EXTRA_DATA_PIN 4

//power
// tested using page 2
// all lights on at 5 brightness - 0.071a
// all lights on at 10 brightness - 0.085a
// all lights on at 20 brightness - 0.112a
// all lights on at 30 brightness - 0.138a
// all lights on at 80 brightness - 0.274a
// all lights on at 100 brightness - 0.328a
// all lights on at 150 brightness - 0.463a
// all lights on at 200 brightness - 0.598a
// all lights on at 225 brightness - 0.667a
// all lights on at 255 brightness - 0.750a

CRGB bodyLeds[BODY_NUM_LEDS];
CRGB extraLeds[EXTRA_NUM_LEDS];

CHSV hsvToCHSV(int hNum, uint8_t sNum, uint8_t vNum) {
  uint8_t hValue = map(hNum, 0, 360, 0, 255);
  uint8_t sValue = map(sNum, 0, 100, 0, 255);
  uint8_t vValue = map(vNum, 0, 100, 0, 255);
  return CHSV(hValue, sValue, vValue);
}

//Basic colors
CHSV blueColor = CHSV(159, 255, 255);
CHSV redColor = CHSV(0, 255, 255);

CHSV pinkColor = hsvToCHSV(320, 65, 93);  //page 1
CHSV lightBlueColor = hsvToCHSV(191,67,100); //page 1

CHSV pink2Color = hsvToCHSV(302, 62, 76); //page 2
CHSV lightBlue2Color = hsvToCHSV(196,66,100); //page 2
CHSV greenColor = hsvToCHSV(135, 100, 100); //page 2
CHSV red2Color = hsvToCHSV(0, 99, 70); //page 2

CHSV pink3Color = hsvToCHSV(326, 47, 100); //page 3
CHSV lightBlue3Color = hsvToCHSV(180, 37, 100); //page 3
CHSV pink4Color = hsvToCHSV(304, 53, 100); //page 3
CHSV lightBlue4Color = hsvToCHSV(196, 63, 100); //page 3

CHSV blackColor = CHSV(0, 0, 0);

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, BODY_DATA_PIN, GRB>(bodyLeds, BODY_NUM_LEDS);
  FastLED.addLeds<WS2812B, EXTRA_DATA_PIN, GRB>(extraLeds, EXTRA_NUM_LEDS);
  FastLED.setBrightness(10);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  fill_solid(bodyLeds, BODY_NUM_LEDS, CRGB::Blue);
//  page1();
  page2();
//  page3();
  FastLED.show();
}

void page1() {
  //color body
  left(bodyLeds, pinkColor);
  top(bodyLeds, pinkColor);
  right(bodyLeds, pinkColor);
  pants(bodyLeds, pinkColor);
  
  //color extremeties
  leftBox(extraLeds, lightBlueColor);
  horn(extraLeds, lightBlueColor);
  eye(extraLeds, lightBlueColor);
}

void page2() {
  //color body
  left(bodyLeds, greenColor);
  top(bodyLeds, greenColor);
  right(bodyLeds, greenColor);
  pants(bodyLeds, greenColor);
  
  //color extremeties
  leftBox(extraLeds, red2Color);
  horn(extraLeds, pink2Color);
  eye(extraLeds, blueColor);
}

void page3() {
  //color body
  left(bodyLeds, pink4Color);
  top(bodyLeds, pink4Color);
  right(bodyLeds, pink4Color);
  pants(bodyLeds, pink4Color);
  
  //color extremeties
  leftBox(extraLeds, lightBlue4Color);
  horn(extraLeds, pink3Color);
  eye(extraLeds, lightBlue3Color);
}

void left(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 4, 11);
}

void top(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 12, 19);
}

void right(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 20, 21);
  colorSection(ledStrip, color, 24, 27);
}

void pants(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 0, 3);
  colorSection(ledStrip, color, 28, 46);
}

void leftBox(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 0, 8);
}

void horn(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 9, 15);
}

void eye(CRGB ledStrip[], CHSV color) {
  colorSection(ledStrip, color, 16, 23);
}

void colorSection(CRGB ledStrip[], CHSV color, uint8_t first, uint8_t last) {
  for(uint8_t ledCounter = first; ledCounter <= last; ledCounter ++) {
    ledStrip[ledCounter] = color;
  }
}
