# reset_repl.py
# Si se presiona el switch "TEC1" al iniciar
# devuelve el control al REPL
#
# Creado el 16 de junio de 2024
# Por Lucas Martin Treser
#

import pyb

flag = True

def reset(sw):      
    global flag
    flag = False
    print("REPL return")

tec1 = pyb.Switch(1)
tec1.callback(reset)
pyb.delay(1000)

# Desactivar el callback y eliminar el objeto
tec1.callback(None)
del tec1

# Bucle principal, acá va el programa principal
while (flag == True):
    print("Bucle principal")
    pyb.delay(1000)
    pass
