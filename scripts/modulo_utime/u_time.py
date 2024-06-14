import pyb
import utime

print("utime Test")

rtc = pyb.RTC()

while True:
    now = rtc.datetime()
    print(now)

    ts = utime.time()
    print("timestamp:"+str(ts))
    dateTimeTuple = utime.localtime(ts)
    print(dateTimeTuple)
    ts = utime.mktime(dateTimeTuple)
    print("mktime timestamp:"+str(ts))
    print("__________________________")

    utime.sleep(1)
