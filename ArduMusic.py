import MuseScoreHelper as MuseScore
import SerialHelper





while True:
    # Print a menu of available operations
    print ("AVAILABLE OPERATIONS:")
    print ("  1. Connect Device\n")
    print ("  2. Load Music File\n")
    print ("  3. Exit Program\n")
    
    # Loop until valid input is provided
    while True:
        try:
            operation_code = int(input("SELECT OPERATION: "))
            if operation_code >= 1 and operation_code <= 3: break
        except: pass
    
    # Print spacer
    print("\n...\n")
    
    
    
    
    
    # CONNECT DEVICE
    if operation_code == 1:
        # Allow the user to select from a list of devices,
        # and then form a connection with the given device
        device = SerialHelper.select_device()
        if type(device) != None:
            Arduino = SerialHelper.device_begin(device)
        else:
            print("No device found")
        print("\n...\n")


    


    # LOAD MUSIC FILE
    elif operation_code == 2:
        # Asks the user for a file to load music from, and
        # loads it into a list of tuples (pitch, duration)
        Music_Raw = MuseScore.read_file()
        


        # Loop through the music tracks that were returned
        # (one track will be played on one buzzer)
        for i in range(0, len(Music_Raw)):
            print("BUZZER " + str(i) + ":")
            
            for i in Music_Raw[i]:
                print ("  " + str(i[0]) + " " + str(i[1]))



        # Print a divider
        print("\n...\n")

        
        
        # Loop through the musical tuples and build a byte
        # array that can be sent to the Arduino
        output_b1 = bytes(Music_Raw[0][1])
        for i in Music_Raw[0][2:]:
            output_b1 += bytes(i)
            
        output_b2 = bytes(Music_Raw[1][1])
        for i in Music_Raw[1][2:]:
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





    elif operation_code == 3:
        print("Exiting Program")
        break
