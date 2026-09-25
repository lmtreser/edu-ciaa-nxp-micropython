# EDU-CIAA-NXP — Cheatsheet `pyb`

> DOCUMENTO PRELIMINAR -SIN REVISIÓN-

Referencia rápida para el port de MicroPython 1.5.2 de la EDU-CIAA-NXP basada en LPC4337.

> **Importante:** esta documentación corresponde al port específico de la EDU-CIAA-NXP. No asumir que una API de `pyb` de versiones modernas de MicroPython funciona de la misma manera.

## 1. Acceso al módulo

```python
import pyb
```

También es posible importar clases individualmente:

```python
from pyb import LED
from pyb import Pin
from pyb import ADC
```

Forma recomendada para ejemplos:

```python
import pyb

led = pyb.LED(1)
```

## 2. Resumen de hardware soportado

| Recurso             | Clase      |   Cantidad |
| ------------------- | ---------- | ---------: |
| LEDs individuales   | `LED`      |  6 canales |
| Pulsadores          | `Switch`   |          4 |
| GPIO                | `Pin`      |          9 |
| ADC                 | `ADC`      |          3 |
| DAC                 | `DAC`      |          1 |
| PWM                 | `PWM`      | 11 salidas |
| Timers              | `Timer`    |          4 |
| Interrupciones GPIO | `ExtInt`   |          4 |
| UART                | `UART`     |          1 |
| RS-485              | `UART`     |          1 |
| SPI                 | `SPI`      |          1 |
| I²C                 | `I2C`      |          1 |
| RTC                 | `RTC`      |          1 |
| EEPROM              | `EEPROM`   |      16 KB |
| LCD HD44780         | `LCD`      |          1 |
| Teclado matricial   | `Keyboard` |  hasta 4×4 |

Módulos de software documentados:

```text
json
math
utime
modbus
```

## 3. LED

### Constructor

```python
led = pyb.LED(n)
```

Valores:

```text
1 → LED 1
2 → LED 2
3 → LED 3
4 → RGB Red
5 → RGB Green
6 → RGB Blue
```

### Métodos

```python
led.on()
led.off()
led.toggle()
led.value()
led.intensity(value)
```

`value()` devuelve:

```text
True  → encendido
False → apagado
```

`intensity()` solamente es válido para los canales RGB.

Rango:

```text
0 ... 15
```

### Ejemplo

```python
import pyb

led = pyb.LED(1)

while True:
    led.on()
    pyb.delay(500)

    led.off()
    pyb.delay(500)
```

### RGB

```python
import pyb

red = pyb.LED(4)
green = pyb.LED(5)
blue = pyb.LED(6)

red.intensity(15)
green.intensity(0)
blue.intensity(0)
```

## 4. Switch

Los cuatro pulsadores se acceden mediante:

```python
sw = pyb.Switch(n)
```

Valores:

```text
1 ... 4
```

### Lectura

```python
sw.switch()
```

Devuelve:

```text
True  → pulsado
False → no pulsado
```

### Callback

```python
def callback(sw):
    print("Pulsador presionado")

sw = pyb.Switch(1)
sw.callback(callback)
```

El callback recibe como argumento el objeto `Switch`.

### Ejemplo

```python
import pyb

sw = pyb.Switch(1)

while True:
    print(sw.switch())
    pyb.delay(200)
```

### Ejemplo con interrupción/callback

```python
import pyb

def pressed(sw):
    print("SW1")

sw = pyb.Switch(1)
sw.callback(pressed)

while True:
    pyb.delay(1000)
```

## 5. GPIO — `Pin`

La EDU-CIAA expone 9 GPIO:

```text
GPIO 0 ... GPIO 8
```

### Constructor

```python
p = pyb.Pin(0)
```

### Modos

```python
pyb.Pin.IN
pyb.Pin.OUT_PP
pyb.Pin.OUT_OD
```

Significado:

```text
IN       → entrada
OUT_PP   → salida Push-Pull
OUT_OD   → salida Open Drain
```

### Pull-up / pull-down

```python
pyb.Pin.PULL_NONE
pyb.Pin.PULL_UP
pyb.Pin.PULL_DOWN
```

## Configuración

```python
p.init(mode)
```

o:

```python
p.init(mode, pull)
```

Ejemplo:

```python
p.init(
    pyb.Pin.OUT_PP,
    pyb.Pin.PULL_NONE
)
```

### Salida

```python
p.high()
p.low()
```

### Lectura

```python
value = p.value()
```

Devuelve:

```text
0
1
```

### Ejemplo

```python
import pyb

p = pyb.Pin(0)

p.init(
    pyb.Pin.OUT_PP,
    pyb.Pin.PULL_NONE
)

while True:
    p.high()
    pyb.delay(500)

    p.low()
    pyb.delay(500)
```

### Entrada

```python
import pyb

p = pyb.Pin(0)
p.init(
    pyb.Pin.IN,
    pyb.Pin.PULL_UP
)

while True:
    print(p.value())
    pyb.delay(100)
```

## 6. ADC

La EDU-CIAA dispone de tres entradas analógicas:

```text
ADC(1)
ADC(2)
ADC(3)
```

### Constructor

```python
adc = pyb.ADC(n)
```

### Lectura

```python
value = adc.read()
```

Resolución:

```text
10 bits
```

Rango:

```text
0 ... 1023
```

Referencia:

```text
3.3 V
```

Conversión aproximada:

```python
voltage = adc.read() * 3.3 / 1023
```

### Ejemplo

```python
import pyb

adc = pyb.ADC(1)

while True:
    value = adc.read()
    voltage = value * 3.3 / 1023

    print(value)
    print(voltage)

    pyb.delay(500)
```

### Tres canales

```python
import pyb

adc1 = pyb.ADC(1)
adc2 = pyb.ADC(2)
adc3 = pyb.ADC(3)

while True:
    print(adc1.read())
    print(adc2.read())
    print(adc3.read())

    pyb.delay(100)
```

## 7. DAC

La EDU-CIAA dispone de una salida DAC:

```python
dac = pyb.DAC(1)
```

Resolución:

```text
10 bits
```

Rango:

```text
0 ... 1023
```

Fondo de escala:

```text
3.3 V
```

### Escritura

```python
dac.write(value)
```

Ejemplo:

```python
import pyb

dac = pyb.DAC(1)

dac.write(0)
pyb.delay(1000)

dac.write(512)
pyb.delay(1000)

dac.write(1023)
```

### Conversión tensión → cuenta

Aproximadamente:

```python
value = voltage * 1023 / 3.3
```

Ejemplo:

```python
dac.write(int(1.65 * 1023 / 3.3))
```

## 8. DAC — ruido

```python
dac.noise(f)
```

Genera una señal pseudoaleatoria de 256 muestras.

Rango documentado:

```text
1 ... 400000 Hz
```

Ejemplo:

```python
import pyb

dac = pyb.DAC(1)

dac.noise(1000)

while True:
    pyb.delay(1000)
```

## 9. DAC — triangular

```python
dac.triangle(f)
```

Ejemplo:

```python
import pyb

dac = pyb.DAC(1)

dac.triangle(1000)

while True:
    pyb.delay(1000)
```

## 10. DAC — `write_timed()`

Permite reproducir una tabla de muestras utilizando DMA.

```python
dac.write_timed(data, freq, mode)
```

Modos:

```python
pyb.DAC.NORMAL
pyb.DAC.CIRCULAR
```

`NORMAL`:

```text
reproduce una vez
```

`CIRCULAR`:

```text
repite continuamente
```

### Ejemplo de seno

```python
import pyb
import math

dac = pyb.DAC(1)

samples = 100

buf = bytearray(samples * 2)

j = 0

for i in range(samples):
    v = 512 + int(
        511 * math.sin(
            2 * math.pi * i / samples
        )
    )

    buf[j + 1] = (v >> 8) & 0xff
    buf[j] = v & 0xff

    j += 2

frequency = 400 * samples

dac.write_timed(
    buf,
    frequency,
    mode=pyb.DAC.CIRCULAR
)

while True:
    pyb.delay(1000)
```

## 11. PWM

El port implementa:

```python
pyb.PWM
```

Hay 11 salidas:

| Canal | Pin    |
| ----: | ------ |
|     0 | GPIO_2 |
|     1 | GPIO_8 |
|     2 | T_FIL1 |
|     3 | T_FIL2 |
|     4 | T_FIL3 |
|     5 | T_COL0 |
|     6 | T_COL1 |
|     7 | T_COL2 |
|     8 | LCD_1  |
|     9 | LCD_2  |
|    10 | LCD_3  |

### Importante

Existe un único módulo PWM con 11 salidas.

Por lo tanto:

```text
frecuencia → común a todas las salidas
duty cycle → independiente por canal
```

### Configurar frecuencia

```python
pyb.PWM.set_frequency(1000)
```

### Crear canal

```python
pwm = pyb.PWM(0)
```

### Duty cycle

```python
pwm.duty_cycle(50)
```

Rango:

```text
0 ... 100 %
```

### Leer duty cycle

```python
value = pwm.duty_cycle()
```

### Ejemplo

```python
import pyb

pyb.PWM.set_frequency(1000)

pwm = pyb.PWM(0)

pwm.duty_cycle(50)

while True:
    pyb.delay(1000)
```

### Varios canales

```python
import pyb

pyb.PWM.set_frequency(1000)

pwm0 = pyb.PWM(0)
pwm1 = pyb.PWM(1)
pwm2 = pyb.PWM(2)

pwm0.duty_cycle(25)
pwm1.duty_cycle(50)
pwm2.duty_cycle(75)
```

## 12. Timers

Timers disponibles:

```text
0
1
2
3
```

Constructor:

```python
timer = pyb.Timer(1)
```

### `interval()`

Ejecuta periódicamente una función:

```python
timer.interval(t, callback)
```

`t` está expresado en milisegundos.

Ejemplo:

```python
import pyb

def callback(timer):
    print("tick")

timer = pyb.Timer(1)

timer.interval(
    1000,
    callback
)

while True:
    pyb.delay(100)
```

### `timeout()`

Ejecuta una función una sola vez después del intervalo:

```python
timer.timeout(t, callback)
```

Ejemplo:

```python
import pyb

def callback(timer):
    print("timeout")

timer = pyb.Timer(1)

timer.timeout(
    5000,
    callback
)

while True:
    pyb.delay(1000)
```

### `init(freq=...)`

```python
timer.init(freq=100)
```

Rango documentado:

```text
1 ... 1000000 Hz
```

### Callback

```python
timer.callback(callback)
```

La función recibe el objeto `Timer`.

Ejemplo:

```python
import pyb

counter = 0

def callback(timer):
    global counter
    counter += 1

timer = pyb.Timer(1)

timer.init(freq=100)
timer.callback(callback)

while True:
    pyb.delay(1000)
    print(counter)
```

### `counter()`

Leer:

```python
value = timer.counter()
```

Escribir:

```python
timer.counter(0)
```

### `freq()`

Leer:

```python
f = timer.freq()
```

Escribir:

```python
timer.freq(1000)
```

### `period()`

Leer:

```python
p = timer.period()
```

Escribir:

```python
timer.period(value)
```

### `prescaler()`

Leer:

```python
p = timer.prescaler()
```

Escribir:

```python
timer.prescaler(value)
```

### `source_freq()`

```python
f = timer.source_freq()
```

Devuelve la frecuencia de operación del microcontrolador en Hz.

### Limitación

Este port **no implementa `TimerChannel`**.

Por lo tanto no están disponibles mediante esta API las funciones de:

```text
Output Compare
Input Capture
```

## 13. Interrupciones GPIO — `ExtInt`

Permite generar interrupciones ante cambios en GPIO.

### Constructor

```python
extint = pyb.ExtInt(
    pin,
    mode,
    pull,
    callback
)
```

Modos documentados:

```python
pyb.ExtInt.IRQ_RISING
```

También se dispone de los modos correspondientes a las distintas condiciones de interrupción implementadas por el port.

### Ejemplo

```python
import pyb

def callback(line):
    print("Interrupción")
    print(line)

p = pyb.Pin(8)

p.init(
    pyb.Pin.OUT_PP,
    pyb.Pin.PULL_NONE
)

extint = pyb.ExtInt(
    p,
    pyb.ExtInt.IRQ_RISING,
    pyb.Pin.PULL_NONE,
    callback
)

while True:
    pyb.delay(1000)
```

El callback recibe el objeto/línea de interrupción.

### Métodos

```python
extint.enable()
extint.disable()
extint.swint()
extint.line()
```

El port dispone de:

```text
4 líneas de interrupción
```

que pueden asignarse a las GPIO disponibles.

## 14. UART

La clase:

```python
pyb.UART
```

se utiliza tanto para UART como para RS-485.

### Interfaces

```text
UART(0) → RS-485
UART(3) → UART
```

### Constructor

```python
uart = pyb.UART(3)
```

## 15. UART — `init()`

Forma general:

```python
uart.init(
    baudrate,
    bits=8,
    parity=None,
    stop=1,
    timeout=1000,
    timeout_char=1,
    read_buf_len=64,
    packet_mode=False,
    packet_end_char=...
)
```

#### `baudrate`

Velocidad:

```python
115200
```

#### `bits`

El port soporta:

```text
8
```

#### `parity`

Valores documentados:

```text
None → sin paridad
1    → impar
2    → par
3    → F1
4    → F2
```

#### `stop`

```text
1
2
```

bits de stop.

#### `timeout`

Tiempo de espera de recepción en ms.

#### `timeout_char`

Tiempo entre bytes durante transmisión/recepción.

#### `read_buf_len`

Tamaño del buffer.

Máximo documentado:

```text
2048 bytes
```

#### `packet_mode`

```python
False
```

recepción por bytes.

```python
True
```

recepción por paquetes/tramas.

#### `packet_end_char`

Carácter utilizado como delimitador de fin de trama en el modo correspondiente.

## 16. UART — transmisión

```python
uart.write(data)
```

`data` puede ser:

```text
string
bytearray
```

Ejemplo:

```python
import pyb

uart = pyb.UART(3)

uart.init(
    115200,
    bits=8,
    parity=None,
    stop=1
)

uart.write("Hola mundo\r\n")
```

### `writechar()`

```python
uart.writechar(ch)
```

Envía un carácter.

## 17. UART — recepción

### `any()`

```python
if uart.any():
    ...
```

Indica si existe información recibida.

### `readchar()`

```python
ch = uart.readchar()
```

Espera hasta el timeout. Si no hay datos:

```text
-1
```

Si hay datos:

```text
byte recibido
```

### `read()`

```python
data = uart.read()
```

o:

```python
data = uart.read(n)
```

Devuelve un `bytearray`.

### `readall()`

```python
data = uart.readall()
```

### `readinto()`

```python
buffer = bytearray(64)

uart.readinto(buffer)
```

También:

```python
uart.readinto(buffer, nbytes)
```

## 18. UART — ejemplo completo

```python
import pyb

uart = pyb.UART(3)

uart.init(
    115200,
    bits=8,
    parity=None,
    stop=1,
    timeout=500,
    timeout_char=1,
    read_buf_len=64
)

uart.write("EDU-CIAA\r\n")

while True:

    if uart.any():

        data = uart.readall()

        print(data)

    pyb.delay(10)
```

## 19. RS-485

El RS-485 de la EDU-CIAA se accede mediante:

```python
uart = pyb.UART(0)
```

La API es esencialmente la misma que UART. Ejemplo:

```python
import pyb

rs485 = pyb.UART(0)

rs485.init(
    115200,
    bits=8,
    parity=None,
    stop=1,
    timeout=500,
    timeout_char=1,
    read_buf_len=128
)

rs485.write("HELLO\r\n")
```

Esto permite implementar protocolos propios o utilizar el módulo Modbus disponible en el proyecto.

## 20. UART — recepción por paquetes

El port agrega un modo específico de recepción por trama.

```python
uart.init(
    115200,
    bits=8,
    parity=None,
    stop=1,
    timeout=200,
    timeout_char=1,
    read_buf_len=64,
    packet_mode=True
)
```

En este modo:

```python
uart.any()
```

Indica que se recibió una trama completa. Luego:

```python
data = uart.readall()
```

Obtiene la trama. Esto es especialmente útil para protocolos simples:

```text
PC → EDU-CIAA

<STX> comando datos <ETX>
```

## 21. EEPROM

La EDU-CIAA dispone de una EEPROM interna accesible mediante:

```python
eeprom = pyb.EEPROM()
```

Capacidad documentada:

```text
16 KB
```

### Byte

Escribir:

```python
eeprom.write_byte(addr, value)
```

Leer:

```python
value = eeprom.read_byte(addr)
```

### Entero de 32 bits

```python
eeprom.write_int(addr, value)

value = eeprom.read_int(addr)
```

### Float

```python
eeprom.write_float(addr, value)

value = eeprom.read_float(addr)
```

### String

Escribir desde `0x0000`:

```python
eeprom.write("Hola")
```

Leer:

```python
text = eeprom.readall()
```

## 22. EEPROM

Ejemplo:

```python
import pyb

eeprom = pyb.EEPROM()

eeprom.write_byte(
    0x0000,
    0x27
)

value = eeprom.read_byte(
    0x0000
)

print(hex(value))
```

### Enteros

```python
eeprom.write_int(
    0x0000,
    0x11223344
)

value = eeprom.read_int(
    0x0000
)

print(hex(value))
```

### Float

```python
eeprom.write_float(
    0x0000,
    3.14
)

value = eeprom.read_float(
    0x0000
)

print(value)
```

## 23. EEPROM + JSON

Una aplicación muy útil es almacenar configuración.

```python
import pyb
import json

config = {
    "baudrate": 115200,
    "device": 3,
    "gain": 2.5
}

text = json.dumps(config)

eeprom = pyb.EEPROM()

eeprom.write(text)
```

Recuperar:

```python
text = eeprom.readall()

config = json.loads(text)

print(config)
```

Esto permite usar la EEPROM como almacenamiento persistente de parámetros.

## 24. SPI

El port implementa SPI Master.

### Constructor

```python
spi = pyb.SPI(
    bits,
    mode,
    frequency
)
```

Valores de bits:

```text
4
8
16
```

Modo:

```text
0
1
2
3
```

Frecuencia en Hz.
Ejemplo:

```python
spi = pyb.SPI(
    8,
    0,
    100000
)
```

## 25. SPI — escribir

```python
data = bytearray()

data.append(0x55)
data.append(0xAA)

spi.write(data)
```

### Leer

```python
data = spi.read(5)
```

Devuelve un `bytearray`.

## 26. SPI — ejemplo

```python
import pyb

spi = pyb.SPI(
    8,
    0,
    100000
)

tx = bytearray([
    0x55,
    0xAA,
    0x01,
    0x02
])

spi.write(tx)

rx = spi.read(4)

print(rx)
```

## 27. I²C

El port implementa:

```text
I²C Master
```

### Constructor

```python
i2c = pyb.I2C(frequency)
```

Velocidades documentadas:

```text
100000 Hz
400000 Hz
```

Ejemplo:

```python
i2c = pyb.I2C(100000)
```

## 28. I²C — dirección

La dirección del esclavo se establece mediante:

```python
i2c.slave_addr(address)
```

Ejemplo:

```python
i2c.slave_addr(0x50)
```

## 29. I²C — escribir

```python
data = bytearray([
    0x00,
    0x55
])

i2c.write(data)
```

## 30. I²C — leer

```python
data = i2c.read(16)
```

Devuelve un `bytearray`.

## 31. I²C — ejemplo EEPROM 24C04

```python
import pyb

i2c = pyb.I2C(100000)

i2c.slave_addr(0x50)

data = bytearray([
    0x00,
    0x27
])

i2c.write(data)

pyb.delay(10)

data = bytearray([
    0x00
])

i2c.write(data)

result = i2c.read(16)

print(result)
```

## 32. RTC

Constructor:

```python
rtc = pyb.RTC()
```

### Leer fecha/hora

```python
now = rtc.datetime()
```

Formato:

```text
(year,
 month,
 day,
 weekday,
 hours,
 minutes,
 seconds)
```

Ejemplo:

```python
import pyb

rtc = pyb.RTC()

while True:
    print(rtc.datetime())
    pyb.delay(1000)
```

## 33. RTC — establecer fecha/hora

```python
datetime = [
    2026,
    9,
    24,
    4,
    23,
    30,
    0
]

rtc.datetime(datetime)
```

Formato:

```text
año
mes
día
día_semana
hora
minuto
segundo
```

El día de semana utiliza:

```text
0 ... 6
```

## 34. RTC — calibración

```python
rtc.calibration(value)
```

Rango documentado:

```text
-131072 ... 131072
```

Ejemplo:

```python
rtc.calibration(0)
```

Después de calibrar se recomienda volver a establecer fecha y hora.

## 35. RTC — backup registers

Hay:

```text
64 registros
```

de:

```text
32 bits
```

Lectura:

```python
value = rtc.read_bkp_reg(n)
```

Escritura:

```python
rtc.write_bkp_reg(n, value)
```

Rango de registros:

```text
0 ... 63
```

Ejemplo:

```python
rtc.write_bkp_reg(
    0,
    1234
)

value = rtc.read_bkp_reg(0)

print(value)
```

Son útiles para conservar pequeños estados a través de un reset del CPU.

## 36. RTC — alarma

Configurar:

```python
rtc.alarm_datetime(
    datetime,
    mask
)
```

La fecha utiliza el mismo formato de `datetime()`.

### Máscaras

```python
pyb.RTC.MASK_SEC
pyb.RTC.MASK_MIN
pyb.RTC.MASK_HR
pyb.RTC.MASK_DAY
pyb.RTC.MASK_MON
pyb.RTC.MASK_YR
pyb.RTC.MASK_DOW
```

Se pueden combinar:

```python
mask = (
    pyb.RTC.MASK_SEC |
    pyb.RTC.MASK_MIN
)
```

### Callback

```python
def alarm_callback(rtc):
    print("ALARMA")

rtc.callback(alarm_callback)
```

### Deshabilitar

```python
rtc.alarm_disable()
```

## 37. LCD HD44780

El port implementa LCD compatible con:

```text
HD44780U
```

### Constructor

```python
lcd = pyb.LCD(
    lines,
    character_format
)
```

Líneas:

```text
1
2
3
4
```

Formato:

```text
0 → 5×8
1 → 5×10
```

Ejemplo:

```python
lcd = pyb.LCD(2, 0)
```

## 38. LCD — limpiar

```python
lcd.clear()
```

## 39. LCD — escribir

```python
lcd.write("Hola")
```

También se pueden utilizar saltos de línea:

```python
lcd.write(
    "EDU-CIAA\nMicroPython"
)
```

## 40. LCD — posición

```python
lcd.goto_xy(x, y)
```

Ejemplo:

```python
lcd.goto_xy(0, 0)
lcd.write("Hola")

lcd.goto_xy(0, 1)
lcd.write("Mundo")
```

## 41. LCD — cursor

```python
lcd.config_cursor(
    visible,
    blink
)
```

Ejemplo:

```python
lcd.config_cursor(
    True,
    True
)
```

Activa:

```text
cursor visible
blink
```

## 42. LCD — ejemplo completo

```python
import pyb

lcd = pyb.LCD(2, 0)

lcd.clear()

lcd.write(
    "EDU-CIAA\n"
    "MicroPython"
)

pyb.delay(2000)

lcd.clear()

lcd.config_cursor(
    True,
    True
)

counter = 0

while True:

    counter += 1

    lcd.goto_xy(0, 0)
    lcd.write("Counter:")

    lcd.goto_xy(10, 0)
    lcd.write(str(counter))

    pyb.delay(1000)
```

## 43. Teclado matricial

Constructor:

```python
keyboard = pyb.Keyboard(
    rows,
    columns
)
```

Ejemplo 4×4:

```python
keyboard = pyb.Keyboard(4, 4)
```

Pines utilizados:

```text
T_FIL0
T_FIL1
T_FIL2
T_FIL3

T_COL0
T_COL1
T_COL2
GPIO8 / T_COL3
```

## 44. Keyboard — `get_char()`

```python
key = keyboard.get_char()
```

Es bloqueante.

Espera hasta que se presione una tecla.

El resultado contiene:

```text
4 bits superiores → fila
4 bits inferiores → columna
```

## 45. Keyboard — `get_matrix()`

```python
key = keyboard.get_matrix()
```

No es bloqueante.

Si no se presiona ninguna tecla:

```text
0xFF
```

## 46. Ejemplo teclado

```python
import pyb

keyboard = pyb.Keyboard(4, 4)

while True:

    key = keyboard.get_char()

    print(
        "key:",
        hex(key)
    )
```

## 47. Funciones de tiempo de `pyb`

La implementación utilizada por el port incluye las funciones de temporización históricas de `pyb`.

### Delay

```python
pyb.delay(ms)
```

Ejemplo:

```python
pyb.delay(1000)
```

Espera:

```text
1000 ms = 1 segundo
```

### Milisegundos

```python
t = pyb.millis()
```

Obtiene el contador de milisegundos.

### Microsegundos

```python
t = pyb.micros()
```

Obtiene el contador de microsegundos.

### Tiempo transcurrido

```python
elapsed = pyb.elapsed_millis(start)
```

y:

```python
elapsed = pyb.elapsed_micros(start)
```

Ejemplo:

```python
start = pyb.millis()

# trabajo...

print(
    pyb.elapsed_millis(start)
)
```

## 48. Medición de tiempos

Patrón recomendado:

```python
start = pyb.micros()

# código a medir

elapsed = pyb.elapsed_micros(start)

print(elapsed)
```

Para tiempos largos:

```python
start = pyb.millis()

# ...

print(
    pyb.elapsed_millis(start)
)
```

## 49. Arquitectura típica de un programa

Para esta versión de MicroPython es conveniente mantener el programa sencillo:

```python
import pyb

led = pyb.LED(1)
sw = pyb.Switch(1)

while True:

    if sw.switch():
        led.on()
    else:
        led.off()

    pyb.delay(10)
```

## 50. Máquina de estados

La EDU-CIAA es suficientemente potente para utilizarla como plataforma de enseñanza de máquinas de estados:

```python
import pyb

led = pyb.LED(1)

state = 0

while True:

    if state == 0:
        led.off()

        if ...:
            state = 1

    elif state == 1:
        led.on()

        if ...:
            state = 0

    pyb.delay(10)
```

## 51. ADC + PWM

Ejemplo clásico de control:

```python
import pyb

adc = pyb.ADC(1)

pyb.PWM.set_frequency(1000)

pwm = pyb.PWM(0)

while True:

    value = adc.read()

    duty = value * 100 // 1023

    pwm.duty_cycle(duty)

    pyb.delay(10)
```

Resultado:

```text
potenciómetro
     ↓
    ADC
     ↓
  0...1023
     ↓
0...100 %
     ↓
   PWM
```

## 52. ADC + DAC

Conversión directa:

```python
import pyb

adc = pyb.ADC(1)
dac = pyb.DAC(1)

while True:

    value = adc.read()

    dac.write(value)

    pyb.delay(1)
```

Esto permite construir un experimento básico de:

```text
ADC → procesamiento → DAC
```

## 53. ADC + UART

```python
import pyb

adc = pyb.ADC(1)

uart = pyb.UART(3)

uart.init(
    115200,
    bits=8,
    parity=None,
    stop=1
)

while True:

    value = adc.read()

    uart.write(
        str(value) + "\r\n"
    )

    pyb.delay(100)
```

Esto permite convertir la EDU-CIAA en un dispositivo de adquisición controlado desde una PC.

## 54. Timer + ADC

```python
import pyb

adc = pyb.ADC(1)

samples = 0

def callback(timer):

    global samples

    samples = adc.read()

timer = pyb.Timer(1)

timer.init(
    freq=100
)

timer.callback(callback)

while True:

    print(samples)

    pyb.delay(1000)
```

Frecuencia de adquisición:

```text
100 Hz
```

## 55. Interrupción + LED

```python
import pyb

led = pyb.LED(1)

p = pyb.Pin(8)

p.init(
    pyb.Pin.IN,
    pyb.Pin.PULL_UP
)

def callback(line):

    led.toggle()

extint = pyb.ExtInt(
    p,
    pyb.ExtInt.IRQ_RISING,
    pyb.Pin.PULL_UP,
    callback
)

while True:
    pyb.delay(1000)
```

## 56. RGB

Los tres canales RGB son:

```python
red = pyb.LED(4)
green = pyb.LED(5)
blue = pyb.LED(6)
```

Ejemplo:

```python
red.intensity(15)
green.intensity(0)
blue.intensity(0)
```

Cian:

```python
red.intensity(0)
green.intensity(15)
blue.intensity(15)
```

Blanco:

```python
red.intensity(15)
green.intensity(15)
blue.intensity(15)
```

Negro/apagado:

```python
red.intensity(0)
green.intensity(0)
blue.intensity(0)
```

## 57. Tabla rápida de clases

```text
pyb.LED(n)
    on()
    off()
    toggle()
    value()
    intensity(value)

pyb.Switch(n)
    switch()
    callback(fn)

pyb.Pin(n)
    init(mode, pull)
    high()
    low()
    value()

pyb.ADC(n)
    read()

pyb.DAC(n)
    write(value)
    noise(freq)
    triangle(freq)
    write_timed(data, freq, mode)

pyb.PWM(n)
    duty_cycle()
    duty_cycle(value)

pyb.PWM
    set_frequency(freq)

pyb.Timer(n)
    interval(ms, fn)
    timeout(ms, fn)
    init(...)
    callback(fn)
    counter()
    counter(value)
    freq()
    freq(value)
    period()
    period(value)
    prescaler()
    prescaler(value)
    source_freq()

pyb.ExtInt(...)
    enable()
    disable()
    swint()
    line()

pyb.UART(n)
    init(...)
    write(data)
    writechar(ch)
    get_baudrate()
    any()
    readchar()
    read()
    readall()
    readinto()

pyb.EEPROM()
    write_byte()
    read_byte()
    write_int()
    read_int()
    write_float()
    read_float()
    write()
    readall()

pyb.SPI(...)
    write()
    read()

pyb.I2C(freq)
    slave_addr()
    write()
    read()

pyb.RTC()
    datetime()
    datetime(value)
    calibration()
    calibration(value)
    read_bkp_reg()
    write_bkp_reg()
    alarm_datetime()
    alarm_datetime(...)
    callback()
    alarm_disable()

pyb.LCD(...)
    clear()
    write()
    goto_xy()
    config_cursor()

pyb.Keyboard(rows, cols)
    get_char()
    get_matrix()
```

## 58. Mapa conceptual

```text
                         pyb
                          │
       ┌──────────────────┼──────────────────┐
       │                  │                  │
    DIGITAL            ANALOG             TIEMPO
       │                  │                  │
   ┌───┼───┐          ┌───┴───┐          ┌───┴───┐
   │   │   │          │       │          │       │
 LED SW  Pin         ADC     DAC       Timer    RTC
   │       │
   │       └── ExtInt
   │
   └── PWM

       ┌───────────────────────────────────────┐
       │           COMUNICACIONES              │
       ├─────────┬─────────┬─────────┬─────────┤
       │         │         │         │
      UART     RS-485     SPI       I2C
       │
     Modbus

       ┌───────────────────────────────────────┐
       │             INTERFAZ                  │
       ├──────────────────┬────────────────────┤
       │                  │
      LCD              Keyboard

       ┌───────────────────────────────────────┐
       │            PERSISTENCIA               │
       ├──────────────────┬────────────────────┤
       │                  │
     EEPROM              RTC
```

## 59. Lo que NO hay que asumir de MicroPython moderno

Este port es histórico y específico. No asumir automáticamente la existencia de:

```python
machine.Pin
machine.I2C
machine.SPI
machine.UART
```

ni reemplazar:

```python
pyb.Pin
```

por:

```python
machine.Pin
```

La interfaz principal de este firmware es:

```python
pyb
```

Tampoco asumir:

```python
TimerChannel
```

porque no fue implementado en este port.

## 60. Limitaciones importantes del port

La documentación específica de la EDU-CIAA indica que:

* `TimerChannel` no está implementado.
* SPI funciona como Master.
* I²C funciona como Master.
* UART soporta 8 bits.
* PWM comparte frecuencia entre todos los canales.
* ADC tiene resolución de 10 bits.
* DAC tiene resolución de 10 bits.
* Hay 3 canales ADC.
* Hay un solo DAC.
* EEPROM tiene 16 KB.
* Existen 4 líneas de interrupción GPIO.
* Los timers disponibles son 0, 1, 2 y 3.

Por tanto, para desarrollar software sobre esta placa hay que tomar esta implementación como una plataforma propia, no como una simple instalación de MicroPython genérico.

## 61. Chuleta mínima para tener al lado de la placa

```python
import pyb

# LED
led = pyb.LED(1)
led.on()
led.off()
led.toggle()

# RGB
r = pyb.LED(4)
g = pyb.LED(5)
b = pyb.LED(6)
r.intensity(15)

# SWITCH
sw = pyb.Switch(1)
print(sw.switch())

# GPIO
p = pyb.Pin(0)
p.init(pyb.Pin.OUT_PP, pyb.Pin.PULL_NONE)
p.high()
p.low()
print(p.value())

# ADC
adc = pyb.ADC(1)
value = adc.read()

# DAC
dac = pyb.DAC(1)
dac.write(512)

# PWM
pyb.PWM.set_frequency(1000)
pwm = pyb.PWM(0)
pwm.duty_cycle(50)

# TIMER
t = pyb.Timer(1)
t.init(freq=100)
t.callback(fn)

# UART
uart = pyb.UART(3)
uart.init(115200)
uart.write("Hola\r\n")
if uart.any():
    data = uart.readall()

# RS485
rs485 = pyb.UART(0)
rs485.init(115200)

# SPI
spi = pyb.SPI(8, 0, 100000)
spi.write(bytearray([0x55]))
data = spi.read(4)

# I2C
i2c = pyb.I2C(100000)
i2c.slave_addr(0x50)
i2c.write(bytearray([0x00, 0x55]))
data = i2c.read(4)

# EEPROM
eeprom = pyb.EEPROM()
eeprom.write_byte(0, 123)
print(eeprom.read_byte(0))

# RTC
rtc = pyb.RTC()
print(rtc.datetime())

# LCD
lcd = pyb.LCD(2, 0)
lcd.clear()
lcd.goto_xy(0, 0)
lcd.write("Hola")

# KEYBOARD
keyboard = pyb.Keyboard(4, 4)
key = keyboard.get_char()

# TIME
pyb.delay(1000)
t = pyb.millis()
t = pyb.micros()
```

## 62. Idea central

Para esta EDU-CIAA, el modelo mental más útil es:

```text
MicroPython
     │
     ▼
    pyb
     │
     ├── hardware básico
     │    ├── LED
     │    ├── Switch
     │    ├── Pin
     │    └── ExtInt
     │
     ├── adquisición/generación
     │    ├── ADC
     │    ├── DAC
     │    └── PWM
     │
     ├── tiempo
     │    ├── Timer
     │    └── RTC
     │
     ├── comunicaciones
     │    ├── UART
     │    ├── RS485
     │    ├── SPI
     │    └── I2C
     │
     ├── almacenamiento
     │    └── EEPROM
     │
     └── interfaz
          ├── LCD
          └── Keyboard
```

La combinación **ADC + Timer + DAC + DMA + UART/RS-485 + Python** es probablemente la parte más potente de este port para hacer experimentos de sistemas embebidos, instrumentación y automatización.