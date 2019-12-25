#include <stickerboxutils.h>

int frameCounter = 0;

void setup() {
  beginLeds();
  Serial.begin(9600);
}

void resetCounter() {
  frameCounter = 0;
}

void setRandomMode() {
  executeMode = modes[random(number_of_modes+1)];
}

void loop() {
  if(frameCounter == 0) {
    resetStripes();
    setRandomMode();
  }

  executeMode(frameCounter);

  showStripes();

  frameCounter++;

  if(frameCounter > frames_per_mode) {
    resetCounter();
  }

  delay(frame_delay);
}
