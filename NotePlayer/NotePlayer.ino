#include "pitches.h"
#include "melody.h"

const int SPEAKER = 10;

const int bpm = 120;
const int noteDuration = 4 / (bpm / 60) * 1000;

void setup() {
  pinMode(SPEAKER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int notesCount = sizeof(melody) / sizeof(int) / 2;
  int total_duration = 0;
  for (int i = 0; i < notesCount; i++) {
    int position = i * 2;
    int note = melody[position];
    int part = melody[position + 1];
    int duration;
    if (part > 0) {
      duration = noteDuration / part;
    } else if (part < 0) {
      duration = noteDuration / abs(part);
      duration *= 1.5;
    }
    tone(SPEAKER, note, duration * 0.9);
    delay(duration);
    total_duration += duration;
  }
}
