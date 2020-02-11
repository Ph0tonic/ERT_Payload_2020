#!/usr/bin/env python3.6

import serial

ser = serial.Serial("/dev/ttyS0",9600,timeout=1)
while True:
	received = ser.readline()
	print(received.decode('utf-8'))