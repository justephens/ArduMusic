import xml.etree.ElementTree as ET    # For parsing XML (Savefile)



def convert_pitch(note):
    '''
    Given a pitch from a MuseScore savefile, this
    function converts it to the format used by the
    Arduino.
    '''
    
    # C1 on the Arduino is represented by integer 0,
    # while MuseScore C1 is represented by 24.
    if type(note) == int and note > 24 and note < 112:
        return note-24;
    
    # If an invalid integer is given, return a rest.
    return 88;



def convert_duration(duration):
    '''
    This function returns a numeric value given a
    string that contains an english duration
    '''
    
    if type(duration) != str    : return 0
    elif duration == "measure"  : return 32
    elif duration == "whole"    : return 32
    elif duration == "half"     : return 16
    elif duration == "quarter"  : return 8
    elif duration == "eighth"   : return 4
    elif duration == "16th"     : return 2
    elif duration == "32nd"     : return 1
    else                        : return 0



def read_measure(Element, Music):
    '''
    This function is used to abstract the parsing
    process by handling the parsing for a <Measure>
    tag in the file
    '''
    
    # Verify this tag defines a Measure
    if type(Element) != ET.Element: return False
    if Element.tag != "Measure": return False

    # Loop through the children of the measure,
    # and handle each type (chord, rest, timesig)
    for child in list(Element):
        if child.tag == "Chord":
            durationTag = child.find("durationType")
            duration = convert_duration(durationTag.text)

            # Loop through all the notes in a chord
            for i, noteTag in enumerate(child.findall("Note")):
                if i >= 2: break
                # Finds the pitch and duration
                pitchTag = noteTag.find("pitch")
                pitch = pitchTag.text

                # Adds this note to the music
                Music[i].append((int(pitch)-24, duration))

            # If there were fewer than 2 notes in
            # the chord, the rest the second buzzer
            if (len(child.findall("Note")) < 2):
                Music[1].append((int(88), duration))



        '''
        elif child.tag == "Rest":
            durationTag = child.find("durationType")
            duration = read_duration(durationTag.text)
            
            print("Rest")
        elif child.tag == "TimeSig":
            print("TimeSig")
        '''


def read_file():
    '''
    This function enters the program into a routine
    where the user enters a MuseScore save file to
    be loaded and returned
    '''

    # The music storage device to be used
    Music = ([(int, int)],[(int, int)])
    
    # INFORMATION ABOOUT PIECE
    piece_composer = "Unknown"
    piece_title = "Unknown"
    staff_count = 0;


    # The xml tree
    tree = None
    
    # Continually asks for a file to load until a
    # valid file is opened or "exit" is typed
    while True:
        # Get file to load, append file extension
        # if none given
        music_file = input("Please give a file to load: ")
        if '.' not in music_file: music_file += '.mscx'

        # Attempt to load file, repeat loop if load
        # fails, otherwise break the loop
        try:
            tree = ET.parse(music_file)
            break
        except:
            pass


    root = tree.getroot()
    Score = tree.find("Score")


    for child in Score:
        # GET INFORMATION ABOUT PIECE
        if child.tag == "metaTag":
            if child.attrib["name"] == "composer":
                piece_composer = child.text
            elif child.attrib["name"] == "workTitle":
                piece_title = child.text

        # Count the number of Staffs
        if child.tag == "Part":
            for x in child.findall("Staff"):
                staff_count += 1

        # Parse the measures in the Staff declaration
        if child.tag == "Staff":
            i = 0
            for measure in child.findall("Measure"):
                read_measure(measure, Music)



    # Print info about the piece
    print ("Loaded music from file:  " + music_file)
    print ("    " + str(piece_title) + " by " + str(piece_composer))
    print ("    " + str(staff_count) + " staffs")


    # Return the list of tuples
    return Music
