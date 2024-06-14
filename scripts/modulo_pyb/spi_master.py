import pyb

spi = pyb.SPI(8,0,10000)

dataTx = bytearray()
dataTx.append(0x55)
dataTx.append(0x55)
dataTx.append(0x55)
dataTx.append(0x55)

while True:
    print("send:")
    print(dataTx)
    spi.write(dataTx)
    pyb.delay(1000)

    dataRx = spi.read(5)
    print("received:")
    print(dataRx)
    pyb.delay(1000)