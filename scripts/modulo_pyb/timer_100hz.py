import pyb

counter=0

def callb(timer):
    global counter
    counter+=1

t1 = pyb.Timer(1)
t1.init(freq=100) #100Hz
t1.callback(callb)

while True:
        pyb.delay(1000)
        print("counter:"+str(counter))