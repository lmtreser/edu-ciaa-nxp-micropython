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

