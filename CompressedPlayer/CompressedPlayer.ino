/* arduino-cli compile --fqbn arduino:avr:uno Piano &&  */
/* arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Piano */

#include "pitches.h"
#include "whole_star_wars.h"

const int SPEAKER = 10;

int sampleIndex = 0;
void setup() {
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  int sampleDuration = 1000 / sampleRate;
  int index = sampleIndex * 2;
  int note = samples[index];
  int times = samples[index + 1];
  tone(SPEAKER, note);
  sampleIndex = (sampleIndex + 1) % (sizeof(samples) / sizeof(int) / 2);
  delay(sampleDuration * times);
}
