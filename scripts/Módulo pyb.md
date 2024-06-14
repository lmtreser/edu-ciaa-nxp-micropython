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
