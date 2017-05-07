import MuseScoreHelper as MuseScore
import SerialHelper



# Allow the user to select from a list of devices,
# and then form a connection with the given device
device = SerialHelper.select_device()
Arduino = SerialHelper.device_begin(device)



# Asks the user for a file to load music from, and
# loads it into a list of tuples (pitch, duration)
Music = MuseScore.read_file()

# Loop through the musical tuples and build a byte
# array that can be sent to the Arduino
output = bytes([Music[1][0]]) + bytes([Music[1][1]])
for i in Music[2:]:
    output += bytes([i[0]])
    output += bytes([i[1]])



# Write 255 to the Arduino to begin a transmission
Arduino.write(bytes([255]))



# Once the Arduino recieves the starting opcode, it
# will send back the max length of the song
Max_notes       = int(SerialHelper.device_readline(Arduino))
print(str(Max_notes))



# After recieving information about the Arduino, we
# send back a message confirming the number of notes
Arduino.write(SerialHelper.pack_short(9))

print(output[0:Max_notes])
Arduino.write(output[0:Max_notes])


#Arduino.write("R".encode('utf-8'))

#MuseScore.read_file()

