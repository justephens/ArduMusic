from serial.tools import list_ports # For autodetecting devices
import serial       # For communicating with Arduino



def select_device():
    '''
    Enters the program into a user input mode where
    the user is given a list of available devices
    and is allowed to pick one
    '''
    
    # Gets a list of available devices and checks
    # that there is at least one connected
    ports = list_ports.comports()
    if (len(ports) == 0): return None

    # Prints all the devices in a numbered list
    # with their names
    print ("DEVICES FOUND (" + str(len(ports)) + "):")
    for i, p in enumerate(ports):
        print ("  " + str(i+1) + ". " + str(p.device) + "\n")

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
