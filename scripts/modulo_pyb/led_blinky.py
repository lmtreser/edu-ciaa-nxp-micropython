import pyb

led1 = pyb.LED(3)
pyb.delay(5000)

while True:
    led1.on()
    pyb.delay(100)
    led1.off()
    pyb.delay(100)