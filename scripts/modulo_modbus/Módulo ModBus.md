# Módulo ModBus

## Modo Master

Ejemplo: Lectura de registro en la dirección `0x0001` desde un esclavo con la dirección `0x55` usando la `uart 3`.

```python
import pyb
import ModBus

uart = pyb.UART(3)
uart.init(115200)

instrument = ModBus.Instrument(uart,0x55,mode=ModBus.MODE_ASCII)
print(instrument)

while True:
    try:
        v = instrument.read_register(1)
        print("Register 1 value :"+str(v))
    except Exception as e:
        print(e)
    pyb.delay(1000)
```

La clase `Instrument` necesita para ser creada, un objeto `uart`, que representa un puerto serie de la placa, la dirección del slave (`0x55` en este ejemplo) y por ultimo el modo del protocolo modbus:

* ModBus.MODE_ASCII
* ModBus.MODE_RTU

El objeto instrument se puede usar para leer y escribir registros a través del puerto serie en el slave definido usando el protocolo Modbus.

## Métodos soportados:

* read_bit(self, registeraddress, functioncode=2)

Lee un bit del dispositivo slave
Args:
* registeraddress (int): La dirección del registro del slave.
* functioncode (int): Código de función modbus. Puede ser 1 o 2.

Returns:
    El valor del bit 0 o 1 (int).

Raises:
    ValueError, TypeError, IOError

* write_bit(self, registeraddress, value, functioncode=5)

Escribe un bit en el dispositivo slave.
Args:
* registeraddress (int): La dirección del registro del slave.
* value (int): 0 o 1
* functioncode (int): Código de función modbus. 5 o 15.

Returns:
    None

Raises:
    ValueError, TypeError, IOError

* read_register(self, registeraddress, numberOfDecimals=0, functioncode=3, signed=False)

Lee un integer de uno de los registros de 16 bit del dispositivo slave, con la posibilidad de escalarlo.

Args:
    * registeraddress (int): La dirección del registro del slave.
    * numberOfDecimals (int): Cantidad de decimales para la conversión del contenido.
    * functioncode (int): Código de función modbus. 3 o 4.
    * signed (bool): Interpretación del contenido con signo.

Si un valor de 77.0 se almacena internamente en el registro como 770, se debe utilizar ``numberOfDecimals=1``
de este modo se dividirá el contenido por 10 antes de devolver el valor.

De la misma forma, si se utiliza ``numberOfDecimals=2`` se dividirá por 100.

Returns:
    El dato del registro en forma numérica (int o float).

Raises:
    ValueError, TypeError, IOError

* write_register(self, registeraddress, value, numberOfDecimals=0, functioncode

Escribe un integer de uno de los registros de 16 bit del dispositivo slave, con la posibilidad de escalarlo.

Args:
    * registeraddress (int): La dirección del registro del slave.
    * value (int or float): Valor a escribir.
    * numberOfDecimals (int): Cantidad de decimales para la conversión del contenido.
    * functioncode (int): Código de función modbus. 6 o 16.
    * signed (bool): Interpretación del contenido con signo.

Si un valor de 77.0 se almacena internamente en el registro como 770, se debe utilizar ``numberOfDecimals=1``
de este modo se multiplicara el contenido por 10 antes de enviar el valor al slave.

Returns:
    None

Raises:
    ValueError, TypeError, IOError

* read_registers(self, registeraddress, numberOfRegisters, functioncode=3)

Lee integers en los registros de 16 bit del dispositivo slave

Args:
    * registeraddress (int): La dirección de inicio de los registros a leer del slave.
    * numberOfRegisters (int): Numero de registros a leer.
    * functioncode (int): Código de función modbus. 3 o 4.

Returns:
    Los valores de los registros en una list de integers.

Raises:
    ValueError, TypeError, IOError

* write_registers(self, registeraddress, values)

Escribe integers en los registros de 16-bit del dispositivo slave.

Usa el código de función modbus 16.

El número de registros a escribir esta dado por la cantidad de valores en la lista.

Args:
    * registeraddress (int): La dirección de inicio de los registros a escribir en el slave.
    * values (list of int): Valores a escribir en los registros.

Returns:
    None

Raises:
    ValueError, TypeError, IOError

## Modo Slave

Ejemplo:

```python
import pyb
import ModBus

uart = pyb.UART(3)
uart.init(115200)
led1 = pyb.LED(1)

mappedRegs = {0x4000 : 0x0000 , 0x4001 : 0x0000}

modbus = ModBus.Slave(uart,0x55,mappedRegs,mode=ModBus.MODE_ASCII)
print(modbus)

print(mappedRegs)

while True:
    if modbus.receive():
        print(mappedRegs)
        if mappedRegs[0x4000]==0:
            led1.off()
        else:
            led1.on()
```

En el modo slave, se necesita definir un diccionario donde se mapearán los supuestos registros del dispositivo slave. En este diccionario, las claves serán las direcciones de los registros, y los valores del diccionario, los valores de cada registro. En el ejemplo, se definen dos registros, uno en la dirección `0x4000` y otro en la dirección `0x4001` ambos con el valor `0`. Se soportan comandos para leer y escribir registros, estos comandos modificarán los valores del diccionario.

Para crear el objeto `Slave`, se necesita un objeto `uart`, la dirección del slave, el diccionario con los registros definidos y la constante que indica si se utilizará Modbus en modo ascii o rtu.

El método "receive" se debe ejecutar constantemente para recibir por el puerto serie las tramas modbus, al recibirlas se modificará el estado del diccionario y se devolverá True, de lo contrario el método devolverá False.
