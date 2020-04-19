# General structure

The avionic of payload is composed of 2 parts and can be controlled by the groundstation via a RF communication.
Those 2 parts are the following:
- 1 board with a teensy 3.5 which serve as a controller
- 1 raspberry pi 3

The first one is is the main component of our avionic and interfaces with all the captors and the rf module. Our raspberry pi is only use to control the camera and the recoring of the experiment. The board is able to shutdown the raspberry pi via a shutdown pin such as to minimize the running time of the pi and therefore try to lower the heat generated.

has there is two main components, we have 2 program.
One on the board in c++ and the second in python run on the pi. They are communication via a RX/TX serial pins.

## Main board program

The main code has been modularized into kind of modules by clearly extracting interactions with captors and physicals component inside a file each. This structure allows to easily update and replace some portion of the code.

Here are the different files/modules :
- xbee
- bme
- bmo
- buzzer
- led
- pi

## Raspberry pi program

This program consist of a main loop which is waiting for event comming from the teensy board. Messages are encoded in the following way :
- 
