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



def read_measure(Element):
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
    # appropriately
    for child in list(Element):
        if child.tag == "Chord":
            durationTag = child.find("durationType")
            noteTag = child.find("Note")
            pitchTag = noteTag.find("pitch")

            duration = convert_duration(durationTag.text)
            pitch = pitchTag.text 
            print (str(int(pitch)-24) + " " + str (duration))

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
    
    # INFORMATION ABOOUT PIECE
    piece_composer = "Unknown"
    piece_title = "Unknown"
    staff_count = 0;



    # Gets the file to read from user
    music_file = input("Please give a file to load: ")

    # Get xml node to parse
    tree = ET.parse(music_file)
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
                read_measure(measure)



    # Print info about the piece
    print ("Loaded music from file:  " + music_file)
    print ("    " + piece_title + " by " + piece_composer)
    print ("    " + str(staff_count) + " staffs")
