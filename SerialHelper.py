from serial.tools import list_ports # For autodetecting devices
import serial       # For communicating with Arduino
import struct       # For packing data



def select_device():
    '''
    Enters the program into a user input mode where
    the user is given a list of available devices
    and is allowed to pick one
    '''
    
    # Gets a list of available devices
    ports = list_ports.comports()

    # Prints all the devices in a numbered list
    # with their names
    print ("DEVICES FOUND (" + str(len(ports)) + "):")
    for i, p in enumerate(ports):
        print ("  " + str(i+1) + ". " + str(p.device) + "\n")

    # If there are no devices return None
    if (len(ports) == 0): return None

    # Repeatedly asks for a device until a proper
    # number is given, then continues with program
    while True:
        try:
            device_index = int(input("SELECT DEVICE: ")) - 1
            if device_index < len(ports): break
        except: pass

    # Gets the device from the list
    device = ports[device_index-1]
    print(str(device.device) + " selected")

    # Returns the device
    return device



def device_begin(device):
    '''
    Begins connections with the device. This function
    exists purely to keep code pretty
    '''
    
    # Begins serial with device
    ser = serial.Serial(device.device)
    
    # Return the serial connection
    return ser



def pack_short(val):
    '''
    Give a value between 0 and 65546, this will
    convert it to a bytes form compatible with the
    Arduino and return it
    '''
    
    if type(val) != int:
        return None
            
    if val >= 0 and val < 65536:
        return struct.pack("H", val)
    else:
        return None


def device_readline(device):
    '''
    Reads a line from the given device, and strips
    it of \n and \r characters
    '''
    
    # Read a line
    string = device.readline().decode('utf-8')

    # Create a dictionary mapping '\n' and '\r' to
    # None, so they can be removed with translate
    translation_table = dict.fromkeys(map(ord, '\n\r'), None)
    string = string.translate(translation_table)

    # Return the string, now with no special anythings,
    # Just plain text
    return string
