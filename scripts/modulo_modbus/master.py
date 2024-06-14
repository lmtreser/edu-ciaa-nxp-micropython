import pyb
import ModBus

uart = pyb.UART(3)
uart.init(115200)

instrument = ModBus.Instrument(uart,0x55,mode=ModBus.MODE_ASCII)
print(instrument)

while True:
    try:
        v = instrument.read_register(1)
        print("Register 1 value :"+str(v))
    except Exception as e:
        print(e)
    pyb.delay(1000)