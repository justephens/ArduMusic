#include <Tone.h>
#include "Notes.cpp"



// Create two tone controllers
Tone buzzer[2];

// Holds the time when the buzzers should play to
unsigned long buzzer_target[2] = { 0, 0 };


// The "cursor" for each of the buzzers
unsigned int music_pos[2] = { 0, 0 };
// Holds the length of the music
unsigned int music_length = 9;


// Defines the music
Note Music[2][9] = {
  {
    { NOTE_C4, 10 },
    { NOTE_D4, 10 },
    { NOTE_E4, 10 },
    { NOTE_F4, 10 },
    { NOTE_G4, 10 },
    { NOTE_A4, 10 },
    { NOTE_B4, 10 },
    { NOTE_C5, 20 },
    { NOTE_RST, 20 }
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
    { NOTE_RST, 20 }
  }
};



void setup()
{
  // Here we initiallize our three piezo buzzers
  buzzer[0].begin(9);
  buzzer[1].begin(10);

  // Creates a Serial connection
  Serial.begin(9600);
}



void loop()
{
  // Taking a "snapshot" of the microseconds at the start of a loop
  // will help us ensure the same value is sampled for both buzzers,
  // thus removing drift in the time between buzzers
  unsigned long micro_snapshot = micros();


  // Iterate through both buzzers
  for (unsigned int i = 0; i < 2; i++)
  {

    // Check if it's time for the buzzer to stop
    if (micro_snapshot >= buzzer_target[i])
    {
      
      // Increment the music pointer, wrap it to begin if necessary
      music_pos[i]++;
      if (music_pos[i] >= music_length) music_pos[i] = 0;

      
      // Stop buzzer, play next note (as long as it's not a rest)
      buzzer[i].stop();
      if (Music[i][music_pos[i]].pitch != pgm_read_word(Frequency + NOTE_RST))
        buzzer[i].play(pgm_read_word(Frequency + Music[i][music_pos[i]].pitch));


      // Set the time to stop playing
      buzzer_target[i] += Music[i][music_pos[i]].duration * 50000;
      
    }
    
  }
}
