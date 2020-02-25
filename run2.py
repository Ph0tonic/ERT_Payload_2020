#!/usr/bin/env python3.6

from serial import Serial

#port = "/dev/ttyAMA0"
port = "/dev/ttyS0"
try:
	ser = Serial(port,9600,timeout=3.0)
except:
	print("WARNING! Si le port `/dev/ttyS0` n'est pas reconnu ou n'existe pas, suivre la documentation dans le fichier pi.md")
	exit(-1)

def startRecording(_):
	return "Start recording"

def stopRecording(_):
	return "Stop recording"

def customCmd(cmd):
	return 'Cmd `'+cmd+'` treated sucessfully'

def getImage(_):
	# iterable as source
	data = [1, 2, 3, 4] 
	array = bytearray(data)

	ser.write(len(data))
	ser.write(array)

def manageOrder(order):
	switcher = {
		1: startRecording,
		2: stopRecording,
		3: customCmd,
		4: getImage
	}
	params = None
	if(len(order.split(' ', 1)) == 1):
		number = order
	else:
		[number,params] = order.split(' ', 1)
	number = int(number)

	func = switcher.get(number, lambda: "Invalid cmd")
	print(func(params))

def parseCommande(order):
	pass

while True:
	#received = ser.readline()
	received = ser.readline()
	#print(received)
	#print(int.from_bytes(received, "big"))
	#print(int.from_bytes(received, "little"))
	cmd = received.decode('utf-8').rstrip()

	# TODO: Parse commande
	if cmd:
		print("Start managing order : " + cmd)
		manageOrder(cmd)