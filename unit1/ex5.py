
import struct

# Replace 'event8' with the correct event number for your mouse
event_file = "/dev/input/event11"

with open(event_file, "rb") as f:
    while True:
        data = f.read(24)
        # Unpack the event structure 
        tv_sec, tv_usec, type, code, value = struct.unpack('llHHI', data) 
        # print(f"type: {type}, code: {code}, value: {value}")
        if type == 3:  # EV_REL (relative movement)
            if code == 0:  # X-axis movement
                print(f"dx: {value}")
            elif code == 1:  # Y-axis movement
                print(f"dy: {value}")
