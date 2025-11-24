import serial
import time

# Replace 'COM6' with your Outgoing COM port
ser = serial.Serial('COM6', 9600, timeout=1)
time.sleep(2)  # wait for connection to stabilize

print("Connected! Listening for gestures...")

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line:
                print("Received:", line)
except KeyboardInterrupt:
    ser.close()
    print("Disconnected")
