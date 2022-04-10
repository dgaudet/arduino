#include <FastLED.h>

const int numLeds = 96;
const int pin = 4;
const int nextButton = 3;
const int colorButton = 2;
const int maxAnimation = 11;
const int maxColor = 8;

int animation = 5;
int color = 2;
int state = 0;
int fadeState = 0;
int maxState = 0;
int changeTime = 1;
int blendSpeed = 2;

uint8_t hue = 0;
uint8_t blendAmount = 0;

bool useLeds1 = true;

unsigned long lastDebounceTimeNext = 0;
unsigned long debounceDelay = 300;
unsigned long lastDebounceTimeColor = 0;
unsigned long prevChangeTime = 0;

typedef void (*animFn)();

static animFn animations[maxAnimation];
static CRGB colors[maxColor];

CRGB leds[numLeds];
CRGB leds2[numLeds];
CRGB output[numLeds];
uint8_t colorIndex[numLeds];

void setup() {
  Serial.println("start setup");
  pinMode(nextButton, INPUT);
  pinMode(colorButton, INPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  FastLED.addLeds<WS2812, pin, GRB>(leds, numLeds);
  FastLED.setBrightness(50);
  FastLED.setCorrection(UncorrectedColor);
  clear();
  update();

  animations[0] = solid;//X
  animations[1] = solidBlink;
  animations[2] = moveOneWay;
  animations[3] = moveTwoWayFade;
  animations[4] = topBottomFade;
  animations[5] = rainbow;
  animations[6] = fadeHueSolid;
  animations[7] = fadeHue;
  animations[8] = RGWWave;
  animations[9] = RGWBlink;//X
  animations[10] = threeAreas;
  animations[11] = closeIn;

  colors[0] = CRGB::Black;
  colors[1] = CRGB::Red;
  colors[2] = CRGB::Green;
  colors[3] = CRGB::Blue;
  colors[4] = CRGB::Yellow;
  colors[5] = CRGB::Magenta;
  colors[6] = CRGB::Cyan;
  colors[7] = CRGB::White;

  for(int i = 0; i < numLeds; i++) {
    colorIndex[i] = random8();
  }
//  
//  attachInterrupt(digitalPinToInterrupt(colorButton), nextColor, RISING);
//  attachInterrupt(digitalPinToInterrupt(nextButton), nextAnimation, RISING);
  Serial.println("end setup");
}

void loop() {  
  Serial.println("start loop");

//  EVERY_N_MILLISECONDS(10) {
//    clear();
//    blend(leds2, leds, output, numLeds, blendAmount);
//    if(useLeds1) {
//      if(blendAmount < 255) {
//        blendAmount ++; 
//      }
//    } else {
//      if(blendAmount > 0) {
//        blendAmount --;
//      }
//    }
//  }
  
  updateState();

//  Serial.println(animation);
  animations[animation]();
  if(animation < maxAnimation - 1) {
    animations[animation+1];
  } else {
    animations[0];
  }
  
  update();
  Serial.println("end loop");
  delay(10);
}

void update() {
  FastLED.show();
}

void clear() {
  fill_solid(output, numLeds, CRGB::Black);
}

void updateState() {
//  Serial.print("animation: ");
//  Serial.print(animation);
//  Serial.print("  color: ");
//  Serial.println(color);
  
  if ((millis() - prevChangeTime) > changeTime) {
    state++;
    if(state > maxState) {
      state = 0;
      fadeState++;
      animation++;
    }
    prevChangeTime = millis();
  }
}

void nextAnimation() {  
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTimeNext) > debounceDelay) {
     animation++;
     useLeds1 = !useLeds1;
      if(animation > maxAnimation) {
        animation = 0;
      }
      state = 0;
  }

  lastDebounceTimeNext = currentTime;
}

void nextColor() {  
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTimeColor) > debounceDelay) {
     color++;
      if(color >= maxColor) {
        color = 0;
      }
  }
  lastDebounceTimeColor = currentTime;
}

//<animation-functions>

void solid() {
  fill_solid(leds, numLeds, colors[color]);
}

void solidBlink() {
  changeTime = 200;
  maxState = 1;
  if(state == 0) {
    fill_solid(leds2, numLeds, colors[color]);
  } else {
    clear();
  }
}

void moveOneWay() {
  changeTime = 60;
  uint8_t led = map(beat8(changeTime, 0), 0, 255, 0, numLeds-1);
  leds[led] = colors[color];

  fadeToBlackBy(leds, numLeds, 10);
}

void moveTwoWayFade() {
  changeTime = 50;
  uint8_t sinBeat = beatsin8(changeTime, 0, numLeds - 1, 0, 0);
  leds2[sinBeat] = colors[color];

  fadeToBlackBy(leds2, numLeds, 10);
}

void topBottomFade() {
  changeTime = 50;
  uint8_t sinBeat = beatsin8(changeTime, 0, numLeds - 1, 0, 0);
  leds[sinBeat] = colors[color];

  fadeToBlackBy(leds, numLeds, 1);
}

void rainbow() {
  fill_rainbow(leds2, numLeds, 0, 255 / numLeds);
}

void fadeHueSolid() {
  changeTime = 15;
  maxState = 255;
  fill_solid(leds, numLeds, CHSV(state, 255, 255));
}

void fadeHue() {
  changeTime = 15;
  maxState = 255;
  for(int led = 0; led < numLeds; led++) {
    leds[led] = CHSV(state + (led*15), 255, 255);
  }
}

void fadeHueFast() {
  changeTime = 15;
  maxState = 255;
  for(int led = 0; led < numLeds; led++) {
    leds[led] = CHSV(state + (led*30), 255, 255);
  }
}

void RGWWave() {
  uint8_t sinBeat1 = beatsin8(30, 0, numLeds-1, 0, 0);
  uint8_t sinBeat2 = beatsin8(30, 0, numLeds-1, 0, 85);
  uint8_t sinBeat3 = beatsin8(30, 0, numLeds-1, 0, 170);

  leds[sinBeat1] = CRGB::Red;
  leds[sinBeat2] = CRGB::Green;
  leds[sinBeat3] = CRGB::White;
  
  fadeToBlackBy(leds, numLeds, 1);
}

DEFINE_GRADIENT_PALETTE(redGreenWhite_gp) {
  0, 255, 0, 0,
  64, 0, 255, 0,
  191, 255, 255, 255,
  255, 255, 0, 0
};

CRGBPalette16 RGW = redGreenWhite_gp;

void RGWBlink() {
  changeTime = 5;
  maxState = 1;
  for(int led = 0; led < numLeds; led++) {
    leds2[led] = ColorFromPalette(RGW, colorIndex[led]);
  }

  if(state == 1) {
    for(int i = 0; i < numLeds; i++) {
      colorIndex[i]++;
    }
  }
}

void threeAreas() {
  changeTime = 50;
  maxState = 81;
  Serial.println(state);
  if(state >= 80) {
    firstThird(CRGB(255, 0, 0));
    secondThird(CRGB(0, 255, 0));
    thirdThird(CRGB(0, 0, 255));
  } else if(state >= 60) {
    firstThird(CRGB(255, 0, 0));
    secondThird(CRGB(0, 255, 0));
    thirdThird(CRGB(0, 0, (state%20*13)));
  } else if(state >= 40) {
    firstThird(CRGB(255, 0, 0));
    secondThird(CRGB(0, ((state%20)*13), 0));
  } else if(state >= 20) {
    secondThird(CRGB(0, 0, 0));
    firstThird(CRGB((state%20*13), 0, 0)); 
  } else {
    firstThird(CRGB(0, 0, 0));
    secondThird(CRGB(0, 0, 0));
    thirdThird(CRGB(0, 0, 0));
    clear();
  }
}

void closeIn() {
//  test++;
  changeTime = 1;
  maxState = 22;
  int test = state;
//  lightUpArea(0, state, CRGB::Red);
  leds[test] = CRGB::Red;
//  for(int i = 0; i < numLeds; i++) {
//    if(i == state) {
//      leds[i] = CRGB::Red;
//    }
//  }
}

//</animation-functions>

void lightUpArea(int startingIndex, int endingIndex, CRGB color) {
  for(int led = startingIndex; led < endingIndex; led++) {
    leds[led] = color;
  }
}

void firstThird(CRGB color) {
  lightUpArea(0, 16, color);
  lightUpArea(78, 96, color);
}

void secondThird(CRGB color) {
  lightUpArea(16, 31, color);
  lightUpArea(63, 78, color);
}

void thirdThird(CRGB color) {
  lightUpArea(31, 63, color);
}





















































//
