#include <Tone.h>
#include "Notes.cpp"



// Create three tone controllers
Tone buzzer[3];


// The "cursor" for each of the buzzers
unsigned int music_pos[3] = { 0, 0, 0 };
// Holds the length of the music
unsigned int music_length = 9;


// Defines the music
Note Music[3][9] = {
  {
    { NOTE_C4, 10 },
    { NOTE_D4, 10 },
    { NOTE_E4, 10 },
    { NOTE_F4, 10 },
    { NOTE_G4, 10 },
    { NOTE_A4, 10 },
    { NOTE_B4, 10 },
    { NOTE_C5, 20 },
    { NOTE_RST, 10 }
  },
  {
    { NOTE_E4, 10 },
    { NOTE_F4, 10 },
    { NOTE_G4, 10 },
    { NOTE_A4, 10 },
    { NOTE_B4, 10 },
    { NOTE_C5, 10 },
    { NOTE_D5, 10 },
    { NOTE_E5, 20 },
    { NOTE_RST, 10 }
  },
  {
    { NOTE_G4, 10 },
    { NOTE_A4, 10 },
    { NOTE_B4, 10 },
    { NOTE_C5, 10 },
    { NOTE_D5, 10 },
    { NOTE_E5, 10 },
    { NOTE_F5, 10 },
    { NOTE_G5, 20 },
    { NOTE_RST, 10 }
  }
};



void setup()
{
  // Here we initiallize our three piezo buzzers
  buzzer[0].begin(8);
  buzzer[1].begin(9);
  buzzer[2].begin(10);

  // Creates a Serial connection
  Serial.begin(9600);
}



void loop()
{
  for (unsigned int i = 0; i < 3; i++)
  {
    // If the buzzer is not playing
    if (!buzzer[i].isPlaying())
    {
      // Play the next note, advance the cursor
      buzzer[i].play(
        pgm_read_word(Frequency + Music[i][music_pos[i]++].pitch),
        Music[i][music_pos[i]].duration * 20);

      // Wrap the cursor if necessary
      if (music_pos[i] >= music_length) music_pos[i] = 0;
    }
  }
}
