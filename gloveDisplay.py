import serial
import time

# Windows: BLUETOOTH_PORT = "COM4"
# Mac/Linux: BLUETOOTH_PORT = "/dev/tty.HC-05-DevB"
BLUETOOTH_PORT = "COM4"
BAUD_RATE = 9600

def main():
    print("Connecting to ASL Glove...")
    try:
        bt = serial.Serial(BLUETOOTH_PORT, BAUD_RATE, timeout=1)
        time.sleep(2)
        print("Connected! Listening for gestures...\n")
    except Exception as e:
        print("Could not connect:", e)
        return

    while True:
        try:
            if bt.in_waiting > 0:
                data = bt.readline().decode().strip()

                if data:
                    print(f"[Gesture Received]  {data}")

                    # Save gestures to a log file
                    with open("gesture_log.txt", "a") as f:
                        f.write(data + "\n")

        except KeyboardInterrupt:
            print("\nClosing connection...")
            bt.close()
            break
        except Exception as e:
            print("Error:", e)


if __name__ == "__main__":
    main()

