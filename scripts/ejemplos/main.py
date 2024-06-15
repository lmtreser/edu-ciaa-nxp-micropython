##################################################
# main.py
# Todo el código se ejecutará al iniciar la placa
# Si se presiona el switch "TEC1" al iniciar,
# se saltea el bucle principal
##################################################

import pyb

flag = True

def reset(sw):      
    global flag
    flag = False

tec1 = pyb.Switch(1)
tec1.callback(reset)
pyb.delay(1000)

# Desactivar el callback y eliminar el objeto
tec1.callback(None)
del tec1


##################################################
# Bucle principal, acá va el programa principal
while (flag == True):
    print("flag principal: ")
    pyb.delay(1000)
    pass


##################################################
# Fin de ejecución, devuelve el control al REPL
print("-Fin de ejecución, volviendo al REPL-")
##################################################