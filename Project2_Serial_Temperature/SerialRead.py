# -*- coding: utf-8 -*-
"""
Created on Sat Feb 15 14:43:29 2020

@author: zacha
"""

import serial
import csv
from datetime import datetime

ser = serial.Serial()
ser.baudrate = 9600;
ser.port = 'COM3'

if ser.is_open:
    ser.close()
    
ser.open()
recording = False
counter = 0;

with open('temperature_data.csv',mode='w') as file:
    
    dataWriter = csv.writer(file,delimiter=',')
    while counter < 70:
        
        if ser.is_open:
            if recording:
                line = ser.readline()
                print(line)
                now = datetime.now()
                currentTime = now.strftime("%H:%M:%S")
                dataWriter.writerow([currentTime,str(float(line))])
                counter += 1
            else:
                    
                a = ser.read()
                print(a)
                if a == (b'!'):
                    print("stabilized")
                    recording = True
                
        
        else:
            print('nope')
            
    ser.close()
        
        