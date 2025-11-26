##########################################################################################
# This code connects to the HC-05 bluetooth component of the arduino on COM6 for Windows #
# (Will be different on mac, still needs testing on mac)                                 #
# The code also displays a GUI the shows the letter detected                             #
# Author: Vinh Tran                                                                      #
##########################################################################################

import serial
import time
import threading
import tkinter as tk
from tkinter import scrolledtext

# Windows = COM6
# Mac = /dev/cu.HC-05
BLUETOOTH_PORT = "/dev/cu.HC-05"
BAUD_RATE = 9600

def read_from_bluetooth(bt_serial, text_widget):
    while True:
        try:
            if bt_serial.in_waiting > 0:
                data = bt_serial.readline().decode(errors='ignore').strip()
                if data:
                    text_widget.insert(tk.END, f"{data}\n")
                    text_widget.see(tk.END)
                    with open("gesture_log.txt", "a") as f:
                        f.write(data + "\n")
        except serial.SerialException:
            print("Serial connection lost.")
            break
        except Exception as e:
            print("Error:", e)
            break

def start_connection():
    try:
        bt = serial.Serial(BLUETOOTH_PORT, BAUD_RATE, timeout=2)
        time.sleep(3)  # allow HC-05 to stabilize
        print("Connected to ASL Glove!")
        status_label.config(text="Connected!", fg="green")
        
        # Start reading in a separate thread
        threading.Thread(target=read_from_bluetooth, args=(bt, text_area), daemon=True).start()
    except Exception as e:
        print("Could not connect:", e)
        status_label.config(text=f"Connection failed: {e}", fg="red")

# --- GUI setup ---
root = tk.Tk()
root.title("ASL Glove Bluetooth Monitor")

status_label = tk.Label(root, text="Not connected", fg="red")
status_label.pack(pady=5)

text_area = scrolledtext.ScrolledText(root, width=50, height=20)
text_area.pack(padx=10, pady=10)

connect_button = tk.Button(root, text="Connect to ASL Glove", command=start_connection)
connect_button.pack(pady=5)

root.mainloop()
