import pyb

led1 = pyb.LED(3)

while True:
    led1.on()
    pyb.delay(1000)
    led1.off()
    pyb.delay(1000)