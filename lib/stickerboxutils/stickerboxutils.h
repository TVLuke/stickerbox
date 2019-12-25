#include <Adafruit_NeoPixel.h>
#include <modes.h>
#include <stickerpoxpins.h>

Adafruit_NeoPixel leds1(NUM_LEDS, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds2(NUM_LEDS, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds3(NUM_LEDS, LED_PIN3, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel stripes[] = {leds1, leds2, leds3};

//new stuff
void (*executeMode) (int);

void resetStripes() {
  reset();

  TMP1 = BLACK;
  TMP2 = BLACK;
  TMP3 = BLACK;
}

/**
** if not all leds are visible at the begining or end, set these so they are not setup
** This can conserve energy
*/
static const int invisible_start = 12;
static const int invisible_end = 13;

void showStripes() {
  for(int i=0; i<number_of_stripes; i++) {
    for(int j=0; j<number_of_leds_per_stripe; j++) {
      if(j > invisible_start && j < (number_of_leds_per_stripe - invisible_end)) {
        stripes[i].setPixelColor(j, leds[i][j].r, leds[i][j].g, leds[i][j].b);
      }
    }
    stripes[i].show();
  }
}
