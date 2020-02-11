import thread
import time
time.sleep(20)
#Don't fight with the Kernel, wait some seconds for prepare device

class _CDC :
    def __init__(self):
        self.dev = "/dev/ttyACM0"
        self.query = ""
    def read(self,_passarg):
        with open("/dev/ttyACM0","r") as readBuff:
            while True :
                ans = readBuff.readline()
                if ans:
                    print(ans[:-2])#Ignore "\r\n" parts ! 
                #time sleep for save cpu clocks
                time.sleep(0.001)
    def write(self,_passarg):
        with open("/dev/ttyACM0","a") as writeBuff:
            while True :
                if self.query != "" :
                    writeBuff.write(self.query+"\n")
                    self.query = ""
                #time sleep for save cpu clocks
                time.sleep(0.001)

CDC = _CDC()
thread.start_new_thread(CDC.read,(None,))
thread.start_new_thread(CDC.write,(None,))

for i in range(30):
    q = "SEND-TEST%02d"%i
    CDC.query = q+((64-len(q))*"\x00")
    time.sleep(0.1)