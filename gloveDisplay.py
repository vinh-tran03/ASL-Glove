import serial
import time
import tkinter as tk
from tkinter import scrolledtext

# Replace with the Outgoing COM port of your HC-05
BLUETOOTH_PORT = "COM6"
BAUD_RATE = 9600

def read_from_bluetooth(bt_serial, text_widget):
    while True:
        try:
            if bt_serial.in_waiting > 0:
                data = bt_serial.readline().decode(errors='ignore').strip()
                if data:
                    text_widget.insert(tk.END, f"{data}\n")
                    text_widget.see(tk.END)  # scroll to bottom
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
        time.sleep(3)  # wait for Bluetooth connection to stabilize
        print("Connected to ASL Glove!")
        status_label.config(text="Connected!", fg="green")
        read_from_bluetooth(bt, text_area)
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
