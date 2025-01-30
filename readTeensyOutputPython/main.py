import serial

# Replace with the serial port path of your adapter
SERIAL_PORT = "/dev/cu.usbserial-B001AW6G"  # Example, replace with your actual port
BAUD_RATE = 9600  # Must match the baud rate used in your Teensy code

try:
    # Open the serial port
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        print(f"Listening on {SERIAL_PORT} at {BAUD_RATE} baud...\n")

        while True:
            if ser.in_waiting > 0:  # Check if data is available
                data = ser.readline().decode('utf-8').strip()  # Read a line of data
                print(f"Received: {data}")
except serial.SerialException as e:
    print(f"Error: {e}")
except KeyboardInterrupt:
    print("\nExiting program.")
