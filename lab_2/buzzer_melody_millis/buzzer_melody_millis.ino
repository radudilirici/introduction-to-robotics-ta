#include "pitches.h"

const byte buzzerPin = 11;

// notes in the melody:
int melody[] = {
  0, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 8, 8, 4, 4, 4, 4, 4
};
const int fullNoteDuration = 1000;
const float pause = 0.3;

int getNoteDurationInMs(int noteDuration) {
  return fullNoteDuration / noteDuration;
}

int getNotePauseInMs(int noteDuration) {
  return fullNoteDuration / noteDuration * (1 + pause);
}

unsigned int lastNoteIndex = 0;
unsigned int lastNotePause = getNotePauseInMs(noteDurations[0]);
unsigned long lastNotePlayedAt = 0;

unsigned int loopCounter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  loopCounter++;
  Serial.print("loopCounter: ");
  Serial.println(loopCounter);

  if (millis() - lastNotePlayedAt > lastNotePause) {
    lastNotePlayedAt = millis();
    int newNoteIndex = lastNoteIndex + 1;
    if (newNoteIndex >= 9) {
      newNoteIndex = 0;
    }
    int noteDuration = getNoteDurationInMs(noteDurations[newNoteIndex]);
    tone(buzzerPin, melody[newNoteIndex], noteDuration);

    lastNoteIndex = newNoteIndex;
    lastNotePause = getNotePauseInMs(noteDurations[newNoteIndex]);
  }
}
