#include <modeutils.h>

void prideInit(int ledStripeNumber);
void prideInit();
void randomInit();
void wheelInit();
void alternatingInit();

//each of the mode funtions can be randomly selected to be displayed
void shMode(int frame) {
  setcolor(2, BLUE);
  setcolor(1, WHITE);
  setcolor(0, RED);
}

void prideMode(int frame) {
  if(frame == 0) {
    prideInit();
  } else {
    walkForwards();
  }
}

void pride2Mode(int frame) {
  if(frame == 0) {
    prideInit();
  } else {
    if(frame < 500) {
      walkForwards();
    } else {
      walkBackwards();
    }
  }
}

void randomMode(int frame) {
  if(frame == 0) {
    randomInit();
  } else {
    if(frame % 10 == 0) {
      walkForwards();
   }
  }
}

void wheelMode(int frame) {
    if(frame == 0) {
      wheelInit();
    } else {
      walkForwards();
    }
}

void alternatingMode(int frame) {
  if(frame == 0) {
    alternatingInit();
    for(int i=0; i<number_of_stripes; i++) {
      if(i%2 == 1) {
          prideInit(i);
      }
    }
  } else {
    if(frame % 10 == 0) {
      walkForwards();
    } else {
      walkBackwards(1);
    }
  }
}

void aaaalarmMode(int frame) {
  int x = frame / 25;
  if (x%2 == 0) {
    for(int i=0; i<number_of_stripes; i++) {
      if(i%2 == 1) {
        setcolor(i, BLUE);
      } else {
        setcolor(i, RED);
      }
    }
  } else {
    for(int i=0; i<number_of_stripes; i++) {
      if(i%2 == 1) {
        setcolor(i, RED);
      } else {
        setcolor(i, BLUE);
      }
    }
  }
}

void greenMode(int frame) {
  for(int i=0; i<number_of_stripes; i++) {
    setcolor(i, GREEN);
  }
}

void redMode(int frame) {
  for(int i=0; i<number_of_stripes; i++) {
    setcolor(i, RED);
  }
}

void magentaMode(int frame) {
  for(int i=0; i<number_of_stripes; i++) {
    setcolor(i, MAGENTA);
  }
}

void stroboMode(int frame) {
  int x = frame / 15;
  if (x%8 == 1 || x%8 == 3 ) {
      setcolor(WHITE);
    } else {
      setcolor(BLACK);
    }
}

static const int number_of_modes = 10;
void (*modes[number_of_modes])(int) = {prideMode, pride2Mode, randomMode, wheelMode, alternatingMode,
  aaaalarmMode, greenMode, redMode, magentaMode, stroboMode};

//bunch of init functions and stuff
void prideInit(int ledStripeNumber) {
  for(int j=0; j<number_of_leds_per_stripe; j++) {
    leds[ledStripeNumber][j].r = getPrideColor_r(j);
    leds[ledStripeNumber][j].g = getPrideColor_g(j);
    leds[ledStripeNumber][j].b = getPrideColor_b(j);
  }
}

void prideInit() {
  for(int i=0; i<number_of_stripes; i++) {
    prideInit(i);
  }
}

void randomInit() {
  for(int i=0; i<number_of_stripes; i++) {
    for(int j=0; j<number_of_leds_per_stripe; j++) {
      //random values with always 100% saturation
      leds[i][j].r = random(256);
      leds[i][j].g = random(256-leds[i][j].r);
      leds[i][j].b = (255-leds[i][j].r-leds[i][j].g);
    }
  }
}

void wheelInit() {
  for(int i=0; i<number_of_stripes; i++) {
    for(int j=0; j<number_of_leds_per_stripe; j++) {
      leds[i][j].r = getWheel_r(j);
      leds[i][j].g = getWheel_g(j);
      leds[i][j].b = getWheel_b(j);
    }
  }
}

void alternatingInit() {
  for(int i=0; i<number_of_stripes; i++) {
    for(int j=0; j<number_of_leds_per_stripe; j++) {
      if(j%2 == 0) {
        leds[i][j] = WHITE;
      }
    }
  }
}
