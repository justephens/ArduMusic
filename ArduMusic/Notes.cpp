#include <avr/pgmspace.h>



/* Redifines all the NOTE macros to hold indices instead of values. These indices
 * match up with the proper value, which is stored in the Pitches[] array. In this
 * way, we can store byte indices instead of unsigned short frequencies, saving us
 * space which means more complex songs.
 */
#define NOTE_C1  0
#define NOTE_CS1 1
#define NOTE_D1  2
#define NOTE_DS1 3
#define NOTE_E1  4
#define NOTE_F1  5
#define NOTE_FS1 6
#define NOTE_G1  7
#define NOTE_GS1 8
#define NOTE_A1  9
#define NOTE_AS1 10
#define NOTE_B1  11
#define NOTE_C2  12
#define NOTE_CS2 13
#define NOTE_D2  14
#define NOTE_DS2 15
#define NOTE_E2  16
#define NOTE_F2  17
#define NOTE_FS2 18
#define NOTE_G2  19
#define NOTE_GS2 20
#define NOTE_A2  21
#define NOTE_AS2 22
#define NOTE_B2  23
#define NOTE_C3  24
#define NOTE_CS3 25
#define NOTE_D3  26
#define NOTE_DS3 27
#define NOTE_E3  28
#define NOTE_F3  29
#define NOTE_FS3 30
#define NOTE_G3  31
#define NOTE_GS3 32
#define NOTE_A3  33
#define NOTE_AS3 34
#define NOTE_B3  35
#define NOTE_C4  36
#define NOTE_CS4 37
#define NOTE_D4  38
#define NOTE_DS4 39
#define NOTE_E4  40
#define NOTE_F4  41
#define NOTE_FS4 42
#define NOTE_G4  43
#define NOTE_GS4 44
#define NOTE_A4  45
#define NOTE_AS4 46
#define NOTE_B4  47
#define NOTE_C5  48
#define NOTE_CS5 49
#define NOTE_D5  50
#define NOTE_DS5 51
#define NOTE_E5  52
#define NOTE_F5  53
#define NOTE_FS5 54
#define NOTE_G5  55
#define NOTE_GS5 56
#define NOTE_A5  57
#define NOTE_AS5 58
#define NOTE_B5  59
#define NOTE_C6  60
#define NOTE_CS6 61
#define NOTE_D6  62
#define NOTE_DS6 63
#define NOTE_E6  64
#define NOTE_F6  65
#define NOTE_FS6 66
#define NOTE_G6  67
#define NOTE_GS6 68
#define NOTE_A6  69
#define NOTE_AS6 70
#define NOTE_B6  71
#define NOTE_C7  72
#define NOTE_CS7 73
#define NOTE_D7  74
#define NOTE_DS7 75
#define NOTE_E7  76
#define NOTE_F7  77
#define NOTE_FS7 78
#define NOTE_G7  79
#define NOTE_GS7 80
#define NOTE_A7  81
#define NOTE_AS7 82
#define NOTE_B7  83
#define NOTE_C8  84
#define NOTE_CS8 85
#define NOTE_D8  86
#define NOTE_DS8 87
#define NOTE_RST 88

/* Signifies the start of a music transfer */
#define OP_MUSIC 255

/* Stores the pitches that can be played. When a macro NOTE is used as an index in
 * this array, it will yield the proper pitch. Ex: Pitches[NOTE_C4] will give 262
 */
const unsigned short Frequency[] PROGMEM =
{
	33,		35,		37,		39,		41,		44,		46,		49,		52,		55,		58,		62,
	65,		69,		73,		78,		82,		87,		93,		98,		104,	110,	117,	123,
	131,	139,	147,	156,	165,	175,	185,	196,	208,	220,	233,	247,
	262,	277,	294,	311,	330,	349,	370,	392,	415,	440,	466,	494,
	523,	554,	587,	622,	659,	698,	740,	784,	831,	880,	932,	988,
	1047,	1109,	1175,	1245,	1319,	1397,	1480,	1568,	1661,	1760,	1865,	1976,
	2093,	2217,	2349,	2489,	2637,	2794,	2960,	3136,	3322,	3520,	3729,	3951,
	4186,	4435,	4699,	4978,	0
};



/* This struct holds a Note and duration for use in storing music  */
struct Note {
  // Holds the index of the note
  char pitch;

  // Holds the duration of the note
  char duration;



  // Automatically init to 0
  Note()
    : pitch(0), duration(0)
  {}
  // If values are given on initialization
  Note(char p, unsigned short d)
    : pitch(p), duration(d)
  {}
};

