# Módulo utime

Este módulo permite el manejo de fecha y hora usando el módulo RTC.

## Ejemplo

```python
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
```

## Métodos

* localtime([secs]): Convierte un timestamp desde el 1 de enero de 2000 a una tupla de 8 items (year, month, mday, hour, minute, second, weekday, yearday) Si no se le pasan los segundos como argumento, se utilizará la fecha y hora actual tomadas del módulo RTC. El año incluye todos los dígitos (p. ej. 2016) el mes es de 1 a 12 y el día de 1 a 31, las horas de 0 a 23, los minutos de 0 a 59 así como los segundos. el día de la semana va de 0 a 6 y el día del año de 1 a 366.

* mktime(): Es la función inversa a localtime. Recibe como argumento una tupla de 8 items y devuelve la cantidad de segundos desde el 1 de enero de 2000.

* sleep(seconds): Es un delay de la cantidad de segundos pasada como argumento, el cual puede ser un float.

* time(): Devuelve el timestamp en segundos desde el 1 de enero de 2000, tomando la fecha y hora del módulo RTC

NOTA: El módulo RTC debe ser inicializado antes de utilizar el modulo utime.

Mas información en [https://micropython.org/doc/module/time](https://micropython.org/doc/module/time)
