#include <Tone.h>
#include "Notes.cpp"



// Create two tone controllers
Tone buzzer[2];

// Holds the time when the buzzers should play to
unsigned long buzzer_target[2] = { 0, 0 };


// The "cursor" for each of the buzzers
unsigned int music_pos[2] = { 0, 0 };
// Holds the length of the music
unsigned int music_length[2] = { 9, 9 };


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
    { NOTE_RST, 10 },
    { NOTE_RST, 10 },
    { NOTE_RST, 10 },
    { NOTE_RST, 10 },
    { NOTE_RST, 10 },
    { NOTE_RST, 10 },
    { NOTE_RST, 10 },
    { NOTE_RST, 20 },
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
  Serial.print(F("Testing Python Communication with Arduino..."));
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
      if (music_pos[i] >= music_length[i]) music_pos[i] = 0;

      
      // Stop buzzer, play next note (as long as it's not a rest)
      buzzer[i].stop();
      if (Music[i][music_pos[i]].pitch != pgm_read_word(Frequency + NOTE_RST))
        buzzer[i].play(pgm_read_word(Frequency + Music[i][music_pos[i]].pitch));


      // Set the time to stop playing
      buzzer_target[i] += Music[i][music_pos[i]].duration * 50000;
      
    }
    
  }


  if (Serial.available())
  {
    // Check the start of the transmission
    byte opcode = 0;
    byte dat[4] = { 0, 0, 0, 0 };  // Some bytes to store temporary data in
    Serial.readBytes(&opcode, 1);
    Serial.print(opcode);

    // Check to see if it's the opening of a music transfer
    if (opcode == OP_MUSIC)
    {
      buzzer[0].stop();
      buzzer[1].stop();

      
      Serial.print(F("Music Transfer initiated"));
      // Immediately following the opening OPcode should be a short detailing
      // how many notes there are
      Serial.readBytes(dat, 2);
      if (*(unsigned short*)&dat[0] == 9) Serial.print("Y");
      else Serial.print("N");

      // If no data was read then skip again to the start of the loop
      //if (*(unsigned short*)&dat[0] == 0) return;

      
      music_length[0] = *(unsigned short*)&dat[0];
      Serial.readBytes((byte*)&Music[0][0], 9*2);


      // After loading all the music, reset the buzzers and internal cursors
      buzzer_target[0]  = 0;
      buzzer_target[1]  = 0;
      music_pos[0]      = 0;
      music_pos[1]      = 0;
    }
  }
}
