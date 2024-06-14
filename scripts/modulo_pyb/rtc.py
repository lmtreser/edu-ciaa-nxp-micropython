import pyb
rtc = pyb.RTC()

# (year, month, day, weekday, hours, minutes, seconds)
#newDt = [2015,12,31,0,18,16,0]
#rtc.datetime(newDt)

while True:
    now = rtc.datetime()
    print(now)   
    pyb.delay(1000)