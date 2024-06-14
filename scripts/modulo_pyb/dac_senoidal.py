import pyb
import math

dac = pyb.DAC(1)

# sine
buf = bytearray(200) #100 samples. 2 bytes per sample
j=0
for i in range (0,len(buf)/2):
        v = 512 + int(511 * math.sin(2 * math.pi * i / (len(buf)/2) ) )
        buf[j+1] = (v >>  8) & 0xff
        buf[j] = v & 0xff
        j=j+2

# output the sine-wave at 400Hz
print("sine created")

dac.write_timed(buf, 400*(int(len(buf)/2)), mode=pyb.DAC.CIRCULAR)

while True:
        pyb.delay(1000)