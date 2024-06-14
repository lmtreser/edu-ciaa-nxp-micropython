# Python corriendo en la EDU-CIAA

Existe en desarrollo un firmware que permite interpretar un programa escrito en lenguaje Python. El proyecto es llamado [micro-python](https://micropython.org/) y fue desarrollado para un hardware llamado pyboard.

Se desarrolló una versión de este firmware para correr en la EDU-CIAA, mediante el cual es posible ejecutar un archivo de extensión `.py` o utilizar una consola de Python en donde el código se va ejecutando a medida que se van escribiendo las líneas.

## Soporte de hardware

Hasta el momento el soporte de hardware existente es el siguiente:

* Manejo de los 3 leds
* Manejo del led RGB
* Manejo de los 4 pulsadores
* Manejo de la UART
* Manejo del puerto RS-485
* Manejo de las 9 GPIOs
* Manejo del DAC
* Manejo de Timers
* Manejo de 11 salidas de PWM
* Manejo de 3 entradas analógicas
* [Teclado matricial y LCD HD44780U](https://www.proyecto-ciaa.com.ar/devwiki/doku.php%3Fid=desarrollo:edu-ciaa:poncho_ui.html)
* EEPROM interna (16 Kbytes)
* Manejo de SPI modo Master
* RTC con alarma y registros de backup.
* Manejo de I2C modo Master

## Soporte de software

* Módulo json
* Módulo Modbus
* Módulo utime
* Módulo math
