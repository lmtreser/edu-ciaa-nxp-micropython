import pyb
rtc = pyb.RTC()

#rtc.write_bkp_reg(0,27)
#rtc.write_bkp_reg(32,28)
#rtc.write_bkp_reg(63,29)

while True:
    print(rtc.read_bkp_reg(0))
    print(rtc.read_bkp_reg(32))
    print(rtc.read_bkp_reg(63))
    pyb.delay(1000)