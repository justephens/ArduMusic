#include <Tone.h>
#include "Notes.cpp"

#define MAX_MUSIC_LEN 400
#define NUMBER_OF_BUZZERS 2
#define TEMPO 70000

// Create two tone controllers
Tone buzzer[2];

// Holds the time when the buzzers should play to
unsigned long buzzer_target[NUMBER_OF_BUZZERS];


// The "cursor" for each of the buzzers
unsigned int music_pos[NUMBER_OF_BUZZERS];
// Holds the length of the music
unsigned int music_length[NUMBER_OF_BUZZERS];


// Defines the music
Note Music[NUMBER_OF_BUZZERS][MAX_MUSIC_LEN];



void setup()
{
  // Here we initiallize our piezo buzzers, on pins 8+
  for (unsigned int i = 0; i < NUMBER_OF_BUZZERS; i++)
    buzzer[i].begin(8+i);

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
  for (unsigned int i = 0; i < NUMBER_OF_BUZZERS; i++)
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
      buzzer_target[i] += Music[i][music_pos[i]].duration * TEMPO;
      
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
      Serial.println(NUMBER_OF_BUZZERS);


      // Receive data for both buzzers, one after the other.
      // If only data for one buzzer is given, timeout will occur
      for (unsigned int i = 0; i < NUMBER_OF_BUZZERS; i++)
      {
        // Reset the temporary datafields
        dat[0] = 0, dat[1] = 0;
        
        // First two bytes details how many notes will be in the music
        // for this buzzer
        Serial.readBytes(dat, 2);
        music_length[i] = *(unsigned short*)&dat[0];

        // Read the follow data into the music buffer for this buzzer
        Serial.readBytes((byte*)&Music[i][0], music_length[i]*2);
  
        // After loading all the music, reset the buzzers and internal cursors
        buzzer_target[i]  = 0;
        music_pos[i]      = 0;
      }
    }
    
  }
}
