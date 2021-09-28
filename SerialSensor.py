import serial
import string
ser = serial.Serial('/dev/ttyACM0',9600)

while True:
    serialData=ser.readline()
    print(serialData)
    