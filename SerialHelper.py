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
    if val >= 0 and val < 65536:
        return struct.pack("H", val)
    else:
        return None
