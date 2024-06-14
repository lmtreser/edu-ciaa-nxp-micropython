import pyb
import ModBus

uart = pyb.UART(3)
uart.init(115200)
led1 = pyb.LED(1)

mappedRegs = {0x4000 : 0x0000 , 0x4001 : 0x0000}

modbus = ModBus.Slave(uart,0x55,mappedRegs,mode=ModBus.MODE_ASCII)
print(modbus)

print(mappedRegs)

while True:
    if modbus.receive():
        print(mappedRegs)
        if mappedRegs[0x4000]==0:
            led1.off()
        else:
            led1.on() 