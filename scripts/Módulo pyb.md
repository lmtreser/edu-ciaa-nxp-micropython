====== Módulo pyb ======

Este módulo posee las clases que representan los periféricos de hardware de la placa. Creando objetos de estas clases se podrán manejar dichos perifericos.

===== Clases Soportadas =====

  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-led|LED]] : Permite el uso de los Leds
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-switch|Switch]] : Permite el uso de los pulsadores
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-uart|UART]] : Permite el uso de las dos UARTs
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-pin|Pin]] : Permite el uso de las GPIOs
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-adc|ADC]] : Permite el uso de las entradas analógicas
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-dac|DAC]] : Permite el uso del conversor digital analógico
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-timer|Timers]] : Permite el uso de los timers
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-eeprom|EEPROM]] : Permite el uso de la memoria EEPROM interna del microcontrolador
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-extint|ExtInt]] : Permite usar las GPIOs con interrupciones
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-pwm|PWM]] : Permite el uso de las salidas PWM
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-keyboard|Keyboard]] : Configura algunos GPIOs para escanear un teclado matricial
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-lcd|LCD]] : Configura algunos GPIOs para manejar un LCD tipo HD44780U
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-spi|SPI]] : Permite el uso del módulo SPI en modo Master
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-rtc|RTC]] : Permite el uso del módulo RTC y los registros de backup
  * [[desarrollo:edu-ciaa:edu-ciaa-nxp:python:bibliotecas:modulo-pyb-i2c|I2C]] : Permite el uso del módulo I2C en modo Master

====== Soporte Leds: Clase LED ======


La clase LED permite la creación de objetos que representan los LEDs que posee la placa.

==== Constructor ====

La clase posee un constructor que recibe un solo argumento, este argumento es el número de LED que controlará.

Números de leds disponibles: de 1 a 6:
  * 1: Led 1
  * 2: Led 2
  * 3: Led 3
  * 4: Led RGB (Red)
  * 5: Led RGB (Green)
  * 6: Led RGB (Blue)


==== Métodos ====

  * on(): Enciende el LED
  * off(): Apaga el LED
  * toggle(): Invierte el estado del LED
  * value(): Devuelve el estado del LED (True o False)
  * intensity(value): Solo válido para los 3 leds RGB. Recibe como argumento un número de 0 a 15 y configura la intensidad de brillo del LED. Esto permitirá formar diferentes colores.

==== Ejemplo Blinky ====

  import pyb
  led1 = pyb.LED(1)
  while True:
      led1.on()
      pyb.delay(1000)
      led1.off()
      pyb.delay(1000)

