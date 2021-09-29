/* arduino-cli compile --fqbn arduino:avr:uno Piano &&  */
/* arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Piano */

#include "pitches.h"
#include "silence.h"

const int SPEAKER = 10;

int sampleIndex = 0;
void setup() {
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  int sampleDuration = 1000 / sampleRate;
  tone(SPEAKER, samples[sampleIndex]);
  sampleIndex = (sampleIndex + 1) % (sizeof(samples) / sizeof(int));
  delay(sampleDuration);
}
