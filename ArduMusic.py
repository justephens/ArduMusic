import MuseScoreHelper as MuseScore
import SerialHelper

device  = SerialHelper.select_device()
Arduino = SerialHelper.device_begin(device)


val = int(input("Pitch: "))
output = bytes([val])
val = int(input("Duration: "))
output += bytes([val])

for i in range(0, 8):
    try:
        val = int(input("Pitch: "))
        output += bytes([val])
        val = int(input("Duration: "))
        output += bytes([val])
    except:
        print("invalid")
        pass

print(Arduino.read(44))

Arduino.write(bytes([255]))
print(Arduino.read(3))

print(Arduino.read(24))

Arduino.write(SerialHelper.pack_short(9))
print(Arduino.read(1))

Arduino.write(output)


#Arduino.write("R".encode('utf-8'))

#MuseScore.read_file()

