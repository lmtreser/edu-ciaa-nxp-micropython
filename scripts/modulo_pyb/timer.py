import pyb

def callb(timer):
      print("Interval interrupt")
      print(timer)

def callbTimeout (timer):
      print("Timeout interrupt")
      print(timer)

print("Test Timers")

t1 = pyb.Timer(1)
t2 = pyb.Timer(2)
t1.interval(2000,callb)
t2.timeout(5000,callbTimeout)

while True:
        pyb.delay(1000)