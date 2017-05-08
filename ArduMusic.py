import MuseScoreHelper as MuseScore
import SerialHelper



# Allow the user to select from a list of devices,
# and then form a connection with the given device
device = SerialHelper.select_device()
Arduino = SerialHelper.device_begin(device)
print("\n...\n")




# Asks the user for a file to load music from, and
# loads it into a list of tuples (pitch, duration)
Music = MuseScore.read_file()
print("\n...\n")


# Loop through the musical tuples and build a byte
# array that can be sent to the Arduino
output = bytes([Music[1][0]]) + bytes([Music[1][1]])
for i in Music[2:]:
    output += bytes([i[0]])
    output += bytes([i[1]])





# Write 255 to the Arduino to begin a transmission
Arduino.write(bytes([255]))

# The Arduino will send back the maximum notes it
# can handle (this is per-buzzer). From this we
# decide how many we are actually going to send
Max_notes       = int(SerialHelper.device_readline(Arduino))
Num_notes       = Max_notes if int(len(output)/2) > Max_notes else int(len(output)/2)

Num_buzzers     = int(SerialHelper.device_readline(Arduino))

# Send a message dictating how many notes will be sent
Arduino.write(SerialHelper.pack_short(Num_notes))

# Send the data up to the requested size by the Arduino
# We multiply by 2 because each note takes up 2 bytes
Arduino.write(output[0:Num_notes*2])



# Print a nice overview at the end
print("Music Transfer Complete:")
print("  Arduino with " + str(Num_buzzers) + " buzzers")
print("  " + str(Num_notes) + " notes transferred")
