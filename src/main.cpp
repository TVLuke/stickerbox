#include <stickerboxutils.h>

int frameCounter = 0;

void setup() {
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
    pinMode(LED_PIN3, OUTPUT);

    leds1.begin();
    leds1.show();

    leds2.begin();
    leds2.show();

    leds3.begin();
    leds3.show();

    Serial.begin(9600);
}

void resetCounter() {
  frameCounter = 0;
}

void setRandomMode() {
  int mode = random(8);
  Serial.println(mode);
  if(mode == 0) {
    executeMode = shMode;
  }
  if(mode == 1) {
    executeMode = prideMode;
  }
  if(mode == 2) {
    executeMode = randomMode;
  }
  if(mode == 3) {
    executeMode = wheelMode;
  }
  if(mode == 4) {
    executeMode = alternatingMode;
  }
  if( mode == 5) {
    executeMode = aaaalarmMode;
  }
  if(mode == 6) {
    executeMode = greenMode;
  }
  if(mode == 7) {
    executeMode = redMode;
  }
  if(mode == 8) {
    executeMode = magentaMode;
  }
}

void loop() {
  Serial.println("loop");
  Serial.println(frameCounter);

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
