#include <Tone.h>
#include "Notes.cpp"

// Create three tone controllers
Tone buzzer[3];


Note Music[3][9] = {
  { NOTE_C4, 10 },
  { NOTE_D4, 10 },
  { NOTE_E4, 10 },
  { NOTE_F4, 10 },
  { NOTE_G4, 10 },
  { NOTE_A4, 10 },
  { NOTE_B4, 10 },
  { NOTE_C5, 20 },
  { NOTE_RST, 100 }
};

void setup()
{
  // Here we initiallize our three piezo buzzers
  buzzer[0].begin(8);
  buzzer[1].begin(9);
  buzzer[2].begin(10);

  // Creates a Serial connection
  Serial.begin(9600);
  Serial.print("Program Begin \n");
  Serial.print("Note size:");
  Serial.println(sizeof(Note));
}

void loop()
{
  for (unsigned int i = 0; i < 9; i++)
  {
    // Play or stop the music
    buzzer[0].play(
      Frequency[Music[i].pitch],
      Music[i].duration * 20);
  
    // Wait until the next note
    while (buzzer[0].isPlaying());
  }
}

