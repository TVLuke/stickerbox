#include <Arduino.h>

struct RGB {
  byte r;
  byte g;
  byte b;
};

static const int number_of_stripes = 3;
static const int number_of_leds_per_stripe = 100;
static const int frames_per_mode = 1000;
static const int frame_delay = 1;

static const RGB BLACK = {0,0,0};
static const RGB WHITE = {100,100,100};
static const RGB RED = {255,0,0};
static const RGB GREEN = {0,255,0};
static const RGB BLUE = {0,0,255};
static const RGB ORANGE = {215,50,0};
static const RGB YELLOW = {255,255,0};
static const RGB MAGENTA = {255,0,255};

static const RGB pride[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, MAGENTA};

//these are reset between each modes
RGB TMP1 = {0,0,0};
RGB TMP2 = {0,0,0};
RGB TMP3 = {0,0,0};

RGB leds[number_of_stripes][number_of_leds_per_stripe] = {};

void setcolor(int ledStripeNumber, RGB c) {
    for(int j=0; j<number_of_leds_per_stripe; j++) {
      leds[ledStripeNumber][j].r = c.r;
      leds[ledStripeNumber][j].g = c.g;
      leds[ledStripeNumber][j].b = c.b;
    }
}

void reset(int ledStripeNumber) {
  setcolor(ledStripeNumber, BLACK);
}

void reset() {
  for (int i = 0; i < number_of_stripes; i++) {
    reset(i);
  }
}

int getPrideColor_r(int numberOfLed) {
  int divN = number_of_leds_per_stripe/6;
  return pride[numberOfLed/divN].r;
}

int getPrideColor_g(int numberOfLed) {
  int divN = number_of_leds_per_stripe/6;
  return pride[numberOfLed/divN].g;
}

int getPrideColor_b(int numberOfLed) {
  int divN = number_of_leds_per_stripe/6;
  return pride[numberOfLed/divN].b;
}

int getWheel_r(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return 255 - wheelPos * 3;
  }
  if(wheelPos < 170) {
    return 0;
  }
  wheelPos -= 170;
  return wheelPos * 3;
}

int getWheel_g(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return 0;
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
    return wheelPos * 3;
  }
  wheelPos -= 170;
  return 255 - wheelPos * 3;
}

int getWheel_b(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return wheelPos * 3;
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
    return 255 - wheelPos * 3;
  }
  return 0;
}

void walkForwards(int ledStripeNumber) {
  int nextColor_r = leds[ledStripeNumber][0].r;
  int nextColor_g = leds[ledStripeNumber][0].g;
  int nextColor_b = leds[ledStripeNumber][0].b;
  for(int j=1; j<number_of_leds_per_stripe; j++) {
      int nextColorTemp_r = leds[ledStripeNumber][j].r;
      int nextColorTemp_g = leds[ledStripeNumber][j].g;
      int nextColorTemp_b = leds[ledStripeNumber][j].b;

      leds[ledStripeNumber][j].r = nextColor_r;
      leds[ledStripeNumber][j].g = nextColor_g;
      leds[ledStripeNumber][j].b = nextColor_b;

      nextColor_r = nextColorTemp_r;
      nextColor_g = nextColorTemp_g;
      nextColor_b = nextColorTemp_b;
    if(j == number_of_leds_per_stripe-1) {
      leds[ledStripeNumber][0].r = nextColor_r;
      leds[ledStripeNumber][0].g = nextColor_g;
      leds[ledStripeNumber][0].b = nextColor_b;
    }
  }
}

void walkForwards() {
  for(int i=0; i<number_of_stripes; i++) {
    walkForwards(i);
  }
}

void walkBackwards(int ledStripeNumber) {
  int nextColor_r = leds[ledStripeNumber][number_of_leds_per_stripe-1].r;
  int nextColor_g = leds[ledStripeNumber][number_of_leds_per_stripe-1].g;
  int nextColor_b = leds[ledStripeNumber][number_of_leds_per_stripe-1].b;
  for(int j=number_of_leds_per_stripe-2; j>=0; j--) {
      int nextColorTemp_r = leds[ledStripeNumber][j].r;
      int nextColorTemp_g = leds[ledStripeNumber][j].g;
      int nextColorTemp_b = leds[ledStripeNumber][j].b;

      leds[ledStripeNumber][j].r = nextColor_r;
      leds[ledStripeNumber][j].g = nextColor_g;
      leds[ledStripeNumber][j].b = nextColor_b;

      nextColor_r = nextColorTemp_r;
      nextColor_g = nextColorTemp_g;
      nextColor_b = nextColorTemp_b;
    if(j == 0) {
      leds[ledStripeNumber][number_of_leds_per_stripe-1].r = nextColor_r;
      leds[ledStripeNumber][number_of_leds_per_stripe-1].g = nextColor_g;
      leds[ledStripeNumber][number_of_leds_per_stripe-1].b = nextColor_b;
    }
  }
}

void walkBackwards() {
  for(int i=0; i<number_of_stripes; i++) {
      walkBackwards(i);
    }
}
