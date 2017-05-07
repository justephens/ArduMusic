#include <Tone.h>
#include "Notes.cpp"

#define MAX_MUSIC_LEN 9


// Create two tone controllers
Tone buzzer[2];

// Holds the time when the buzzers should play to
unsigned long buzzer_target[2] = { 0, 0 };


// The "cursor" for each of the buzzers
unsigned int music_pos[2] = { 0, 0 };
// Holds the length of the music
unsigned int music_length[2] = { 0, 0 };


// Defines the music
Note Music[2][MAX_MUSIC_LEN];



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
      if (music_pos[i] >= music_length[i]) music_pos[i] = 0;

      
      // Stop buzzer, play next note (as long as it's not a rest)
      buzzer[i].stop();
      if (Music[i][music_pos[i]].pitch != pgm_read_word(Frequency + NOTE_RST))
        buzzer[i].play(pgm_read_word(Frequency + Music[i][music_pos[i]].pitch));


      // Set the time to stop playing
      buzzer_target[i] += Music[i][music_pos[i]].duration * 50000;
      
    }
    
  }



  // If there is incoming Serial communication
  if (Serial.available())
  {
    
    // Check the start of the transmission
    byte opcode = 0;
    byte dat[2] = { 0, 0 };  // Some bytes to store temporary data in
    Serial.readBytes(&opcode, 1);

    // Check to see if it's the opening of a music transfer
    if (opcode == OP_MUSIC)
    {
      // Once the opcode is verified, send data about the arduino
      Serial.println(MAX_MUSIC_LEN);
      
      // Immediately following the opening OPcode should be a short detailing
      // how many notes there are for the first buzzer
      Serial.readBytes(dat, 2);
      
      // Get the length of the music and buffer that many x2 bytes (one byte
      // for pitch, one for duration) into the music array
      music_length[0] = *(unsigned short*)&dat[0];
      Serial.readBytes((byte*)&Music[0][0], music_length[0]*2);


      // After loading all the music, reset the buzzers and internal cursors
      buzzer_target[0]  = 0;
      buzzer_target[1]  = 0;
      music_pos[0]      = 0;
      music_pos[1]      = 0;
    }
    
  }
}
