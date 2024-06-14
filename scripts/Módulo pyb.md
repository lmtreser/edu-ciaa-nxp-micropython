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
