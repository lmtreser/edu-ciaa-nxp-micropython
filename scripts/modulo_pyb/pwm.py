import pyb

pyb.PWM.set_frequency(1000)

out0 = pyb.PWM(0)
out0.duty_cycle(50) # 50%
print("Duty cycle :"+str(out0.duty_cycle()))

out1= pyb.PWM(1)
out1.duty_cycle(25)

out10= pyb.PWM(10)
out10.duty_cycle(75)

while True:
        pyb.delay(1000)