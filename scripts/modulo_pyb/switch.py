import pyb

switch1 = pyb.Switch(1)

while True:
    val = switch1.switch()
    print('sw1:'+str(val))
    pyb.delay(200)