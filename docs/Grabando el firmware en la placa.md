# Grabando el firmware en la placa

El primer paso es grabar el firmware en la EDU-CIAA, para ello necesitamos compilar el proyecto y tener funcionando OpenOCD para poder grabarlo en la placa, la misma la conectaremos por el conector USB-debug.

Instalamos `git` y `zip` en el sistema:

```bash
sudo install git zip
```

## Clonando el repositorio del firmware

Luego debemos clonar el repositorio del proyecto micropython para la EDU-CIAA creado por Martín Ribelotta:

```bash
git clone https://github.com/martinribelotta/micropython.git
cd micropython
```

El repositorio anterior puede no ser estable debido a que el proyecto se encuentra en desarrollo. Para utilizar la última versión estable del proyecto, se puede clonar el siguiente repositorio en lugar del anterior:

```bash
git clone https://github.com/ernesto-g/micropython.git
cd micropython
```

## Compilando y grabando el firmware

Ingresamos al directorio `ciaa-nxp` y compilamos el proyecto

```bash
cd ciaa-nxp
make
```

Conectamos la placa por el conector USB de debug y grabamos el firmware generado mediante el comando:

```bash
make download
```

## Troubleshooting

A continuación se plantean una serie de problemas típicos con sus soluciones.

### El script se graba en la placa pero no se ejecuta

Si es posible grabar el script en la placa mediante el IDE y luego al ejecutarlo solo aparece el intérprete de Python y el script nunca se ejecuta, es posible que la FAT dentro de la memoria de programa del microcontrolador este corrupta.

La solución es ejecutar:

```bash
make erase_fs
```

### La ventana de carga del script indica ERROR

Es posible que la placa ya tenga un script que imprima datos por la consola constantemente, esto interfiere con el proceso de grabación del script, se debe iniciar primero el proceso de grabación y luego la placa, para ello se utiliza el botón de reset.

Solución: asegurarse de presionar el botón de RESET de la placa y luego el botón "Load Script" en el IDE, luego se debe soltar el botón de RESET.
