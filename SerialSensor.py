import serial
import string
import csv
from datetime import datetime, timezone
ser = serial.Serial('/dev/ttyACM0',9600)
HEADER = ['time', 'rotation', 'velocity']

#what should be sent to ser = velocity and the "steps" from the optical encoder (delimited by a / )
  
def getData(csvFile):
    fileWriter = csv.writer(csvFile)
    fileWriter.writerow(HEADER)
    
    while True:
        serialData=ser.readline().decode('utf-8').split("\\")
        print("Counter: "+ serialData[0] + "\t" + "Velocity" + serialData[1])
     
        # get time
        utc_dt = datetime.now(timezone.utc) #UTC time with milliseconds included
        timeMS = utc_dt.astimezone().strftime('%H:%M:%S.%f')[:-3]
        info =[timeMS, int(serialData[0]), float(serialData[1])]
        fileWriter.writerow(info)
        csvFile.flush()
        
with open ('filename.csv', 'w') as csvFile:
    getData(csvFile)