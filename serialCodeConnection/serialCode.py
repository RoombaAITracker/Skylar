# https://roboticsbackend.com/raspberry-pi-arduino-serial-communication/
import serial
import time

# need to change the serial file path, baud rate has to be the same
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1.0)
time.sleep(3)
ser.reset_input_buffer()
print("Serial OK")

try:
    while True:
        time.sleep(0.01)
        print("Send message to arduino")
        ser.write("Hello from Raspberry Pi\n".encode('utf-8'))

except KeyboardInterrupt:
    print("Close Serial Communcation")
    ser.close()