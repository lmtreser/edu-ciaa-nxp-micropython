import pyb
rtc = pyb.RTC()

newDt = [2015,12,31,0,20,15,0]
rtc.datetime(newDt)

def rtcCallback(rtc):
    print("Alarm int!")

alarmDt = [2015,12,31,0,20,16,10]
rtc.alarm_datetime(alarmDt,pyb.RTC.MASK_SEC | pyb.RTC.MASK_MIN)
rtc.callback(rtcCallback)

print("alarm:")
print(rtc.alarm_datetime())