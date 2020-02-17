#include <Adafruit_NeoPixel.h>
#include <modes.h>
#include <stickerpoxpins.h>

Adafruit_NeoPixel stripe(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void (*executeMode) (int);

void resetStripes() {
  reset();

  TMP1 = BLACK;
  TMP2 = BLACK;
  TMP3 = BLACK;
}

int ledNumberAddition(int ledStripeNumber) {
  return 13+ledStripeNumber*100;
}

void showStripes() {
  for(int i=0; i<number_of_stripes; i++) {
    for(int j=0; j<number_of_leds_per_stripe; j++) {
        int lednumber = j + ledNumberAddition(i);
        stripe.setPixelColor(lednumber, leds[i][j].r, leds[i][j].g, leds[i][j].b);
    }
    stripe.show();
  }
}

void beginLeds() {
  pinMode(LED_PIN, OUTPUT);

  stripe.begin();
  stripe.setBrightness(250);
  stripe.show();
}
