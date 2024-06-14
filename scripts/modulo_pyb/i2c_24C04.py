import pyb
print("Test I2C with AT24C04")

i2c = pyb.I2C(100000) #100Khz
i2c.slave_addr(0x50)

def writeByte(addr,value):
    data = bytearray()
    data.append(addr)
    data.append(value)
    i2c.write(data)

def readBytes(addr,size):
    data = bytearray()
    data.append(addr)    
    i2c.write(data)    
    return i2c.read(size)

writeByte(0x00,11)
pyb.delay(10)
writeByte(0x01,22)
pyb.delay(10)
writeByte(0x02,33)
pyb.delay(10)

data = readBytes(0x00,16)
print("[0]:"+str(data[0]))
print("[1]:"+str(data[1]))
print("[2]:"+str(data[2]))