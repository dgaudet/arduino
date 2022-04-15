#include <FastLED.h>

const int numLeds = 96;
const int pin = 4;
const int nextButton = 3;
const int colorButton = 2;
const int maxAnimation = 13;
const int maxColor = 8;

int animation = 0; // the starting animation 
int color = 2;
int state = 1;    // used to determine that time is moving, each second this gets bumped
int fadeState = 0;
int maxState = 100; // used to restart the state and increment the animation number when it hit this number for a given animation
int changeTime = 1; // used to determine how much time before the state is incremented
int blendSpeed = 2;
int brightness = 50; // this is the highest level of brightness that the lights will go to

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
  FastLED.setBrightness(brightness);
  FastLED.setCorrection(UncorrectedColor);
  clear();
  update();

  colors[0] = CRGB::Black;
  colors[1] = CRGB::Red;
  colors[2] = CRGB::Green;
  colors[3] = CRGB::Blue;
  colors[4] = CRGB::Yellow;
  colors[5] = CRGB::Magenta;
  colors[6] = CRGB::Cyan;
  colors[7] = CRGB::White;

  animations[0] = threeAreas;
  animations[1] = moveOneWay;
  animations[2] = rainbow;
  animations[3] = moveTwoWayFade;
  animations[4] = fadeHueSolid;
  animations[5] = RGWWave;
  animations[6] = solid;
  animations[7] = closeIn;
  animations[8] = closeIn;
  animations[9] = closeIn;
  animations[10] = closeIn;
  animations[11] = closeIn;
  animations[12] = closeOut;

  for(int i = 0; i < numLeds; i++) {
    colorIndex[i] = random8();
  }

  Serial.println("end setup");
}

void loop() {  
  Serial.println("start loop");
  
  updateState();

  animations[animation]();
  if(animation < maxAnimation - 1) {
    animations[animation];
  } else {
    animations[0];
  }
  Serial.print("on animation: ");
  Serial.print(animation);
  Serial.println();
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
  Serial.print("updating state: ");
  Serial.print(state);
  Serial.println();
  
  if ((millis() - prevChangeTime) > changeTime) {
    state++;
    if(state > maxState) {
      state = 1;
      fadeState++;
      animation++;
      if(animation >= maxAnimation) {
        animation = 0;
      }
    }
    prevChangeTime = millis();
  }
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
  changeTime = 1000;
  maxState = 5;
  fill_solid(leds, numLeds, colors[color]);
}

void solidBlink() {
  // currently not working
  changeTime = 10;
  maxState = 100;
  if(state % 2 == 0) {
    fill_solid(leds, numLeds, colors[color]);
  } else {
    clear();
    Serial.println("---------clear---------");
  }
}

void moveOneWay() {
  changeTime = 60;
  maxState = 300;
  uint8_t led = map(beat8(changeTime, 0), 0, 255, 0, numLeds-1);
  leds[led] = colors[1];

  fadeToBlackBy(leds, numLeds, 10);
}

void moveTwoWayFade() {
  changeTime = 5;
  maxState = 350;
  uint8_t sinBeat = beatsin8(changeTime, 0, numLeds - 1, 0, 0);
  leds[sinBeat] = colors[3];

  fadeToBlackBy(leds, numLeds, 10);
}

void topBottomFade() {
  // currently not working
  changeTime = 50;
  maxState = 100;
  uint8_t sinBeat = beatsin8(changeTime, 0, numLeds - 1, 0, 0);
  leds[sinBeat] = colors[1];

  fadeToBlackBy(leds, numLeds, 10);
}

void rainbow() {
  changeTime = 50;
  maxState = brightness + 50;
  if(state < maxState - 50) {
    fill_rainbow(leds, numLeds, 0, 255 / numLeds);
  } else {
    fadeToBlackBy(leds, numLeds, 10);
  }
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
  // this works but isn't interesting unfortunately
  changeTime = 15;
  maxState = 255;
  for(int led = 0; led < numLeds; led++) {
    leds[led] = CHSV(state + (led*60), 255, 255);
  }
}

void RGWWave() {
  maxState = 200;
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
  // currently doesn't work
  changeTime = 5;
  maxState = 1;
  for(int led = 0; led < numLeds; led++) {
    leds[led] = ColorFromPalette(RGW, colorIndex[led]);
  }

  if(state == 1) {
    for(int i = 0; i < numLeds; i++) {
      colorIndex[i]++;
    }
  }
}

void threeAreas() {
  changeTime = 50;
  maxState = 151;
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
  CRGB color = colors[animation-6];
  changeTime = 60;
  maxState = 70;
  if(state <= 25) {
    // light up left
    leds[state-2] = color;
    leds[numLeds - state] = color;
    // light up right
    leds[46+state] = color;
    leds[47-state] = color;
  }
}

void closeOut() {
  CRGB color = colors[0];
  changeTime = 40;
  maxState = 70;
  if(state <= 25) {
    // light up left
    leds[25-state] = color;
    leds[70+state] = color;
    // light up right
    leds[22 + state] = color;
    leds[72 - state] = color;
  }
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
