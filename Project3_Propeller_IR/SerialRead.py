# -*- coding: utf-8 -*-

import serial
import csv
from datetime import datetime
import matplotlib.pyplot as plt
import matplotlib

ser = serial.Serial()
ser.baudrate = 9600;
ser.port = 'COM3'

if ser.is_open:
    ser.close()
    
ser.open()
recording = False
counter = 0;

data = []
time = []       
begin = datetime.now(); 
plt.close()

font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 22}

matplotlib.rc('font', **font)
   

with open('RPM_data.csv',mode='w') as file:
    
    dataWriter = csv.writer(file,delimiter=',')
    while counter < 1000:
        
        if ser.is_open:
            line = ser.readline()
            print(str(float(line)))
            now = datetime.now()
            currentTime = now.strftime("%H:%M:%S")
            diffTime = now-begin;
            data.append(float(line))
            time.append(diffTime.total_seconds())
            plt.cla
            plt.plot(time,data,color = 'blue')
            plt.xlabel('Time (s)')
            plt.ylabel('RPM')
            plt.title('RPM vs. Time')
            plt.pause(0.05)
            plt.show()
            
            dataWriter.writerow([currentTime,str(float(line))])
            counter += 1

        else:
            print('nope')
            
    ser.close()
        
        