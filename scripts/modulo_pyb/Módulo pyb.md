# Módulo pyb

Este módulo posee las clases que representan los periféricos de hardware de la placa. Creando objetos de estas clases se podrán manejar dichos perifericos.

Clases Soportadas

* LED : Permite el uso de los Leds
* Switch : Permite el uso de los pulsadores
* UART : Permite el uso de las dos UARTs
* Pin : Permite el uso de las GPIOs
* ADC : Permite el uso de las entradas analógicas
* DAC : Permite el uso del conversor digital analógico
* Timers : Permite el uso de los timers
* EEPROM : Permite el uso de la memoria EEPROM interna del microcontrolador
* ExtInt : Permite usar las GPIOs con interrupciones
* PWM : Permite el uso de las salidas PWM
* Keyboard : Configura algunos GPIOs para escanear un teclado matricial
* LCD : Configura algunos GPIOs para manejar un LCD tipo HD44780U
* SPI : Permite el uso del módulo SPI en modo Master
* RTC : Permite el uso del módulo RTC y los registros de backup
* I2C : Permite el uso del módulo I2C en modo Master

## Soporte Leds: Clase LED

La clase LED permite la creación de objetos que representan los LEDs que posee la placa.

### Constructor

La clase posee un constructor que recibe un solo argumento, este argumento es el número de LED que controlará.

Números de leds disponibles: de 1 a 6:

* 1: Led 1
* 2: Led 2
* 3: Led 3
* 4: Led RGB (Red)
* 5: Led RGB (Green)
* 6: Led RGB (Blue)

### Métodos

* on(): Enciende el LED
* off(): Apaga el LED
* toggle(): Invierte el estado del LED
* value(): Devuelve el estado del LED (True o False)
* intensity(value): Solo válido para los 3 leds RGB. Recibe como argumento un número de 0 a 15 y configura la intensidad de brillo del LED. Esto permitirá formar diferentes colores.

### Ejemplo Blinky

```python
import pyb
led1 = pyb.LED(1)
while True:
    led1.on()
    pyb.delay(1000)
    led1.off()
    pyb.delay(1000)
```

## Soporte Pulsadores: Clase Switch

La clase Switch permitirá crear objetos que representan los pulsadores de la placa.

### Constructor

La clase posee un constructor que recibe un solo argumento, este argumento es el número de pulsador que controlará.

Números de pulsadores: de 1 a 4

### Métodos

* switch() : Devuelve True si el pulsador está presionado, de lo contrario devuelve False
* callback(fn) : Recibe como argumento una función la cual se ejecutará cuando se presione el pulsador.

### Ejemplo 1

```python
import pyb
switch1 = pyb.Switch(1)
while True:
    val = switch1.switch()
    print('sw1:'+str(val))
    pyb.delay(200)
```

### Ejemplo 2, uso de callbacks

```python
import pyb

def func(sw):
    print("sw pressed!")
    print(sw)

switch1 = pyb.Switch(1)
switch1.callback(func)
while True:
    pyb.delay(1000)
```

## Soporte UART y RS485: Clase UART

La clase UART permitirá crear objetos que representan los módulos UART y RS485 de la placa.

### Constructor

La clase posee un constructor que recibe como argumento el número de UART que controlará. Los valores posibles son:

- 0: RS485
- 3: UART

### Métodos

- `init()`: Recibe la configuración de la UART, la cual consta de 1 argumento obligatorio (baudrate) y 9 opcionales:
  - `baudrate`: Obligatorio. Define la velocidad de comunicación.
  - `bits`: Solo se soporta el valor 8.
  - `parity`: Indica la paridad:
    - `None`: sin paridad.
    - `1`: Impar.
    - `2`: Par.
    - `3`: F1.
    - `4`: F2.
  - `stop`: Indica la cantidad de bits de stop (1 o 2).
  - `timeout`: En el modo recepción por paquete, indica el tiempo que debe pasar para que se reconozca la recepción de una trama. Indicado en ms.
  - `timeout_char`: Tiempo entre envío de bytes indicado en ms.
  - `read_buf_len`: En el modo recepción por paquete, tamaño del buffer de recepción (máx. 2048).
  - `packet_mode`: Indica si la recepción será por byte o por trama.
    - `True`: Por trama.
    - `False`: Por byte.
  - `packet_end_char`: En el modo recepción por paquete, espera este valor para detectar un fin de trama.

- `write(buff)`: Envía una trama por la UART. `buff` puede ser un `bytearray` o un `string`.
- `writechar(ch)`: Envía un carácter por la UART.
- `get_baudrate()`: Devuelve el baudrate configurado.
- `any()`: Devuelve `True` si se recibió un byte/trama.
- `readchar()`: Espera el tiempo `timeout` para leer un byte recibido. En el caso de que no haya nada para recibir, devuelve `-1`; de lo contrario, devuelve el byte recibido.
- `read([nBytes])`: Espera el tiempo `timeout` y devuelve un `bytearray` con los datos recibidos. Opcionalmente, se puede indicar un máximo de bytes a recibir.
- `readall()`: Espera el tiempo `timeout` y devuelve un `bytearray` con los datos recibidos.
- `readinto(buf[, nbytes])`: Espera el tiempo `timeout` y carga los datos recibidos en el objeto `bytearray` pasado como primer argumento. Opcionalmente, se puede indicar un máximo de bytes.

### Ejemplo 1: Envío y recepción en modo byte

```python
import pyb
uart = pyb.UART(3)
uart.init(115200, bits=8, parity=None, stop=1, timeout=500, timeout_char=1, read_buf_len=64)
uart.write("Hola mundo")
while True:
    if uart.any():
        print("hay data:")
        data = uart.readall()
        print(data)
```

### Ejemplo 2: Envío y recepción en modo trama

Se agregó un modo de recepción por "paquete" en donde la trama que llega se almacena en un buffer interno y luego el método `any()` devuelve `True`. Utilizando el método `readall()` se obtiene la trama completa. Para habilitar la recepción por paquete se debe agregar el argumento `packet_mode` en `True` al final del método `init()`.

```python
uart.init(115200, bits=8, parity=None, stop=1, timeout=200, timeout_char=1, read_buf_len=64, packet_mode=True)
```

## Soporte GPIOs: Clase Pin

La clase Pin permitirá crear objetos que representan las GPIOs de la placa.

### Constructor

La clase posee un constructor que recibe un solo argumento, este argumento es el número de GPIO que controlará.

Números de GPIOs: 0 a 8 (como se indican en la placa).

### Métodos

- `low()`: Pone el pin GPIO en un 0 lógico si el mismo está configurado como salida.
- `high()`: Pone el pin GPIO en un 1 lógico si el mismo está configurado como salida.
- `value()`: Devuelve el número 0 o 1 según el estado del pin, ya sea si está configurado como entrada o como salida.
- `init(mode, pull)`: Configura la GPIO, recibe 1 argumento obligatorio y uno opcional:
  - `mode`: Indica el modo del pin, los valores posibles son:
    - `Pin.IN`: Entrada.
    - `Pin.OUT_PP`: Salida Push-Pull.
    - `Pin.OUT_OD`: Salida Open Drain.
  - `pull`: Configura las resistencias de pull up/down del pin, los valores posibles son:
    - `Pin.PULL_NONE`: Sin resistencias.
    - `Pin.PULL_UP`: Se habilita la resistencia de pull-up.
    - `Pin.PULL_DOWN`: Se habilita la resistencia de pull-down.

### Ejemplo

```python
p = pyb.Pin(0)  # GPIO0
p.init(pyb.Pin.OUT_PP, pyb.Pin.PULL_NONE)
print(p)

while True:
    p.high()
    print("value:" + str(p.value()))
    pyb.delay(1000)
    p.low()
    print("value:" + str(p.value()))
    pyb.delay(1000)
```

## Soporte ADC: Clase ADC

La clase ADC permitirá crear objetos que representan las entradas analógicas de la placa.

### Constructor

La clase posee un constructor que recibe un solo argumento, este argumento es el número de entrada que controlará.

Los números disponibles son: 1, 2 o 3.

### Métodos

- `read()`: Devuelve el valor medido en cuentas (0 a 1023, 10 bits de resolución en 3.3V).

### Ejemplo 1

```python
import pyb

channel1 = pyb.ADC(1)
channel2 = pyb.ADC(2)
channel3 = pyb.ADC(3)

while True:
    v1 = channel1.read()
    v2 = channel2.read()
    v3 = channel3.read()
    print("value ch1:" + str(v1))
    print("value ch2:" + str(v2))
    print("value ch3:" + str(v3))
    pyb.delay(1000)
```

## Soporte DAC: Clase DAC

La clase DAC permitirá crear objetos que representan la salida analógica de la placa.

### Constructor

La clase posee un constructor que recibe un solo argumento, este argumento es el número de salida analógica que controlará. Solo existe una salida, por lo que el valor que debe pasarse siempre es 1.

### Métodos

- `write(val)`: Escribe el valor en cuentas (0 a 1023) en la salida con un fondo de escala de 3.3V.
- `noise(f)`: Genera una señal de ruido pseudoaleatorio de 256 muestras a la frecuencia especificada (de 1 a 400000).
- `triangle(f)`: Genera una señal triangular de 256 muestras a la frecuencia especificada (de 1 a 400000).
- `write_timed(data, freq, mode)`: Genera una señal utilizando como muestras el array de datos pasado como argumento (`data`) a la frecuencia dada (`freq` de 1 a 400000) utilizando DMA. El argumento `mode` puede ser `pyb.DAC.NORMAL` (solo genera la señal una vez) o `pyb.DAC.CIRCULAR` (al terminar vuelve a empezar).

### Ejemplo: Generación de una señal senoidal

```python
import pyb
import math

dac = pyb.DAC(1)

# sine
buf = bytearray(200)  # 100 samples. 2 bytes per sample
j = 0
for i in range(0, len(buf) // 2):
    v = 512 + int(511 * math.sin(2 * math.pi * i / (len(buf) // 2)))
    buf[j + 1] = (v >> 8) & 0xff
    buf[j] = v & 0xff
    j += 2

# output the sine-wave at 400Hz
print("sine created")

dac.write_timed(buf, 400 * (len(buf) // 2), mode=pyb.DAC.CIRCULAR)

while True:
    pyb.delay(1000)
```

## Soporte Timers: Clase Timer

La clase Timer permitirá crear objetos que representan los módulos Timers del microcontrolador.

No se implementó la clase TimerChannel, por lo que las funcionalidades de Output Compare e Input Capture no son accesibles.

### Constructor

La clase posee un constructor que recibe un solo argumento, este argumento es el número de timer que controlará.

Timers disponibles: 0, 1, 2 y 3.

### Métodos

- `interval(t, fn)`: Ejecuta la función pasada como argumento `fn` periódicamente cada el tiempo `t` expresado en ms.
- `timeout(t, fn)`: Ejecuta la función pasada como argumento `fn` luego del tiempo `t` expresado en ms.
- `init(prescaler, period)`: Configura el timer con un prescaler dado y un periodo dado (números de 32 bits).
- `init(freq)`: Configura el timer para la frecuencia dada (de 1 a 1000000 Hz).
- `callback(fn)`: Configura una función que se ejecutará al vencerse el timer. La función recibirá como argumento el objeto Timer.
- `counter([value])`: Devuelve o establece el valor del contador del Timer (número de 32 bits).
- `freq([value])`: Devuelve o establece el valor de la frecuencia del Timer (de 1 a 1000000 Hz).
- `period([value])`: Devuelve o establece el valor del periodo (valor de comparación de la cuenta, número de 32 bits).
- `prescaler([value])`: Devuelve o establece el valor del prescaler (número de 32 bits).
- `source_freq()`: Devuelve la frecuencia de operación del microcontrolador en Hz.

### Ejemplo 1: Uso de timeout e interval

```python
import pyb

def callb(timer):
    print("Interval interrupt")
    print(timer)

def callbTimeout(timer):
    print("Timeout interrupt")
    print(timer)

print("Test Timers")

t1 = pyb.Timer(1)
t2 = pyb.Timer(2)
t1.interval(2000, callb)
t2.timeout(5000, callbTimeout)

while True:
    pyb.delay(1000)
```

### Ejemplo 2: Ejecución cada 100Hz

```python
import pyb

counter = 0

def callb(timer):
    global counter
    counter += 1

t1 = pyb.Timer(1)
t1.init(freq=100)  # 100Hz
t1.callback(callb)

while True:
    pyb.delay(1000)
    print("counter:" + str(counter))
```

## Soporte EEPROM interna: Clase EEPROM

La clase EEPROM permitirá crear un objeto que representa la memoria EEPROM interna del microcontrolador.

### Constructor

El constructor de la clase no recibe parámetros.

### Métodos

La clase EEPROM posee métodos para leer y escribir bytes (8 bits), enteros (32 bits), números con punto flotante (32 bits) y Strings.

- `write_byte(addr, val)`: Escribe un byte en la dirección indicada y devuelve la cantidad de bytes escritos (1 byte).
- `write_int(addr, val)`: Escribe un entero en la dirección indicada y devuelve la cantidad de bytes escritos (4 bytes).
- `write_float(addr, val)`: Escribe un float en la dirección indicada y devuelve la cantidad de bytes escritos (4 bytes).
- `write(val)`: Escribe un String a partir de la dirección 0x0000 de la EEPROM.

- `read_byte(addr)`: Lee un byte en la dirección indicada.
- `read_int(addr)`: Lee un entero desde la dirección indicada.
- `read_float(addr)`: Lee un float desde la dirección indicada.
- `readall()`: Lee un string desde la dirección 0x0000 de la EEPROM.

La capacidad de la EEPROM es de 16 Kbytes.

### Ejemplo 1

```python
import pyb
eeprom = pyb.EEPROM()

# R/W bytes test
eeprom.write_byte(0x0000, 0x27)
eeprom.write_byte(0x0004, 0x28)
for addr in range(0, 16):
    val = eeprom.read_byte(addr)
    print(hex(val))

# R/W 32bit integers test
eeprom.write_int(0x0000, 0x11223344)
eeprom.write_int(0x0004, 0x12345678)
val = eeprom.read_int(0x0000)
print(hex(val))
val = eeprom.read_int(0x0004)
print(hex(val))

# R/W 64bit doubles test
eeprom.write_float(0x0000, 3.14)
val = eeprom.read_float(0x0000)
print(str(val))
```

### Ejemplo: Lectura y escritura de un diccionario usando JSON

```python
import pyb
import json

dic = {
    "k1": "Hello",
    "k2": "World",
    "k3": 2016,
    "k4": 3.14
}
print("Python Dict obj:")
print(dic)

# write dict in eeprom
jsonStr = json.dumps(dic)
print("JSON to write:")
print(jsonStr)
eeprom = pyb.EEPROM()
eeprom.write(jsonStr)

# read dict from eeprom
print("Python Dict obj from EEPROM:")
jsonStr = eeprom.readall()
dic = json.loads(jsonStr)
print(dic)
```

En este ejemplo se crea un diccionario Python y luego se serializa utilizando el módulo `json`. Una vez obtenido el String que representa al diccionario, se graba en la EEPROM mediante el método `write`. Para volver a construir el diccionario, se lee el String desde la EEPROM mediante el método `readall` y luego se decodifica mediante el método `loads` del módulo `json`.

Aquí tienes el markdown corregido y formateado para ser compatible con GitHub:

## Soporte interrupciones en GPIOs: Clase ExtInt

```python
import pyb

def callBack(line):
    print("Pin Interrupt!")
    print("Line = ", line)

p = pyb.Pin(8)
p.init(pyb.Pin.OUT_PP, pyb.Pin.PULL_NONE)
print(p)

int = pyb.ExtInt(p, pyb.ExtInt.IRQ_RISING, pyb.Pin.PULL_NONE, callBack)
print(int)

while True:
    pyb.delay(1000)
    print("tick")
```

Existen 4 interrupciones disponibles para asignar a cualquiera de las 9 GPIOs. Se implementaron los siguientes métodos:

- `enable()`
- `disable()`
- `swint()`
- `line()`

Más información en: [pyb.ExtInt](http://test-ergun.readthedocs.org/en/latest/library/pyb.ExtInt.html)

## Soporte PWM: Clase PWM

```python
import pyb

pyb.PWM.set_frequency(1000)

out0 = pyb.PWM(0)
out0.duty_cycle(50)  # 50%
print("Duty cycle :" + str(out0.duty_cycle()))

out1 = pyb.PWM(1)
out1.duty_cycle(25)

out10 = pyb.PWM(10)
out10.duty_cycle(75)

while True:
    pyb.delay(1000)
```

### Salidas de PWM disponibles: 0 a 10

- 0: GPIO_2
- 1: GPIO_8
- 2: T_FIL1
- 3: T_FIL2
- 4: T_FIL3
- 5: T_COL0
- 6: T_COL1
- 7: T_COL2
- 8: LCD_1
- 9: LCD_2
- 10: LCD_3

La placa posee un solo módulo PWM con 11 salidas asociadas. Por esta razón, todas las salidas comparten la misma frecuencia, pero tienen un valor de ciclo de actividad independiente.

## Soporte Teclado Matricial: Clase Keyboard

```python
import pyb

keyboard = pyb.Keyboard(4, 4)  # 4 filas, 4 columnas
print(keyboard)

while True:
    key = keyboard.get_char()
    print("key:" + str(key))
```

El constructor recibe la cantidad de filas y columnas que se sensan. El método `get_char` se quedará esperando que se presione una tecla, devolviendo un byte donde los 4 bits de más peso corresponden con el número de fila y los 4 bits de menor peso corresponden con el número de columna. También puede utilizarse el método `get_matrix`, el cual no es bloqueante y devolverá `0xFF` si ninguna tecla es presionada.

### Pines de Conexión del Teclado

- T_FIL0
- T_FIL1
- T_FIL2
- T_FIL3
- T_COL0
- T_COL1
- T_COL2
- GPIO8 (T_COL3)

## Soporte LCD tipo HD44780U: Clase LCD

```python
import pyb

lcd = pyb.LCD(2, 0)  # 2 líneas, formato de punto: 5x8
lcd.clear()

lcd.write("Test LCD\nEDUCIAA")
pyb.delay(1000)

lcd.clear()
lcd.config_cursor(True, True)  # Cursor ON, Blink ON

c = 0
while True:
    c = c + 1
    lcd.goto_xy(0, 0)
    lcd.write("counter:" + str(c))
    lcd.goto_xy(10, 1)
    lcd.write(str(c))
    pyb.delay(1000)
```

El constructor recibe la cantidad de líneas (1, 2, 3 o 4) y el formato del caracter (0: 5x8 - 1: 5x10). El cursor se encuentra deshabilitado por defecto. Mediante el método `config_cursor` es posible habilitar su visualización y blinking. El método `goto_xy` posiciona el cursor en la columna y fila especificada, permitiendo al método `write` escribir desde dicha posición.

## Soporte SPI modo Master: Clase SPI

```python
import pyb

spi = pyb.SPI(8, 0, 10000)

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
```

El constructor de la clase SPI recibe 3 argumentos:

- Cantidad de bits: 4, 8 o 16.
- Modo del SPI: 0, 1, 2 o 3.
- Frecuencia del clock SPI: expresada en Hz.

Una vez creado el objeto `spi`, se podrá leer y escribir datos mediante el método `write`, el cual recibe un bytearray, y el método `read`, el cual recibe como argumento la cantidad de frames SPI (cantidad de bytes si los bits fueron configurados en 8) y devuelve un array de bytes con los datos leídos.

## Soporte RTC: Clase RTC

```python
import pyb
rtc = pyb.RTC()

# (year, month, day, weekday, hours, minutes, seconds)
# newDt = [2015, 12, 31, 0, 18, 16, 0]
# rtc.datetime(newDt)

while True:
    now = rtc.datetime()
    print(now)
    pyb.delay(1000)
```

El método `datetime` lee o establece los valores de fecha y hora del módulo RTC. Si no se le pasan argumentos, el método devolverá una tupla de 7 valores con la fecha y hora actual. Si se le pasa una tupla como argumento, esos valores se cargarán en el módulo RTC. El formato de la tupla es:

(year, month, day, weekday, hours, minutes, seconds)

El campo "weekday" toma los valores de 0 a 6. El módulo RTC continúa funcionando después de un reinicio del CPU y si se alimenta con una batería, el RTC seguirá funcionando incluso sin la alimentación principal del CPU.

### Ejemplo de calibración

```python
import pyb
rtc = pyb.RTC()
rtc.calibration(0)
newDt = [2015, 12, 31, 0, 18, 16, 0]
rtc.datetime(newDt)
```

El método `calibration` ajusta periódicamente el contador del módulo RTC. Los valores permitidos son de -131072 a 131072. Leer [este documento](http://www.nxp.com/documents/user_manual/UM10503.pdf) para información detallada del procedimiento de calibración. Después de la calibración, se debe establecer una fecha y hora.

### Ejemplo de uso de registros de backup

```python
import pyb
rtc = pyb.RTC()

# rtc.write_bkp_reg(0, 27)
# rtc.write_bkp_reg(32, 28)
# rtc.write_bkp_reg(63, 29)

while True:
    print(rtc.read_bkp_reg(0))
    print(rtc.read_bkp_reg(32))
    print(rtc.read_bkp_reg(63))
    pyb.delay(1000)
```

Existen 64 registros de 32 bits que mantendrán sus valores incluso después de un reinicio del CPU. Si se alimenta con una batería, los valores se mantendrán incluso sin la alimentación principal del CPU. El método `write_bkp_reg` tiene como argumento la dirección del registro (0 a 63) y el valor de 32 bits a escribir. El método `read_bkp_reg` tiene como argumento la dirección del registro (0 a 63) y devolverá el valor que se encuentra en el mismo.

### Ejemplo de uso de alarma

```python
import pyb
rtc = pyb.RTC()

newDt = [2015, 12, 31, 0, 20, 15, 0]
rtc.datetime(newDt)

def rtcCallback(rtc):
    print("Alarm int!")

alarmDt = [2015, 12, 31, 0, 20, 16, 10]
rtc.alarm_datetime(alarmDt, pyb.RTC.MASK_SEC | pyb.RTC.MASK_MIN)
rtc.callback(rtcCallback)

print("alarm:")
print(rtc.alarm_datetime())
```

En este ejemplo se define una función (`rtcCallback`) que se ejecutará cuando se cumpla la fecha de la alarma. Mediante el método `alarm_datetime` se configura (o lee) la fecha de la alarma con la misma tupla de 7 valores usada para configurar la fecha y hora actual. Como segundo argumento se pasa la máscara de la alarma, la cual se construye con las constantes:

- `pyb.RTC.MASK_SEC`: Se chequea el campo de segundos en la comparación.
- `pyb.RTC.MASK_MIN`: Se chequea el campo de minutos en la comparación.
- `pyb.RTC.MASK_HR`: Se chequea el campo de horas en la comparación.
- `pyb.RTC.MASK_DAY`: Se chequea el campo de día en la comparación.
- `pyb.RTC.MASK_MON`: Se chequea el campo de mes en la comparación.
- `pyb.RTC.MASK_YR`: Se chequea el campo de año en la comparación.
- `pyb.RTC.MASK_DOW`: Se chequea el campo de día de la semana en la comparación.

 Mediante el método `callback` se setea la función que se ejecutara cuando se produzca la alarma. En el ejemplo se construye la máscara con segundos y minutos, por lo que la alarma se producirá cada hora, a los 16 minutos y 10 segundos.

Para deshabilitar la alarma puede ejecutarse el método `alarm_disable`.

## Soporte I2C Master: Clase I2C

Ejemplo lectura y escritura de una memoria tipo 24C04:

```python
import pyb

print("Test I2C with AT24C04")

i2c = pyb.I2C(100000)  # 100Khz
i2c.slave_addr(0x50)

def writeByte(addr, value):
    data = bytearray()
    data.append(addr)
    data.append(value)
    i2c.write(data)

def readBytes(addr, size):
    data = bytearray()
    data.append(addr)
    i2c.write(data)
    return i2c.read(size)

writeByte(0x00, 11)
pyb.delay(10)
writeByte(0x01, 22)
pyb.delay(10)
writeByte(0x02, 33)
pyb.delay(10)

data = readBytes(0x00, 16)
print("[0]:" + str(data[0]))
print("[1]:" + str(data[1]))
print("[2]:" + str(data[2]))
```

El constructor de la clase `I2C` recibe como argumento la velocidad (100KHz o 400KHz) expresada en Hz. Luego de crear el objeto `i2c`, se ejecuta el método `slave_addr`, mediante el cual se configura la dirección del dispositivo esclavo que se utilizará al leer y escribir datos por el bus. Esto puede cambiarse en cualquier momento.

Se puede leer y escribir datos mediante el método `write`, que recibe un bytearray, y el método `read`, que recibe como argumento la cantidad de bytes a leer y devuelve un array de bytes con los datos leídos.

En el ejemplo se escriben dos funciones: una para escribir un byte en la memoria y otra para leer una cierta cantidad de bytes, siempre indicando la dirección.
