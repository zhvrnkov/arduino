// run
/* arduino-cli compile --fqbn arduino:avr:uno Piano &&  */
/* arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Piano */

// debug serial
// putty /dev/ttyACM0 -serial -sercfg 9600,8,n,1,N &g

const int POT = 5;
const int SPEAKER = 10;
const int BUTTON_C = 9;
const int BUTTON_D = 8;
const int BUTTON_E = 7;
const int BUTTON_F = 6;
const int BUTTON_G = 5;
const int BUTTON_A = 4;
const int BUTTON_B = 3;
const int BUTTON_X = 2;

#include "pitches.h"

int state = LOW;

//Note Array
int notes[] = {
 NOTE_A3, NOTE_E2, NOTE_A3, 0, 
 NOTE_A3, NOTE_E2, NOTE_A3, 0,
 NOTE_E3, NOTE_D3, NOTE_C3, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3,
 NOTE_E3, NOTE_E2, NOTE_A3, 0
};

//The Duration of each note (in ms)
int times[] = {
 250, 250, 250, 250, 
 250, 250, 250, 250,
 125, 125, 125, 125, 125, 125, 125, 125,
 250, 250, 250, 250 
};

typedef struct {
  int number;
  int duration;
} Note;

void setup() {
  pinMode(SPEAKER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  /* for (int i = 0; i < sizeof(notes) / sizeof(int); i++) { */
  /*   tone(SPEAKER, notes[i], times[i]); */
  /*   delay(times[i]); */
  /* } */
  int octave = pot_to_octave(analogRead(POT));
  int bn = base_note(octave);
  Serial.print(octave);
  
  while (digitalRead(BUTTON_C))
    tone(SPEAKER, note_frequency(0, bn));
  while (digitalRead(BUTTON_D))
    tone(SPEAKER, note_frequency(2, bn));
  while (digitalRead(BUTTON_E))
    tone(SPEAKER, note_frequency(4, bn));
  while (digitalRead(BUTTON_F))
    tone(SPEAKER, note_frequency(5, bn));
  while (digitalRead(BUTTON_G))
    tone(SPEAKER, note_frequency(7, bn));
  while (digitalRead(BUTTON_A))
    tone(SPEAKER, note_frequency(9, bn));
  while (digitalRead(BUTTON_B))
    tone(SPEAKER, note_frequency(11, bn));
  while (digitalRead(BUTTON_X))
    tone(SPEAKER, note_frequency(12, bn));
  noTone(SPEAKER);
}

int isButtonPressed(int BUTTON) {
  static int lastButton;
  int isButtonPressed1 = digitalRead(BUTTON) == HIGH;
  delay(5);
  int isButtonPressed2 = digitalRead(BUTTON) == HIGH;
  int isButtonPressed = isButtonPressed1 && isButtonPressed2;
  int lastButtonValue = lastButton;
  lastButton = isButtonPressed;
  return isButtonPressed && lastButtonValue == LOW;
}

int note_frequency(int n, int f0) {
  float twelth_root = 1.05946;
  return f0 * pow(twelth_root, n);
}

// pot_val is in [0...1023] range
int pot_to_octave(int pot_val) {
  int octaves_count = 7;
  return (pot_val + 1) / (1024 / octaves_count);
}

int base_note(int octave) {
  switch (octave) {
  case 0:
    return NOTE_C1;
  case 1:
    return NOTE_C2;
  case 2:
    return NOTE_C3;
  case 3:
    return NOTE_C4;
  case 4:
    return NOTE_C5;
  case 5:
    return NOTE_C6;
  case 6:
    return NOTE_C7;
  case 7:
    return NOTE_C8;
  }
}
