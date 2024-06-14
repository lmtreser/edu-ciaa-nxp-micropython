import pyb

uart = pyb.UART(3)
uart.init(115200,bits=8, parity=None, stop=1,timeout=500, timeout_char=1, read_buf_len=64)

# Se agregó un modo de recepcion por “paquete” en donde la trama que llega se almacena en
# un buffer interno y luego el metodo “any()” devuelve True. Utilizando el metodo “readall()”
# se obtiene la trama completa. Para habilitar la recepcion por paquete se deben agregar el
# argumento “packet_mode” en True al final del metodo “init()”.

# uart.init(115200,bits=8, parity=None, stop=1,timeout=200, timeout_char=1, read_buf_len=64,
# packet_mode=True)

uart.write("Hola mundo")

while True:
        if uart.any():
                print("hay data:")
                data = uart.readall()
                print(data)