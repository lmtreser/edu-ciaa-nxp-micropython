import pyb

rtc = pyb.RTC()
rtc.calibration(0)
newDt = [2015,12,31,0,18,16,0]
rtc.datetime(newDt)