import MuseScoreHelper as MuseScore
import SerialHelper



# Allow the user to select from a list of devices,
# and then form a connection with the given device
device = SerialHelper.select_device()
Arduino = SerialHelper.device_begin(device)
print("\n...\n")




# Asks the user for a file to load music from, and
# loads it into a list of tuples (pitch, duration)
Music_Raw = MuseScore.read_file()
Music_b1 = Music_Raw[0]
Music_b2 = Music_Raw[1]

print("BUZZER 1:")
for i in Music_b1:
    print ("  " + str(i[0]) + " " + str(i[1]))

print("BUZZER 2:")
for i in Music_b2:
    print ("  " + str(i[0]) + " " + str(i[1]))
    
print("\n...\n")


# Loop through the musical tuples and build a byte
# array that can be sent to the Arduino
output_b1 = bytes(Music_b1[1])
for i in Music_b1[2:]:
    output_b1 += bytes(i)
    
output_b2 = bytes(Music_b2[1])
for i in Music_b2[2:]:
    output_b2 += bytes(i)

print(output_b1)
print(output_b2)




# Write 255 to the Arduino to begin a transmission
Arduino.write(bytes([255]))

# The Arduino will send back the maximum notes it
# can handle (this is per-buzzer). From this we
# decide how many we are actually going to send
Max_notes       = int(SerialHelper.device_readline(Arduino))
Num_buzzers     = int(SerialHelper.device_readline(Arduino))
Num_notes       = Max_notes if int(len(output_b1)/2) > Max_notes else int(len(output_b1)/2)


# Send a message dictating how many notes will be sent
# to the Arduino
Arduino.write(SerialHelper.pack_short(Num_notes))

# Next we send the note output for Buzzer one
Arduino.write(output_b1[0:Num_notes*2])


# Send a message dictating how many notes will be sent
# to the Arduino
Arduino.write(SerialHelper.pack_short(Num_notes))

# Next we send the note output for Buzzer one
Arduino.write(output_b2[0:Num_notes*2])



# Print a nice overview at the end
print("Music Transfer Complete:")
print("  Arduino with " + str(Num_buzzers) + " buzzers")
print("  " + str(Num_notes) + " notes transferred")
